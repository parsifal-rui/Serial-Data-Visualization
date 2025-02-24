import random
import time
from queue import Queue
import math
import threading
from utils.constants import *

class VirtualCANBus:
    def __init__(self):
        self.message_queue = Queue()
        self.connected = False
        self.fault_status = FAULT_NONE
        
    def send(self, msg):
        if self.connected:
            self.message_queue.put(msg)
            return True
        return False
        
    def recv(self, timeout=None):
        if self.connected:
            try:
                return self.message_queue.get(timeout=timeout)
            except:
                return None
        return None

class VirtualCANMessage:
    def __init__(self, arbitration_id, data, dlc=None, is_extended_id=False):
        self.arbitration_id = arbitration_id
        self.data = data
        self.dlc = dlc or len(data)
        self.is_extended_id = is_extended_id
        self.timestamp = time.time()

class MotorSimulator:
    def __init__(self, can_bus):
        self.can_bus = can_bus
        self.running = False
        
        # 基本参数
        self.speed_ref = 0    # 速度参考值
        self.speed_actual = 0 # 实际速度
        self.position = 0     # 位置反馈
        
        # 三相电流初始相位
        self.phase = 0
        
    def start_simulation(self):
        self.running = True
        threading.Thread(target=self._simulation_loop, daemon=True).start()
        
    def stop_simulation(self):
        self.running = False
        
    def set_target_speed(self, speed):
        self.speed_ref = min(max(speed, -MAX_SPEED), MAX_SPEED)
        
    def simulate_fault(self, fault_type, duration=5):
        """模拟故障,duration秒后自动恢复"""
        self.fault_type = fault_type
        if self.fault_timer:
            self.fault_timer.cancel()
        self.fault_timer = threading.Timer(duration, self._clear_fault)
        self.fault_timer.start()
        
    def _clear_fault(self):
        self.fault_type = FAULT_NONE
        
    def _simulation_loop(self):
        while self.running:
            # 1. 模拟三相电流 (Ia, Ib, Ic)
            self.phase += 0.1  # 模拟电机旋转
            current_data = []
            
            # 120度相位差的三相电流
            ia = 10 * math.sin(self.phase)
            ib = 10 * math.sin(self.phase + 2*math.pi/3)
            ic = 10 * math.sin(self.phase + 4*math.pi/3)
            
            # 按照vofa格式打包数据
            current_msg = VirtualCANMessage(
                arbitration_id=CAN_ID_CURRENT,
                data=self._pack_float_data([ia, ib, ic])
            )
            self.can_bus.send(current_msg)
            
            # 2. 模拟速度数据 (速度参考值和实际速度)
            # 实际速度逐渐接近参考值
            speed_diff = self.speed_ref - self.speed_actual
            self.speed_actual += speed_diff * 0.1
            
            speed_msg = VirtualCANMessage(
                arbitration_id=CAN_ID_SPEED,
                data=self._pack_float_data([self.speed_ref, self.speed_actual])
            )
            self.can_bus.send(speed_msg)
            
            # 3. 模拟位置数据
            self.position = (self.position + self.speed_actual * 0.01) % 8192
            
            position_msg = VirtualCANMessage(
                arbitration_id=CAN_ID_POSITION,
                data=self._pack_float_data([self.position])
            )
            self.can_bus.send(position_msg)
            
            time.sleep(0.01)  # 100Hz更新频率

    def _pack_float_data(self, float_list):
        """将浮点数列表打包为vofa格式的字节数据"""
        import struct
        data = bytearray()
        for value in float_list:
            data.extend(struct.pack('<f', float(value)))  # 小端浮点数
        data.extend([0x00, 0x00, 0x80, 0x7F])  # 添加帧尾
        return list(data) 