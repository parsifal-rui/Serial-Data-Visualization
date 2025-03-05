import can
import struct

class DataReceiver:
    def __init__(self):
        # 存储最新数据
        self.speed = 0.0
        self.position = 0.0
        
        # ID映射表
        self.handlers = {
            0x100: self.handle_speed,
            0x101: self.handle_position
        }
    
    def handle_speed(self, data):
        """处理速度数据"""
        self.speed = struct.unpack('<f', data)[0]
        print(f"Speed: {self.speed:.2f}")
    
    def handle_position(self, data):
        """处理位置数据"""
        self.position = struct.unpack('<f', data)[0]
        print(f"Position: {self.position:.2f}")
    
    def process_message(self, msg):
        """处理接收到的CAN消息"""
        if msg.arbitration_id in self.handlers:
            self.handlers[msg.arbitration_id](msg.data)
    
    def start(self):
        """启动接收"""
        bus = can.interface.Bus(channel='can0', bustype='socketcan')
        
        # 设置过滤器，只接收关心的ID
        filters = [
            {"can_id": 0x100, "can_mask": 0x7FF, "extended": False},
            {"can_id": 0x101, "can_mask": 0x7FF, "extended": False}
        ]
        bus.set_filters(filters)
        
        while True:
            try:
                msg = bus.recv()
                self.process_message(msg)
            except Exception as e:
                print(f"Error: {e}")

# 使用示例
if __name__ == "__main__":
    receiver = DataReceiver()
    receiver.start()