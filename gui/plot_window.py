import tkinter as tk
from tkinter import ttk
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
import numpy as np
from collections import deque
from utils.constants import *
import matplotlib
import time

# 设置中文字体
try:
    # 优先使用微软雅黑
    matplotlib.rc('font', family='Microsoft YaHei')
except:
    try:
        # 如果没有微软雅黑，尝试使用其他中文字体
        matplotlib.rc('font', family=['SimHei', 'SimSun', 'Arial Unicode MS'])
    except:
        print("警告：未找到中文字体，图表中文可能无法正常显示")

# 解决负号显示问题
matplotlib.rcParams['axes.unicode_minus'] = False

class PlotWindow:
    def __init__(self, parent):
        self.window = tk.Toplevel(parent)
        self.window.title("实时波形显示")
        self.window.geometry("1200x800")
        
        # 创建图表
        self.fig = Figure(figsize=(12, 10))
        
        # 修改网格布局为2x3
        gs = self.fig.add_gridspec(2, 3, width_ratios=[2, 1, 1], hspace=0.3, wspace=0.3)
        
        # 左列放置波形图(占2格)
        self.ax_current = self.fig.add_subplot(gs[0, 0])
        self.ax_speed = self.fig.add_subplot(gs[1, 0])
        
        # 中列放置位置极坐标图(占2格)
        self.ax_position = self.fig.add_subplot(gs[:, 1], projection='polar')
        
        # 右列放置仪表盘(速度和功率)
        self.ax_speed_gauge = self.fig.add_subplot(gs[0, 2], projection='polar')
        self.ax_power_gauge = self.fig.add_subplot(gs[1, 2], projection='polar')
        
        # 配置速度仪表盘
        self.ax_speed_gauge.set_title("速度仪表盘")
        self._setup_gauge(self.ax_speed_gauge, -6000, 6000, "转速(rpm)")
        
        # 配置功率仪表盘
        self.ax_power_gauge.set_title("功率仪表盘")
        self._setup_gauge(self.ax_power_gauge, 0, 3000, "功率(W)")
        
        # 所有直角坐标图添加网格和标签
        for ax in [self.ax_current, self.ax_speed]:
            ax.grid(True, linestyle='--', alpha=0.7)
            ax.set_xlabel("采样点")
        
        # 创建画布
        self.canvas = FigureCanvasTkAgg(self.fig, master=self.window)
        self.canvas.draw()
        self.canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=1)
        
        # 修改数据缓存大小和更新频率
        self.data_len = 200  # 显示更多数据点
        self.update_interval = 100  # 每100ms更新一次
        self.last_update = 0
        
        # 添加时间轴
        self.time_data = deque(maxlen=self.data_len)
        
        # 数据缓存
        self.current_a = deque(maxlen=self.data_len)
        self.current_b = deque(maxlen=self.data_len)
        self.current_c = deque(maxlen=self.data_len)
        self.speed = deque(maxlen=self.data_len)
        self.speed_ref = deque(maxlen=self.data_len)
        self.position_data = deque(maxlen=self.data_len)
        
        # 图表线条
        self.lines = {}
        
        # 添加暂停按钮
        self.paused = False
        self.pause_btn = ttk.Button(self.window, text="暂停", command=self.toggle_pause)
        self.pause_btn.pack(side=tk.BOTTOM, pady=5)
        
        # 设置Y轴范围
        self.ax_current.set_ylim(-30, 30)  # 根据实际电流范围调整
        self.ax_speed.set_ylim(-6000, 6000)  # 根据实际转速范围调整
        
        # 修改速度图表显示
        if not self.lines.get('speed'):
            self.lines['speed'] = []
            self.lines['speed'].append(self.ax_speed.plot([], [], 'r-', label='实际速度')[0])
            self.lines['speed'].append(self.ax_speed.plot([], [], 'g--', label='目标速度')[0])
            self.ax_speed.legend(loc='upper right')
        
    def toggle_pause(self):
        """切换暂停/继续状态"""
        self.paused = not self.paused
        self.pause_btn.config(text="继续" if self.paused else "暂停")
        
    def update_plot(self, msg_time, msg_id, data):
        """更新图表数据"""
        if self.paused:
            return
            
        current_time = time.time()
        if current_time - self.last_update < self.update_interval/1000:
            return
        
        self.last_update = current_time
        self.time_data.append(msg_time)
        
        try:
            import struct
            data_bytes = bytes(data)
            
            if msg_id == CAN_ID_CURRENT:
                # 解析三相电流
                ia = struct.unpack('<f', data_bytes[0:4])[0]
                ib = struct.unpack('<f', data_bytes[4:8])[0]
                ic = struct.unpack('<f', data_bytes[8:12])[0]
                
                self.current_a.append(ia)
                self.current_b.append(ib)
                self.current_c.append(ic)
                
                # 更新电流图表
                if not self.lines.get('current'):
                    self.lines['current'] = []
                    self.lines['current'].append(self.ax_current.plot([], [], 'r-', label='A相')[0])
                    self.lines['current'].append(self.ax_current.plot([], [], 'g-', label='B相')[0])
                    self.lines['current'].append(self.ax_current.plot([], [], 'b-', label='C相')[0])
                    self.ax_current.legend(loc='upper right')
                
                x_data = list(range(len(self.current_a)))
                for i, line in enumerate([self.current_a, self.current_b, self.current_c]):
                    self.lines['current'][i].set_data(x_data, line)
                
                self.ax_current.relim()
                self.ax_current.autoscale_view()
                
                # 计算功率
                speed = self.speed[-1] if len(self.speed) > 0 else 0
                power = abs(speed * 2 * np.pi / 60) * (abs(ia) + abs(ib) + abs(ic))/3 * 48  # 假设48V电压
                self._update_gauge(self.ax_power_gauge, power, 0, 3000)
            
            elif msg_id == CAN_ID_SPEED:
                # 解析速度数据
                speed_ref = struct.unpack('<f', data_bytes[0:4])[0]
                speed_actual = struct.unpack('<f', data_bytes[4:8])[0]
                
                self.speed.append(speed_actual)
                self.speed_ref.append(speed_ref)
                
                # 更新速度图表
                if not self.lines.get('speed'):
                    self.lines['speed'] = []
                    self.lines['speed'].append(self.ax_speed.plot([], [], 'r-', label='实际速度')[0])
                    self.lines['speed'].append(self.ax_speed.plot([], [], 'g--', label='目标速度')[0])
                    self.ax_speed.legend(loc='upper right')
                
                x_data = list(range(len(self.speed)))
                self.lines['speed'][0].set_data(x_data, self.speed)
                self.lines['speed'][1].set_data(x_data, self.speed_ref)
                self.ax_speed.relim()
                self.ax_speed.autoscale_view()
                
                # 更新速度仪表盘
                self._update_gauge(self.ax_speed_gauge, speed_actual, -6000, 6000)
            
            elif msg_id == CAN_ID_POSITION:
                # 解析位置数据
                position = struct.unpack('<f', data_bytes[0:4])[0]
                angle = position * 360.0 / 8192
                angle_rad = np.deg2rad(angle)
                
                if not self.lines.get('position'):
                    # 创建指针线和圆弧
                    self.lines['position'] = []
                    self.lines['position'].append(self.ax_position.plot([0, angle_rad], [0, 1], 'r-', lw=2)[0])  # 指针
                    theta = np.linspace(0, angle_rad, 100)
                    self.lines['position'].append(self.ax_position.plot(theta, [0.8]*len(theta), 'b-', alpha=0.3)[0])  # 圆弧
                
                else:
                    # 更新指针和圆弧
                    self.lines['position'][0].set_data([0, angle_rad], [0, 1])
                    theta = np.linspace(0, angle_rad, 100)
                    self.lines['position'][1].set_data(theta, [0.8]*len(theta))
            
            # 减少重绘频率
            self.canvas.draw_idle()
        except Exception as e:
            print(f"波形更新错误: {str(e)}") 

    def _setup_gauge(self, ax, min_val, max_val, label):
        """设置仪表盘样式"""
        # 设置角度范围(-30到210度,转换为弧度)
        ax.set_thetamin(-30)
        ax.set_thetamax(210)
        
        # 设置半径范围
        ax.set_rmin(0)
        ax.set_rmax(1)
        
        # 计算刻度位置
        angles = np.linspace(-30, 210, 9) * np.pi/180
        labels = np.linspace(min_val, max_val, 9, dtype=int)
        
        # 设置刻度
        ax.set_xticks(angles)
        ax.set_xticklabels(labels)
        
        # 添加标签
        ax.text(0, -0.2, label, ha='center', va='center', transform=ax.transAxes)
        
        # 隐藏r轴刻度
        ax.set_rticks([])
        
        # 添加网格
        ax.grid(True, alpha=0.3)

    def _update_gauge(self, ax, value, min_val, max_val, color='r'):
        """更新仪表盘指针"""
        # 清除旧的指针
        if hasattr(self, f'{ax.get_label()}_pointer'):
            getattr(self, f'{ax.get_label()}_pointer').remove()
        
        # 计算角度(-30到210度映射到值的范围)
        angle = -30 + (value - min_val) * 240 / (max_val - min_val)
        angle_rad = np.deg2rad(angle)
        
        # 画指针
        pointer = ax.plot([0, angle_rad], [0, 0.8], color=color, lw=3)[0]
        setattr(self, f'{ax.get_label()}_pointer', pointer)
        
        # 添加数值显示
        if hasattr(self, f'{ax.get_label()}_text'):
            getattr(self, f'{ax.get_label()}_text').remove()
        text = ax.text(0, 0.6, f'{value:.0f}', 
                      ha='center', va='center',
                      color=color,
                      fontsize=12)
        setattr(self, f'{ax.get_label()}_text', text) 