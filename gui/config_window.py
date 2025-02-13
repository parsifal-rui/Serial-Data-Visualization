import tkinter as tk
from tkinter import ttk
import json
from utils.constants import *

class ConfigWindow:
    def __init__(self, parent, config_file='config.json'):
        self.window = tk.Toplevel(parent)
        self.window.title("参数配置")
        self.window.geometry("600x400")
        self.config_file = config_file
        
        # 创建notebook用于分页显示
        self.notebook = ttk.Notebook(self.window)
        self.notebook.pack(fill=tk.BOTH, expand=True, padx=5, pady=5)
        
        # 报警配置页
        self.alarm_frame = ttk.Frame(self.notebook)
        self.notebook.add(self.alarm_frame, text="报警配置")
        self.setup_alarm_config()
        
        # 电机参数页
        self.motor_frame = ttk.Frame(self.notebook)
        self.notebook.add(self.motor_frame, text="电机参数")
        self.setup_motor_config()
        
        # 控制参数页
        self.control_frame = ttk.Frame(self.notebook)
        self.notebook.add(self.control_frame, text="控制参数")
        self.setup_control_config()
        
        # 保存按钮
        self.save_btn = ttk.Button(self.window, text="保存配置", command=self.save_config)
        self.save_btn.pack(pady=5)
        
        # 加载配置
        self.load_config()
        
    def setup_alarm_config(self):
        """设置报警配置界面"""
        # 过流保护
        ttk.Label(self.alarm_frame, text="过流保护值 (A):").grid(row=0, column=0, padx=5, pady=5)
        self.over_current = ttk.Entry(self.alarm_frame)
        self.over_current.grid(row=0, column=1, padx=5, pady=5)
        self.over_current.insert(0, "200")
        
        # 过压保护
        ttk.Label(self.alarm_frame, text="过压保护值 (V):").grid(row=1, column=0, padx=5, pady=5)
        self.over_voltage = ttk.Entry(self.alarm_frame)
        self.over_voltage.grid(row=1, column=1, padx=5, pady=5)
        self.over_voltage.insert(0, "400")
        
        # 过温保护
        ttk.Label(self.alarm_frame, text="过温保护值 (℃):").grid(row=2, column=0, padx=5, pady=5)
        self.over_temp = ttk.Entry(self.alarm_frame)
        self.over_temp.grid(row=2, column=1, padx=5, pady=5)
        self.over_temp.insert(0, "85")
        
    def setup_motor_config(self):
        """设置电机参数配置界面"""
        # 额定功率
        ttk.Label(self.motor_frame, text="额定功率 (kW):").grid(row=0, column=0, padx=5, pady=5)
        self.rated_power = ttk.Entry(self.motor_frame)
        self.rated_power.grid(row=0, column=1, padx=5, pady=5)
        
        # 额定转速
        ttk.Label(self.motor_frame, text="额定转速 (rpm):").grid(row=1, column=0, padx=5, pady=5)
        self.rated_speed = ttk.Entry(self.motor_frame)
        self.rated_speed.grid(row=1, column=1, padx=5, pady=5)
        
        # 编码器分辨率
        ttk.Label(self.motor_frame, text="编码器分辨率:").grid(row=2, column=0, padx=5, pady=5)
        self.encoder_resolution = ttk.Entry(self.motor_frame)
        self.encoder_resolution.grid(row=2, column=1, padx=5, pady=5)
        
    def setup_control_config(self):
        """设置控制参数配置界面"""
        # 速度环PID参数
        ttk.Label(self.control_frame, text="速度环参数:").grid(row=0, column=0, columnspan=2, pady=10)
        ttk.Label(self.control_frame, text="Kp:").grid(row=1, column=0, padx=5, pady=5)
        self.speed_kp = ttk.Entry(self.control_frame, width=10)
        self.speed_kp.grid(row=1, column=1, padx=5, pady=5)
        
        ttk.Label(self.control_frame, text="Ki:").grid(row=2, column=0, padx=5, pady=5)
        self.speed_ki = ttk.Entry(self.control_frame, width=10)
        self.speed_ki.grid(row=2, column=1, padx=5, pady=5)
        
        ttk.Label(self.control_frame, text="Kd:").grid(row=3, column=0, padx=5, pady=5)
        self.speed_kd = ttk.Entry(self.control_frame, width=10)
        self.speed_kd.grid(row=3, column=1, padx=5, pady=5) 