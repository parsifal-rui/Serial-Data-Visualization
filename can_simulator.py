import random
import time
from queue import Queue, Empty
import math
import threading
from utils.constants import *

class VirtualCANBus:
    def __init__(self):
        self.queue = Queue()
        self.is_connected = False
        
    def connect(self):
        """连接CAN总线"""
        if not self.is_connected:
            self.is_connected = True
            print("CAN总线已连接")
            return True
        return False
        
    def disconnect(self):
        """断开CAN总线"""
        if self.is_connected:
            self.is_connected = False
            print("CAN总线已断开")
            return True
        return False
        
    def send(self, msg):
        """发送消息"""
        if not self.is_connected:
            raise RuntimeError("CAN总线未连接")
        self.queue.put(msg)
        
    def recv(self, timeout=None):
        """接收消息"""
        if not self.is_connected:
            return None
        try:
            return self.queue.get(timeout=timeout if timeout else 0)
        except Empty:
            return None

class VirtualCANMessage:
    def __init__(self, arbitration_id, data, dlc=None, is_extended_id=False):
        self.arbitration_id = arbitration_id
        
        # 统一处理命令消息和数据消息
        if arbitration_id == CAN_ID_CONTROL:
            # 控制命令格式：[cmd, speed_bytes(4), padding(3)]
            if isinstance(data, (list, bytearray)):
                self.data = list(data)  # 直接使用传入的字节列表
            else:
                self.data = data
        else:
            # VOFA数据格式
            if isinstance(data, list) and isinstance(data[0], float):
                self.data = self._pack_float_data(data)
            else:
                self.data = data
                
        self.dlc = dlc or len(self.data)
        self.is_extended_id = is_extended_id
        self.timestamp = time.time()
        
    def _pack_float_data(self, float_list):
        """将浮点数列表打包为vofa格式"""
        import struct
        data = bytearray()
        for value in float_list:
            data.extend(struct.pack('<f', float(value)))
        # 添加VOFA帧尾
        data.extend([0x00, 0x00, 0x80, 0x7F])
        return list(data)

class MotorSimulator:
    def __init__(self, can_bus):
        self.can_bus = can_bus
        self.running = False
        self.thread = None
        
        # 基本参数
        self.phase = 0
        self.speed_ref = 0
        self.speed_actual = 0
        self.total_angle = 0
        
        # 异常模拟参数
        self.fault_mode = 0  # 0: 正常, 1: 过流, 2: 欠流, 3: 超速, 4: 功率过大
        self.fault_counter = 0
        self.fault_duration = 100  # 故障持续时间(循环次数)
        self.fault_interval = 500  # 故障间隔时间(循环次数)
        
        # 噪声参数
        self.current_noise = 0.2
        self.speed_noise = 5
        self.position_noise = 0.1
        
    def start_simulation(self):
        """启动模拟器"""
        self.running = True
        self.thread = threading.Thread(target=self.simulate_data, daemon=True)
        self.thread.start()
        
    def stop_simulation(self):
        self.running = False
        
    def set_target_speed(self, speed):
        self.speed_ref = min(max(speed, -MAX_SPEED), MAX_SPEED)
        
    def simulate_data(self):
        """模拟电机数据"""
        while self.running:
            current_time = time.time()
            
            # 检查是否有新的控制命令
            control_msg = self.can_bus.recv(timeout=0)
            if control_msg and control_msg.arbitration_id == CAN_ID_CONTROL:
                try:
                    # 解析控制命令
                    import struct
                    cmd = control_msg.data[0]  # 第一个字节是命令类型
                    # 确保数据长度足够
                    if len(control_msg.data) >= 5:  # 至少需要5个字节(1字节命令 + 4字节浮点数)
                        target_speed = struct.unpack('<f', bytes(control_msg.data[1:5]))[0]
                        
                        # 更新目标速度
                        self.speed_ref = target_speed
                        
                        # 打印命令信息
                        cmd_names = {
                            CMD_START: "启动",
                            CMD_STOP: "停止",
                            CMD_SPEED_UP: "加速",
                            CMD_SPEED_DOWN: "减速",
                            CMD_REVERSE: "反转"
                        }
                        cmd_name = cmd_names.get(cmd, "未知")
                        print(f"模拟器收到命令: {cmd_name}, 目标速度: {target_speed} rpm")
                        
                except Exception as e:
                    print(f"控制命令解析错误: {str(e)}")
            
            dt = 0.01  # 10ms
            
            # 更新相位
            self.phase += 0.1
            
            # 检查是否需要触发故障
            self.fault_counter += 1
            if self.fault_counter >= self.fault_interval:
                self.fault_mode = (self.fault_mode + 1) % 5  # 循环切换故障模式
                self.fault_counter = 0
            
            # 根据故障模式生成数据
            if self.fault_mode == 0:  # 正常模式
                ia = 10 * math.sin(self.phase) + random.uniform(-self.current_noise, self.current_noise)
                ib = 10 * math.sin(self.phase + 2*math.pi/3) + random.uniform(-self.current_noise, self.current_noise)
                ic = 10 * math.sin(self.phase + 4*math.pi/3) + random.uniform(-self.current_noise, self.current_noise)
            
            elif self.fault_mode == 1:  # 过流模式
                ia = 20 * math.sin(self.phase) + random.uniform(-self.current_noise, self.current_noise)
                ib = 20 * math.sin(self.phase + 2*math.pi/3) + random.uniform(-self.current_noise, self.current_noise)
                ic = 20 * math.sin(self.phase + 4*math.pi/3) + random.uniform(-self.current_noise, self.current_noise)
            
            elif self.fault_mode == 2:  # 欠流模式
                ia = 0.05 * math.sin(self.phase) + random.uniform(-self.current_noise, self.current_noise)
                ib = 0.05 * math.sin(self.phase + 2*math.pi/3) + random.uniform(-self.current_noise, self.current_noise)
                ic = 0.05 * math.sin(self.phase + 4*math.pi/3) + random.uniform(-self.current_noise, self.current_noise)
            
            elif self.fault_mode == 3:  # 超速模式
                self.speed_actual = 3500 + random.uniform(-self.speed_noise, self.speed_noise)
                ia = 10 * math.sin(self.phase) + random.uniform(-self.current_noise, self.current_noise)
                ib = 10 * math.sin(self.phase + 2*math.pi/3) + random.uniform(-self.current_noise, self.current_noise)
                ic = 10 * math.sin(self.phase + 4*math.pi/3) + random.uniform(-self.current_noise, self.current_noise)
            
            else:  # 功率过大模式
                ia = 15 * math.sin(self.phase) + random.uniform(-self.current_noise, self.current_noise)
                ib = 15 * math.sin(self.phase + 2*math.pi/3) + random.uniform(-self.current_noise, self.current_noise)
                ic = 15 * math.sin(self.phase + 4*math.pi/3) + random.uniform(-self.current_noise, self.current_noise)
            
            # 速度和位置计算
            if self.fault_mode != 3:  # 非超速模式下的正常速度计算
                speed_diff = self.speed_ref - self.speed_actual
                speed_noise = random.uniform(-self.speed_noise, self.speed_noise)
                self.speed_actual += speed_diff * 0.1 + speed_noise
            
            # 位置计算
            angular_velocity = self.speed_actual * 360 / 60
            angle_change = angular_velocity * dt
            position_noise = random.uniform(-self.position_noise, self.position_noise)
            self.total_angle += angle_change + position_noise
            encoder_position = (self.total_angle * 8192 / 360) % 8192
            
            # 打包所有数据到一个帧
            data = [
                ia, ib, ic,                    # 三相电流
                self.speed_ref,                # 速度目标值
                self.speed_actual,             # 实际速度
                encoder_position               # 位置值
            ]
            
            msg = VirtualCANMessage(
                arbitration_id=0x01,  # 使用统一的ID
                data=data             # 所有数据打包在一起
            )
            self.can_bus.send(msg)
            
            time.sleep(0.01)  # 10ms采样周期 