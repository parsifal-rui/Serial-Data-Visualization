import tkinter as tk
from tkinter import ttk
from utils.constants import *

class ControlWindow:
    def __init__(self, parent, can_bus):
        self.window = tk.Toplevel(parent)
        self.window.title("电机控制")
        self.window.geometry("400x600")
        self.can_bus = can_bus
        
        # 创建notebook用于分页显示
        self.notebook = ttk.Notebook(self.window)
        self.notebook.pack(fill=tk.BOTH, expand=True, padx=5, pady=5)
        
        # 基本控制页
        self.basic_frame = ttk.Frame(self.notebook)
        self.notebook.add(self.basic_frame, text="基本控制")
        self.setup_basic_control()
        
        # 运动控制页
        self.motion_frame = ttk.Frame(self.notebook)
        self.notebook.add(self.motion_frame, text="运动控制")
        self.setup_motion_control()
        
        # 诊断功能页
        self.diagnostic_frame = ttk.Frame(self.notebook)
        self.notebook.add(self.diagnostic_frame, text="诊断功能")
        self.setup_diagnostic()
        
    def setup_basic_control(self):
        """基本控制界面"""
        # 运行模式选择
        mode_frame = ttk.LabelFrame(self.basic_frame, text="运行模式")
        mode_frame.pack(fill=tk.X, padx=5, pady=5)
        
        self.mode_var = tk.StringVar(value="speed")
        ttk.Radiobutton(mode_frame, text="速度模式", variable=self.mode_var, 
                       value="speed").pack(side=tk.LEFT, padx=5)
        ttk.Radiobutton(mode_frame, text="位置模式", variable=self.mode_var, 
                       value="position").pack(side=tk.LEFT, padx=5)
        ttk.Radiobutton(mode_frame, text="转矩模式", variable=self.mode_var, 
                       value="torque").pack(side=tk.LEFT, padx=5)
        
        # 控制命令
        cmd_frame = ttk.LabelFrame(self.basic_frame, text="控制命令")
        cmd_frame.pack(fill=tk.X, padx=5, pady=5)
        
        ttk.Button(cmd_frame, text="使能", command=self.enable_motor).pack(fill=tk.X, padx=5, pady=2)
        ttk.Button(cmd_frame, text="断使能", command=self.disable_motor).pack(fill=tk.X, padx=5, pady=2)
        ttk.Button(cmd_frame, text="清除故障", command=self.clear_fault).pack(fill=tk.X, padx=5, pady=2)
        
        # 速度控制
        speed_frame = ttk.LabelFrame(self.basic_frame, text="速度控制")
        speed_frame.pack(fill=tk.X, padx=5, pady=5)
        
        ttk.Label(speed_frame, text="目标速度 (rpm):").pack(side=tk.LEFT, padx=5)
        self.target_speed = ttk.Entry(speed_frame, width=10)
        self.target_speed.pack(side=tk.LEFT, padx=5)
        self.target_speed.insert(0, "0")
        ttk.Button(speed_frame, text="设置", command=self.set_speed).pack(side=tk.LEFT, padx=5)
        
    def setup_motion_control(self):
        """运动控制界面"""
        # 点动控制
        jog_frame = ttk.LabelFrame(self.motion_frame, text="点动控制")
        jog_frame.pack(fill=tk.X, padx=5, pady=5)
        
        ttk.Button(jog_frame, text="正向点动", command=lambda: self.jog_move(1)).pack(side=tk.LEFT, padx=5)
        ttk.Button(jog_frame, text="停止", command=self.stop_move).pack(side=tk.LEFT, padx=5)
        ttk.Button(jog_frame, text="反向点动", command=lambda: self.jog_move(-1)).pack(side=tk.LEFT, padx=5)
        
        # 位置控制
        pos_frame = ttk.LabelFrame(self.motion_frame, text="位置控制")
        pos_frame.pack(fill=tk.X, padx=5, pady=5)
        
        ttk.Label(pos_frame, text="目标位置:").grid(row=0, column=0, padx=5, pady=2)
        self.target_position = ttk.Entry(pos_frame, width=10)
        self.target_position.grid(row=0, column=1, padx=5, pady=2)
        self.target_position.insert(0, "0")
        
        ttk.Label(pos_frame, text="速度:").grid(row=1, column=0, padx=5, pady=2)
        self.move_speed = ttk.Entry(pos_frame, width=10)
        self.move_speed.grid(row=1, column=1, padx=5, pady=2)
        self.move_speed.insert(0, "1000")
        
        ttk.Button(pos_frame, text="移动", command=self.move_to_position).grid(row=2, column=0, columnspan=2, pady=5)
        
    def setup_diagnostic(self):
        """诊断功能界面"""
        # 自学习
        ttk.Button(self.diagnostic_frame, text="电机参数自学习", 
                  command=self.auto_tuning).pack(fill=tk.X, padx=5, pady=5)
        
        # 惯量识别
        ttk.Button(self.diagnostic_frame, text="惯量识别", 
                  command=self.inertia_identification).pack(fill=tk.X, padx=5, pady=5)
        
        # 共振检测
        ttk.Button(self.diagnostic_frame, text="共振频率检测", 
                  command=self.resonance_detection).pack(fill=tk.X, padx=5, pady=5)
        
    def enable_motor(self):
        """使能电机"""
        msg = VirtualCANMessage(
            arbitration_id=CAN_ID_CONTROL,
            data=[CMD_START, 0, 0, 0, 0, 0, 0, 0]
        )
        self.can_bus.send(msg)
        
    def disable_motor(self):
        """断使能电机"""
        msg = VirtualCANMessage(
            arbitration_id=CAN_ID_CONTROL,
            data=[CMD_STOP, 0, 0, 0, 0, 0, 0, 0]
        )
        self.can_bus.send(msg)
        
    def clear_fault(self):
        """清除故障"""
        msg = VirtualCANMessage(
            arbitration_id=CAN_ID_CONTROL,
            data=[CMD_CLEAR_FAULT, 0, 0, 0, 0, 0, 0, 0]
        )
        self.can_bus.send(msg)
        
    def set_speed(self):
        """设置速度"""
        try:
            speed = int(self.target_speed.get())
            msg = VirtualCANMessage(
                arbitration_id=CAN_ID_CONTROL,
                data=[CMD_SPEED, 0, speed & 0xFF, (speed >> 8) & 0xFF, 0, 0, 0, 0]
            )
            self.can_bus.send(msg)
        except ValueError:
            pass
            
    def jog_move(self, direction):
        """点动运行"""
        speed = 500 if direction > 0 else -500  # 点动速度500rpm
        msg = VirtualCANMessage(
            arbitration_id=CAN_ID_CONTROL,
            data=[CMD_JOG, 0, speed & 0xFF, (speed >> 8) & 0xFF, 0, 0, 0, 0]
        )
        self.can_bus.send(msg)
        
    def stop_move(self):
        """停止运动"""
        self.set_speed()  # 设置速度为0
        
    def move_to_position(self):
        """位置控制"""
        try:
            position = int(self.target_position.get())
            speed = int(self.move_speed.get())
            msg = VirtualCANMessage(
                arbitration_id=CAN_ID_CONTROL,
                data=[CMD_POSITION, 0, 
                      position & 0xFF, (position >> 8) & 0xFF,
                      speed & 0xFF, (speed >> 8) & 0xFF,
                      0, 0]
            )
            self.can_bus.send(msg)
        except ValueError:
            pass
            
    def auto_tuning(self):
        """电机参数自学习"""
        msg = VirtualCANMessage(
            arbitration_id=CAN_ID_CONTROL,
            data=[CMD_AUTO_TUNING, 0, 0, 0, 0, 0, 0, 0]
        )
        self.can_bus.send(msg)
        
    def inertia_identification(self):
        """惯量识别"""
        msg = VirtualCANMessage(
            arbitration_id=CAN_ID_CONTROL,
            data=[CMD_INERTIA_ID, 0, 0, 0, 0, 0, 0, 0]
        )
        self.can_bus.send(msg)
        
    def resonance_detection(self):
        """共振检测"""
        msg = VirtualCANMessage(
            arbitration_id=CAN_ID_CONTROL,
            data=[CMD_RESONANCE_DET, 0, 0, 0, 0, 0, 0, 0]
        )
        self.can_bus.send(msg) 