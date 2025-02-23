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
        self.window.geometry("1200x800")  # 加宽窗口以容纳两列
        
        # 创建图表
        self.fig = Figure(figsize=(12, 10))
        
        # 创建2x3网格布局
        gs = self.fig.add_gridspec(3, 2, width_ratios=[2, 1], hspace=0.3, wspace=0.3)
        
        # 左列放置三相数据
        # 电流图表
        self.ax_current = self.fig.add_subplot(gs[0, 0])
        self.ax_current.set_title("三相电流")
        self.ax_current.set_ylabel("电流 (A)")
        
        # 电压图表
        self.ax_voltage = self.fig.add_subplot(gs[1, 0])
        self.ax_voltage.set_title("三相电压")
        self.ax_voltage.set_ylabel("电压 (V)")
        
        # 速度和转矩图表
        self.ax_speed = self.fig.add_subplot(gs[2, 0])
        self.ax_speed.set_title("速度和转矩")
        self.ax_speed.set_ylabel("速度 (rpm)")
        self.ax_speed2 = self.ax_speed.twinx()
        self.ax_speed2.set_ylabel("转矩电流 (A)")
        
        # 右列放置位置极坐标图
        self.ax_position = self.fig.add_subplot(gs[:, 1], projection='polar')
        self.ax_position.set_title("电机位置")
        self.ax_position.set_theta_zero_location('N')  # 设置0度位置在正上方
        self.ax_position.set_theta_direction(-1)  # 设置角度增长方向为顺时针
        
        # 为位置图添加刻度标签
        self.ax_position.set_xticks(np.linspace(0, 2*np.pi, 8, endpoint=False))
        self.ax_position.set_xticklabels(['0°', '45°', '90°', '135°', '180°', '225°', '270°', '315°'])
        
        # 所有直角坐标图添加网格和标签
        for ax in [self.ax_current, self.ax_voltage, self.ax_speed]:
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
        self.voltage_a = deque(maxlen=self.data_len)
        self.voltage_b = deque(maxlen=self.data_len)
        self.voltage_c = deque(maxlen=self.data_len)
        self.speed = deque(maxlen=self.data_len)
        self.torque = deque(maxlen=self.data_len)
        
        # 添加位置数据缓存
        self.position_data = deque(maxlen=self.data_len)
        
        # 图表线条
        self.lines = {}
        
        # 添加暂停按钮
        self.paused = False
        self.pause_btn = ttk.Button(self.window, text="暂停", command=self.toggle_pause)
        self.pause_btn.pack(side=tk.BOTTOM, pady=5)
        
        # 设置Y轴范围
        self.ax_current.set_ylim(-30, 30)  # 根据实际电流范围调整
        self.ax_voltage.set_ylim(0, 400)   # 根据实际电压范围调整
        self.ax_speed.set_ylim(-6000, 6000)  # 根据实际转速范围调整
        self.ax_speed2.set_ylim(-30, 30)     # 根据实际转矩范围调整
        
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
            if msg_id == CAN_ID_CURRENT:
                current_a = int.from_bytes(data[0:2], byteorder='little', signed=True) / 10
                current_b = int.from_bytes(data[2:4], byteorder='little', signed=True) / 10
                current_c = int.from_bytes(data[4:6], byteorder='little', signed=True) / 10
                
                self.current_a.append(current_a)
                self.current_b.append(current_b)
                self.current_c.append(current_c)
                
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
                
            elif msg_id == CAN_ID_VOLTAGE:
                voltage_a = int.from_bytes(data[0:2], byteorder='little', signed=False) / 10
                voltage_b = int.from_bytes(data[2:4], byteorder='little', signed=False) / 10
                voltage_c = int.from_bytes(data[4:6], byteorder='little', signed=False) / 10
                
                self.voltage_a.append(voltage_a)
                self.voltage_b.append(voltage_b)
                self.voltage_c.append(voltage_c)
                
                # 更新电压图表
                if not self.lines.get('voltage'):
                    self.lines['voltage'] = []
                    self.lines['voltage'].append(self.ax_voltage.plot([], [], 'r-', label='A相')[0])
                    self.lines['voltage'].append(self.ax_voltage.plot([], [], 'g-', label='B相')[0])
                    self.lines['voltage'].append(self.ax_voltage.plot([], [], 'b-', label='C相')[0])
                    self.ax_voltage.legend(loc='upper right')
                
                x_data = list(range(len(self.voltage_a)))
                self.lines['voltage'][0].set_data(x_data, self.voltage_a)
                self.lines['voltage'][1].set_data(x_data, self.voltage_b)
                self.lines['voltage'][2].set_data(x_data, self.voltage_c)
                self.ax_voltage.relim()
                self.ax_voltage.autoscale_view()
                
            elif msg_id == CAN_ID_SPEED:
                speed = int.from_bytes(data[0:2], byteorder='little', signed=True)
                torque = int.from_bytes(data[4:6], byteorder='little', signed=True) / 10
                
                self.speed.append(speed)
                self.torque.append(torque)
                
                # 更新速度和转矩图表
                if not self.lines.get('speed'):
                    self.lines['speed'] = []
                    self.lines['speed'].append(self.ax_speed.plot([], [], 'r-', label='速度')[0])
                    self.lines['speed'].append(self.ax_speed2.plot([], [], 'b-', label='转矩')[0])
                    # 合并两个y轴的图例
                    lines = [self.lines['speed'][0], self.lines['speed'][1]]
                    labels = ['速度', '转矩']
                    self.ax_speed.legend(lines, labels, loc='upper right')
                
                x_data = list(range(len(self.speed)))
                self.lines['speed'][0].set_data(x_data, self.speed)
                self.lines['speed'][1].set_data(x_data, self.torque)
                self.ax_speed.relim()
                self.ax_speed.autoscale_view()
                self.ax_speed2.relim()
                self.ax_speed2.autoscale_view()
            
            elif msg_id == CAN_ID_POSITION:
                position = int.from_bytes(data[0:2], byteorder='little', signed=True)
                angle = position * 360.0 / 8192  # 转换为角度
                angle_rad = np.deg2rad(angle)  # 转换为弧度
                
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