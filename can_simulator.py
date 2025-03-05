import random
import time
from queue import Queue, Empty
import math
import threading
from utils.constants import *
import struct
import numpy as np
from typing import Optional
from dataclasses import dataclass
from can_constants import *  # 导入所有 CAN 常量

@dataclass
class MotorData:
    """电机数据结构"""
    ia: float = 0.0
    ib: float = 0.0
    ic: float = 0.0
    id: float = 0.0
    iq: float = 0.0
    speed_ref: float = 0.0
    speed_fed: float = 0.0
    position: int = 0

@dataclass
class VirtualCANMessage:
    """虚拟CAN消息类"""
    arbitration_id: int
    data: bytes
    dlc: int = 8
    is_extended_id: bool = False
    
    def __init__(self, arbitration_id: int, data: bytes, dlc: int = 8, is_extended_id: bool = False):
        self.arbitration_id = arbitration_id
        self.data = data
        self.dlc = dlc
        self.is_extended_id = is_extended_id
        
        # 根据消息ID进行数据验证
        if arbitration_id == CAN_ID_CONTROL:
            if len(data) < 5:  # 至少需要5字节：1字节命令类型 + 4字节浮点数
                raise ValueError("控制命令数据长度不足")
        else:
            if len(data) < 4:  # 其他消息至少需要4字节数据
                raise ValueError("数据长度不足")

class VirtualCANBus:
    def __init__(self):
        self.queue = Queue()
        self.is_connected = False
        
        # 初始化电机数据
        self.data = MotorData()
        
        # 地址映射
        self.addr_map = {
            CAN_ID_IA: ('ia', 'f'),        # Ia 电流
            CAN_ID_IB: ('ib', 'f'),        # Ib 电流
            CAN_ID_IC: ('ic', 'f'),        # Ic 电流
            CAN_ID_ID: ('id', 'f'),        # Id 电流
            CAN_ID_IQ: ('iq', 'f'),        # Iq 电流
            CAN_ID_SPEED_REF: ('speed_ref', 'f'),  # 速度参考值
            CAN_ID_SPEED_FED: ('speed_fed', 'f'),  # 速度反馈值
            CAN_ID_POSITION: ('position', 'h')      # 位置反馈值
        }
        
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
            
    def parse_message(self, msg: VirtualCANMessage) -> tuple[Optional[int], Optional[float]]:
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

class MotorSimulator:
    def __init__(self, can_bus):
        self.can_bus = can_bus
        self.running = False
        
        # 基本参数
        self.phase = 0
        self.speed_ref = 0
        self.speed_actual = 0
        self.position = 0
        
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
        """模拟生成电机数据"""
        while True:
            # 模拟电流数据
            ia = random.uniform(-10, 10)
            ib = random.uniform(-10, 10)
            ic = random.uniform(-10, 10)
            id = random.uniform(-10, 10)
            iq = random.uniform(-10, 10)
            
            # 模拟速度和位置数据
            speed_ref = 1000 * math.sin(time.time())
            speed_fed = speed_ref + random.uniform(-50, 50)
            position = int(1000 * math.sin(time.time() / 2))
            
            # 发送各个数据
            messages = [
                (CAN_ID_IA, ia),
                (CAN_ID_IB, ib),
                (CAN_ID_IC, ic),
                (CAN_ID_ID, id),
                (CAN_ID_IQ, iq),
                (CAN_ID_SPEED_REF, speed_ref),
                (CAN_ID_SPEED_FED, speed_fed),
                (CAN_ID_POSITION, position)
            ]
            
            for msg_id, value in messages:
                # 创建数据包
                if msg_id == CAN_ID_POSITION:
                    # 位置数据使用 short 类型
                    data = bytearray(8)
                    struct.pack_into('<h', data, 0, int(value))
                else:
                    # 其他数据使用 float 类型
                    data = bytearray(8)
                    struct.pack_into('<f', data, 0, float(value))
                
                # 创建并发送消息
                msg = VirtualCANMessage(
                    arbitration_id=msg_id,
                    data=data
                )
                self.can_bus.send(msg)
            
            # 控制发送频率
            time.sleep(0.01)  # 100Hz 