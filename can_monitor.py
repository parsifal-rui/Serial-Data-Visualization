# can_simulator.py
import random
import time
from queue import Queue
import threading

class VirtualCANBus:
    def __init__(self):
        self.message_queue = Queue()
        self.connected = False
        
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

# can_monitor.py
import tkinter as tk
from tkinter import ttk, messagebox
import threading
import time
from datetime import datetime
from utils.constants import *

class CANMonitor:
    def __init__(self, root, can_bus):
        self.root = root
        self.root.title("CAN通信监控器")
        self.bus = can_bus
        self.is_running = False
        self.data_logger = None  # 可选的数据记录器
        
        # 创建主框架
        main_frame = ttk.Frame(root)
        main_frame.pack(padx=10, pady=10, fill=tk.BOTH, expand=True)
        
        # 连接按钮
        self.connect_btn = ttk.Button(main_frame, text="连接", command=self.toggle_connection)
        self.connect_btn.pack(pady=5)
        
        # 发送框架
        send_frame = ttk.LabelFrame(main_frame, text="发送数据")
        send_frame.pack(fill=tk.X, pady=5)
        
        # ID输入
        id_frame = ttk.Frame(send_frame)
        id_frame.pack(fill=tk.X, padx=5, pady=5)
        ttk.Label(id_frame, text="ID (hex):").pack(side=tk.LEFT)
        self.send_id = ttk.Entry(id_frame, width=10)
        self.send_id.insert(0, '123')
        self.send_id.pack(side=tk.LEFT, padx=5)
        
        # 数据输入
        data_frame = ttk.Frame(send_frame)
        data_frame.pack(fill=tk.X, padx=5, pady=5)
        ttk.Label(data_frame, text="数据 (hex):").pack(side=tk.LEFT)
        self.send_data = ttk.Entry(data_frame)
        self.send_data.insert(0, '11 22 33 44')
        self.send_data.pack(side=tk.LEFT, padx=5, fill=tk.X, expand=True)
        
        # 发送按钮
        self.send_btn = ttk.Button(send_frame, text="发送", command=self.send_message)
        self.send_btn.pack(pady=5)
        
        # 接收显示区域
        receive_frame = ttk.LabelFrame(main_frame, text="接收数据")
        receive_frame.pack(fill=tk.BOTH, expand=True, pady=5)
        
        # 创建表格显示
        columns = ('时间', 'ID', '数据', '解析值')
        self.tree = ttk.Treeview(receive_frame, columns=columns, show='headings')
        
        # 设置列标题
        for col in columns:
            self.tree.heading(col, text=col)
            self.tree.column(col, width=100)
        
        # 添加滚动条
        scrollbar = ttk.Scrollbar(receive_frame, orient="vertical", command=self.tree.yview)
        scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
        
        self.tree.pack(fill=tk.BOTH, expand=True)
        self.tree.configure(yscrollcommand=scrollbar.set)
        
        # 记录控制
        control_frame = ttk.Frame(main_frame)
        control_frame.pack(fill=tk.X, pady=5)
        
        self.record_btn = ttk.Button(control_frame, text="开始记录", command=self.toggle_recording)
        self.record_btn.pack(side=tk.LEFT, padx=5)
        
        self.export_btn = ttk.Button(control_frame, text="导出数据", command=self.export_data)
        self.export_btn.pack(side=tk.LEFT, padx=5)
        
        # 添加功能按钮
        button_frame = ttk.Frame(main_frame)
        button_frame.pack(fill=tk.X, pady=5)
        
        ttk.Button(button_frame, text="波形显示", 
                   command=self.show_plot_window).pack(side=tk.LEFT, padx=5)
        ttk.Button(button_frame, text="参数配置", 
                   command=self.show_config_window).pack(side=tk.LEFT, padx=5)
        ttk.Button(button_frame, text="电机控制", 
                   command=self.show_control_window).pack(side=tk.LEFT, padx=5)

    def set_data_logger(self, logger):
        """设置数据记录器"""
        self.data_logger = logger

    def toggle_connection(self):
        """切换连接状态"""
        if not self.is_running:
            if self.bus:
                self.is_running = True
                self.bus.connected = True
                self.connect_btn.config(text="断开")
                # 启动接收线程
                self.receive_thread = threading.Thread(target=self.receive_messages)
                self.receive_thread.daemon = True
                self.receive_thread.start()
        else:
            self.is_running = False
            if self.bus:
                self.bus.connected = False
            self.connect_btn.config(text="连接")

    def send_message(self):
        """发送CAN消息"""
        if not self.bus or not self.bus.connected:
            messagebox.showerror("错误", "请先连接CAN设备")
            return
            
        try:
            # 解析ID和数据
            msg_id = int(self.send_id.get(), 16)
            data = [int(x, 16) for x in self.send_data.get().split()]
            
            # 创建并发送消息
            msg = VirtualCANMessage(
                arbitration_id=msg_id,
                data=data
            )
            self.bus.send(msg)
        except Exception as e:
            messagebox.showerror("错误", f"发送失败: {str(e)}")

    def receive_messages(self):
        """接收CAN消息的线程函数"""
        while self.is_running:
            if self.bus and self.bus.connected:
                msg = self.bus.recv(timeout=0.1)
                if msg:
                    # 在GUI线程中更新显示
                    self.root.after(0, self.update_display, msg)

    def parse_message(self, msg):
        """解析CAN消息内容"""
        if msg.arbitration_id == CAN_ID_CURRENT:
            current_a = int.from_bytes(msg.data[0:2], byteorder='little', signed=True) / 10
            current_b = int.from_bytes(msg.data[2:4], byteorder='little', signed=True) / 10
            current_c = int.from_bytes(msg.data[4:6], byteorder='little', signed=True) / 10
            return f"Ia={current_a:.1f}A, Ib={current_b:.1f}A, Ic={current_c:.1f}A"
            
        elif msg.arbitration_id == CAN_ID_VOLTAGE:
            voltage_a = int.from_bytes(msg.data[0:2], byteorder='little', signed=False) / 10
            voltage_b = int.from_bytes(msg.data[2:4], byteorder='little', signed=False) / 10
            voltage_c = int.from_bytes(msg.data[4:6], byteorder='little', signed=False) / 10
            temp = int.from_bytes(msg.data[6:8], byteorder='little', signed=True) / 10
            return f"Va={voltage_a:.1f}V, Vb={voltage_b:.1f}V, Vc={voltage_c:.1f}V, T={temp:.1f}°C"
            
        elif msg.arbitration_id == CAN_ID_SPEED:
            actual_speed = int.from_bytes(msg.data[0:2], byteorder='little', signed=True)
            target_speed = int.from_bytes(msg.data[2:4], byteorder='little', signed=True)
            torque_current = int.from_bytes(msg.data[4:6], byteorder='little', signed=True) / 10
            return f"Speed={actual_speed}rpm, Target={target_speed}rpm, Torque={torque_current:.1f}A"
            
        return "Unknown message"

    def update_display(self, msg):
        """更新显示接收到的消息"""
        time_str = datetime.now().strftime('%H:%M:%S.%f')[:-3]
        data_str = ' '.join(f'{b:02X}' for b in msg.data)
        parsed_str = self.parse_message(msg)
        
        self.tree.insert('', 0, values=(time_str, f'{msg.arbitration_id:X}', data_str, parsed_str))
        
        # 更新波形显示
        if hasattr(self, 'plot_window') and self.plot_window.window.winfo_exists():
            self.plot_window.update_plot(msg.timestamp, msg.arbitration_id, msg.data)
        
        # 如果有数据记录器，记录数据
        if self.data_logger and self.data_logger.recording:
            self.data_logger.add_message(msg, parsed_str)

    def toggle_recording(self):
        """切换记录状态"""
        if self.data_logger:
            if not self.data_logger.recording:
                self.data_logger.start_recording()
                self.record_btn.config(text="停止记录")
            else:
                self.data_logger.stop_recording()
                self.record_btn.config(text="开始记录")

    def export_data(self):
        """导出记录的数据"""
        if self.data_logger:
            try:
                filename = f"motor_data_{datetime.now().strftime('%Y%m%d_%H%M%S')}.csv"
                self.data_logger.export_csv(time.time()-3600, time.time(), filename)
                messagebox.showinfo("成功", f"数据已导出到 {filename}")
            except Exception as e:
                messagebox.showerror("错误", f"导出失败: {str(e)}")

    def show_plot_window(self):
        """显示波形窗口"""
        from gui.plot_window import PlotWindow
        if not hasattr(self, 'plot_window') or not self.plot_window.window.winfo_exists():
            self.plot_window = PlotWindow(self.root)
        
    def show_config_window(self):
        """显示配置窗口"""
        from gui.config_window import ConfigWindow
        if not hasattr(self, 'config_window') or not self.config_window.window.winfo_exists():
            self.config_window = ConfigWindow(self.root)
        
    def show_control_window(self):
        """显示控制窗口"""
        from gui.control_window import ControlWindow
        if not hasattr(self, 'control_window') or not self.control_window.window.winfo_exists():
            self.control_window = ControlWindow(self.root, self.bus)

if __name__ == '__main__':
    root = tk.Tk()
    # 创建真实CAN设备或虚拟CAN总线
    from can_simulator import VirtualCANBus, MotorSimulator
    bus = VirtualCANBus()
    simulator = MotorSimulator(bus)
    
    # 创建数据记录器
    from data_logger import DataLogger
    logger = DataLogger()
    
    # 创建监控器
    app = CANMonitor(root, bus)
    app.set_data_logger(logger)
    
    # 启动模拟器
    simulator.start_simulation()
    
    root.mainloop()