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
        self.target_speed = 0
        self.actual_speed = 0
        self.mode = MODE_SPEED
        self.temperature = 25.0
        
        # 模拟参数
        self.speed_ramp = 100  # rpm/s
        self.temp_rise = 0.1   # ℃/s
        
        # 故障模拟
        self.fault_timer = None
        self.fault_type = FAULT_NONE
        
    def start_simulation(self):
        self.running = True
        threading.Thread(target=self._simulation_loop, daemon=True).start()
        
    def stop_simulation(self):
        self.running = False
        
    def set_target_speed(self, speed):
        self.target_speed = min(max(speed, -MAX_SPEED), MAX_SPEED)
        
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
        last_time = time.time()
        
        while self.running:
            current_time = time.time()
            dt = current_time - last_time
            last_time = current_time
            
            # 更新速度
            if self.fault_type == FAULT_NONE:
                speed_diff = self.target_speed - self.actual_speed
                speed_change = min(abs(speed_diff), self.speed_ramp * dt)
                if speed_diff > 0:
                    self.actual_speed += speed_change
                else:
                    self.actual_speed -= speed_change
                    
                # 更新温度
                if abs(self.actual_speed) > 0:
                    self.temperature += self.temp_rise * dt * (abs(self.actual_speed)/MAX_SPEED)
                else:
                    self.temperature = max(25.0, self.temperature - self.temp_rise * dt)
                    
            else:
                # 故障状态下速度快速降为0
                self.actual_speed = max(0, abs(self.actual_speed) - MAX_SPEED * dt)
                
            # 生成三相电流
            phase_angle = (current_time * self.actual_speed * 6 / 60) % (2 * 3.14159)
            current_a = 20 * math.sin(phase_angle)
            current_b = 20 * math.sin(phase_angle + 2.0944)  # 120°
            current_c = 20 * math.sin(phase_angle + 4.1888)  # 240°
            
            # 添加随机波动
            current_a += random.uniform(-1, 1)
            current_b += random.uniform(-1, 1)
            current_c += random.uniform(-1, 1)
            
            # 发送电流数据
            current_data = []
            for current in [current_a, current_b, current_c]:
                value = int(current * 10)  # 转换为0.1A单位
                current_data.extend([value & 0xFF, (value >> 8) & 0xFF])
            current_data.extend([self.fault_type & 0xFF, (self.fault_type >> 8) & 0xFF])
            
            self.can_bus.send(VirtualCANMessage(CAN_ID_CURRENT, current_data))
            
            # 发送电压数据
            voltage_base = 220  # 基准电压
            voltage_a = voltage_base + random.uniform(-5, 5)
            voltage_b = voltage_base + random.uniform(-5, 5)
            voltage_c = voltage_base + random.uniform(-5, 5)
            
            voltage_data = []
            for voltage in [voltage_a, voltage_b, voltage_c]:
                value = int(voltage * 10)  # 转换为0.1V单位
                voltage_data.extend([value & 0xFF, (value >> 8) & 0xFF])
                
            temp_value = int(self.temperature * 10)  # 转换为0.1℃单位
            voltage_data.extend([temp_value & 0xFF, (temp_value >> 8) & 0xFF])
            
            self.can_bus.send(VirtualCANMessage(CAN_ID_VOLTAGE, voltage_data))
            
            # 发送速度数据
            speed_data = []
            for value in [int(self.actual_speed), int(self.target_speed)]:
                speed_data.extend([value & 0xFF, (value >> 8) & 0xFF])
            
            torque_current = int(abs(current_a) * 10)  # 简化的转矩电流计算
            speed_data.extend([torque_current & 0xFF, (torque_current >> 8) & 0xFF])
            speed_data.extend([self.mode & 0xFF, 0x00])
            
            self.can_bus.send(VirtualCANMessage(CAN_ID_SPEED, speed_data))
            
            time.sleep(0.01)  # 提高到100Hz更新率 