from abc import ABC, abstractmethod
from queue import Queue, Empty
import struct
from dataclasses import dataclass
from typing import List, Optional, Tuple
from can import Message, Bus
import time
import threading
import random
import math

@dataclass
class MotorData:
    """电机数据结构"""
    ia: float = 0.0
    ib: float = 0.0
    ic: float = 0.0
    speed_ref: float = 0.0
    speed_fed: float = 0.0
    position: int = 0

class CANBus(ABC):
    """CAN总线基类，定义接口"""
    def __init__(self):
        self.data = MotorData()
        # 地址映射
        self.addr_map = {
            0x100: ('ia', 'f'),     # Ia, float类型
            0x101: ('ib', 'f'),     # Ib, float类型
            0x102: ('ic', 'f'),     # Ic, float类型
            0x103: ('speed_ref', 'f'),  # 速度参考值, float类型
            0x104: ('speed_fed', 'f'),  # 速度反馈值, float类型
            0x105: ('position', 'h')    # 位置反馈值, short类型
        }
        
    def parse_message(self, msg: Message) -> Tuple[Optional[int], Optional[float]]:
        """
        解析CAN消息
        :param msg: CAN消息
        :return: (地址, 值)的元组
        """
        try:
            addr = msg.arbitration_id
            if addr not in self.addr_map:
                return None, None
                
            attr_name, data_type = self.addr_map[addr]
            
            # 根据数据类型解析
            if data_type == 'h':  # short类型
                value = struct.unpack('<h', msg.data[:2])[0]
            else:  # float类型
                value = struct.unpack('<f', msg.data[:4])[0]
                
            return addr, value
            
        except Exception as e:
            print(f"解析消息失败: {str(e)}")
            return None, None
            
    def update_motor_data(self, addr: int, value: float) -> bool:
        """
        更新电机数据
        :param addr: 数据地址
        :param value: 数据值
        :return: 是否更新成功
        """
        try:
            if addr in self.addr_map:
                attr_name, _ = self.addr_map[addr]
                setattr(self.data, attr_name, value)
                return True
            return False
        except Exception as e:
            print(f"更新数据失败: {str(e)}")
            return False
    
    @abstractmethod
    def connect(self):
        """连接CAN总线"""
        pass
        
    @abstractmethod
    def disconnect(self):
        """断开CAN总线"""
        pass
        
    @abstractmethod
    def send(self, msg):
        """发送消息"""
        pass
        
    @abstractmethod
    def recv(self, timeout=None):
        """接收消息"""
        pass

class VirtualCANBus(CANBus):
    """虚拟CAN总线实现，包含数据模拟功能"""
    def __init__(self):
        super().__init__()
        self.queue = Queue()
        self.is_connected = False
        self.simulation_thread = None
        self.running = False
        
        # 模拟参数
        self.target_speed = 0.0
        self.current_speed = 0.0
        self.position = 0
        self.acceleration = 100  # rpm/s
        self.last_update = time.time()
        
    def connect(self):
        if not self.is_connected:
            self.is_connected = True
            self.start_simulation()
            print("虚拟CAN总线已连接")
            return True
        return False
        
    def disconnect(self):
        if self.is_connected:
            self.stop_simulation()
            self.is_connected = False
            print("虚拟CAN总线已断开")
            return True
        return False
        
    def send(self, msg):
        """处理控制命令"""
        if not self.is_connected:
            raise RuntimeError("CAN总线未连接")
            
        try:
            command = msg.data.decode('ascii').strip()
            
            if command.startswith("MOT ON"):
                self.start_simulation()
            elif command.startswith("MOT OFF"):
                self.stop_simulation()
            elif command.startswith("ACCE"):
                self.target_speed = min(3000, self.target_speed + 100)
            elif command.startswith("DECE"):
                self.target_speed = max(-3000, self.target_speed - 100)
            elif command.startswith("DIR POS"):
                self.target_speed = abs(self.target_speed)
            elif command.startswith("DIR NEG"):
                self.target_speed = -abs(self.target_speed)
            elif command.startswith("SPD"):
                try:
                    speed = float(command.split()[1])
                    self.target_speed = max(-3000, min(3000, speed))
                except:
                    pass
                    
            self.queue.put(msg)
            
        except Exception as e:
            print(f"处理控制命令失败: {str(e)}")
        
    def recv(self, timeout=None):
        if not self.is_connected:
            return None
        try:
            return self.queue.get(timeout=timeout if timeout else 0)
        except Empty:
            return None
            
    def start_simulation(self):
        """启动模拟器"""
        if not self.running:
            self.running = True
            self.simulation_thread = threading.Thread(target=self._simulation_loop)
            self.simulation_thread.daemon = True
            self.simulation_thread.start()
            
    def stop_simulation(self):
        """停止模拟器"""
        self.running = False
        if self.simulation_thread:
            self.simulation_thread.join()
            
    def _simulation_loop(self):
        """模拟数据生成循环"""
        while self.running:
            current_time = time.time()
            dt = current_time - self.last_update
            self.last_update = current_time
            
            # 更新速度
            if self.current_speed < self.target_speed:
                self.current_speed = min(self.target_speed, 
                                      self.current_speed + self.acceleration * dt)
            elif self.current_speed > self.target_speed:
                self.current_speed = max(self.target_speed, 
                                      self.current_speed - self.acceleration * dt)
                                      
            # 更新位置
            self.position = (self.position + int(self.current_speed * dt * 8192 / 60)) % 8192
            
            # 生成三相电流
            freq = self.current_speed * 2 * math.pi / 60  # 转速到角频率
            t = current_time
            amplitude = abs(self.current_speed) / 3000 * 10  # 最大电流10A
            
            ia = amplitude * math.sin(freq * t)
            ib = amplitude * math.sin(freq * t + 2 * math.pi / 3)
            ic = amplitude * math.sin(freq * t + 4 * math.pi / 3)
            
            # 更新数据
            self.update_motor_data(0x100, ia)
            self.update_motor_data(0x101, ib)
            self.update_motor_data(0x102, ic)
            self.update_motor_data(0x103, self.target_speed)
            self.update_motor_data(0x104, self.current_speed)
            self.update_motor_data(0x105, self.position)
            
            time.sleep(0.01)  # 100Hz更新频率

class RealCANBus(CANBus):
    """真实CAN总线实现"""
    def __init__(self, channel='PCAN_USBBUS1', bitrate=500000):
        super().__init__()
        self.channel = channel
        self.bitrate = bitrate
        self.bus = None
        self.is_connected = False
        
    def connect(self) -> bool:
        """连接CAN设备"""
        try:
            # 创建CAN总线对象，使用 PCAN-USB 驱动
            self.bus = Bus(
                channel=self.channel,
                bustype='pcan',  # Windows下使用PCAN驱动
                bitrate=self.bitrate
            )
            self.is_connected = True
            print(f"CAN总线已连接: {self.channel}")
            return True
        except Exception as e:
            print(f"CAN总线连接失败: {str(e)}")
            return False
            
    def disconnect(self) -> bool:
        """断开CAN连接"""
        if self.is_connected and self.bus:
            try:
                self.bus.shutdown()
                self.is_connected = False
                print("CAN总线已断开")
                return True
            except Exception as e:
                print(f"断开CAN总线失败: {str(e)}")
        return False
        
    def send(self, msg: Message) -> bool:
        """
        发送CAN消息
        :param msg: CAN消息对象
        :return: 是否发送成功
        """
        if not self.is_connected:
            raise RuntimeError("CAN总线未连接")
            
        try:
            self.bus.send(msg)
            return True
        except Exception as e:
            print(f"发送消息失败: {str(e)}")
            return False
            
    def recv(self, timeout: Optional[float] = 0.1) -> Optional[Message]:
        """
        接收CAN消息
        :param timeout: 超时时间(秒)
        :return: CAN消息对象或None
        """
        if not self.is_connected:
            return None
            
        try:
            msg = self.bus.recv(timeout=timeout)
            if msg:
                # 如果收到消息，自动解析并更新数据
                addr, value = self.parse_message(msg)
                if addr is not None and value is not None:
                    self.update_motor_data(addr, value)
            return msg
        except Exception as e:
            print(f"接收消息失败: {str(e)}")
            return None
            
    def send_control_command(self, cmd_type: int, value: float = 0.0) -> bool:
        """
        发送控制命令
        :param cmd_type: 命令类型
        :param value: 命令值
        :return: 是否发送成功
        """
        try:
            # 创建8字节数据
            data = bytearray(8)
            data[0] = cmd_type  # 命令类型占用第一个字节
            # 将float值打包到后续4个字节
            struct.pack_into('<f', data, 1, float(value))
            
            # 创建CAN消息
            msg = Message(
                arbitration_id=0x200,  # 控制命令ID
                data=data,
                is_extended_id=False,
                dlc=8
            )
            
            return self.send(msg)
            
        except Exception as e:
            print(f"发送控制命令失败: {str(e)}")
            return False 