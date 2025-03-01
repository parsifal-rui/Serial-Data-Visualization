from PyQt5.QtWidgets import QWidget, QVBoxLayout
import pyqtgraph as pg
import numpy as np
from collections import deque
import time

class DashBoard(QWidget):
    def __init__(self, title, min_value, max_value, parent=None):
        super().__init__(parent)
        self.min_value = min_value
        self.max_value = max_value
        
        # 创建环形图表
        self.plot = pg.PlotWidget()
        self.plot.setBackground('w')
        self.plot.hideAxis('left')
        self.plot.hideAxis('bottom')
        self.plot.setAspectLocked()
        
        # 设置标题
        self.plot.setTitle(title, size='12pt', color='#2196F3')
        
        # 创建圆环
        self.create_gauge()
        
        # 布局
        layout = QVBoxLayout(self)
        layout.addWidget(self.plot)
        layout.setContentsMargins(0, 0, 0, 0)
        
    def create_gauge(self):
        # 创建背景圆环
        theta = np.linspace(140/180.0*np.pi, 400/180.0*np.pi, 100)
        r = 1.0
        x = r * np.cos(theta)
        y = r * np.sin(theta)
        
        # 绘制背景圆环
        self.plot.plot(x, y, pen=pg.mkPen(color='#E0E0E0', width=15))
        
        # 创建主刻度线
        for i in range(9):  # 8等分
            value = self.min_value + (self.max_value - self.min_value) * i / 8
            angle = (140 + 260 * i / 8) / 180.0 * np.pi
            
            # 绘制刻度线
            r_start = 0.85
            r_end = 1.15
            x_start = r_start * np.cos(angle)
            y_start = r_start * np.sin(angle)
            x_end = r_end * np.cos(angle)
            y_end = r_end * np.sin(angle)
            
            self.plot.plot([x_start, x_end], [y_start, y_end], 
                          pen=pg.mkPen(color='#757575', width=2))
            
            # 添加刻度值
            x_text = 1.3 * np.cos(angle)
            y_text = 1.3 * np.sin(angle)
            text = pg.TextItem(text=f'{value:.0f}', color='#404040', 
                             anchor=(0.5, 0.5))
            text.setFont(pg.QtGui.QFont("Arial", 8))
            text.setPos(x_text, y_text)
            self.plot.addItem(text)
        
        # 创建次刻度线
        for i in range(40):  # 40个小刻度
            if i % 5 != 0:  # 跳过主刻度位置
                angle = (140 + 260 * i / 40) / 180.0 * np.pi
                r_start = 0.9
                r_end = 1.1
                x_start = r_start * np.cos(angle)
                y_start = r_start * np.sin(angle)
                x_end = r_end * np.cos(angle)
                y_end = r_end * np.sin(angle)
                
                self.plot.plot([x_start, x_end], [y_start, y_end], 
                              pen=pg.mkPen(color='#BDBDBD', width=1))
        
        # 创建中心装饰圆
        circle_r = 0.15
        theta_circle = np.linspace(0, 2*np.pi, 100)
        x_circle = circle_r * np.cos(theta_circle)
        y_circle = circle_r * np.sin(theta_circle)
        self.plot.plot(x_circle, y_circle, pen=pg.mkPen(color='#2196F3', width=2))
        
        # 创建指针和值弧
        self.value_curve = self.plot.plot([], [], 
                                        pen=pg.mkPen(color='#2196F3', width=15))
        self.pointer = self.plot.plot([], [], pen=None, 
                                    symbol='o', symbolSize=12,
                                    symbolBrush='#2196F3',
                                    symbolPen=pg.mkPen(color='white', width=2))
        
        # 添加当前值文本显示
        self.value_text = pg.TextItem(text='', color='#2196F3', anchor=(0.5, 0.5))
        self.value_text.setFont(pg.QtGui.QFont("Arial", 12, pg.QtGui.QFont.Bold))
        self.value_text.setPos(0, -0.5)
        self.plot.addItem(self.value_text)
        
        # 设置显示范围
        self.plot.setRange(xRange=(-1.5, 1.5), yRange=(-1.5, 1.5))
        
    def update_value(self, value):
        # 限制值范围
        value = max(min(value, self.max_value), self.min_value)
        
        # 更新数值显示
        self.value_text.setText(f'{value:.1f}')
        
        # 计算角度
        angle = 140 + (value - self.min_value) * 260 / (self.max_value - self.min_value)
        angle_rad = angle / 180.0 * np.pi
        
        # 更新值弧
        theta = np.linspace(140/180.0*np.pi, angle_rad, 50)
        x = np.cos(theta)
        y = np.sin(theta)
        self.value_curve.setData(x, y)
        
        # 更新指针位置
        self.pointer.setData([np.cos(angle_rad)], [np.sin(angle_rad)])

class CurrentLineChart(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
        
        # 创建图表
        self.plot = pg.PlotWidget()
        self.plot.setBackground('w')
        self.plot.setTitle("Phase Current", size='12pt')
        
        # 设置坐标轴
        self.plot.setLabel('left', 'Current (A)')
        self.plot.setLabel('bottom', 'Time (s)')
        self.plot.showGrid(x=True, y=True)
        
        # 设置Y轴范围
        self.plot.setYRange(-20, 20)
        
        # 创建曲线
        self.curves = {
            'Ia': self.plot.plot(pen=pg.mkPen(color='#FF4081', width=2), name='Phase A'),
            'Ib': self.plot.plot(pen=pg.mkPen(color='#00E676', width=2), name='Phase B'),
            'Ic': self.plot.plot(pen=pg.mkPen(color='#2979FF', width=2), name='Phase C')
        }
        
        # 添加图例
        self.plot.addLegend()
        
        # 数据缓存 (1秒 × 100Hz = 1000个点)
        self.window_size = 1  # 1秒窗口
        self.sample_rate = 100  # 100Hz
        buffer_size = self.window_size * self.sample_rate
        
        self.time_data = deque(maxlen=buffer_size)
        self.current_data = {
            'Ia': deque(maxlen=buffer_size),
            'Ib': deque(maxlen=buffer_size),
            'Ic': deque(maxlen=buffer_size)
        }
        
        # 初始化时间窗口
        self.last_update = time.time()
        
        # 布局
        layout = QVBoxLayout(self)
        layout.addWidget(self.plot)
        layout.setContentsMargins(0, 0, 0, 0)
        
    def update_current(self, ia, ib, ic):
        current_time = time.time()
        
        # 只有经过一定时间间隔才更新（控制采样率）
        if current_time - self.last_update < 1.0/self.sample_rate:
            return
        self.last_update = current_time
        
        # 计算相对时间
        if not self.time_data:
            self.start_time = current_time
        relative_time = current_time - self.start_time
        
        # 添加新数据
        self.time_data.append(relative_time)
        self.current_data['Ia'].append(ia)
        self.current_data['Ib'].append(ib)
        self.current_data['Ic'].append(ic)
        
        # 更新曲线
        time_array = np.array(self.time_data)
        for name, curve in self.curves.items():
            curve.setData(time_array, np.array(self.current_data[name]))
        
        # 设置X轴范围为最近10秒
        if len(time_array) > 0:
            x_min = max(0, relative_time - self.window_size)
            x_max = relative_time
            self.plot.setXRange(x_min, x_max)
            
        # 强制重绘
        self.plot.update()

class PositionDashBoard(DashBoard):
    def __init__(self, parent=None):
        super().__init__("Position (deg)", 0, 360, parent)
        
class SpeedDashBoard(DashBoard):
    def __init__(self, parent=None):
        super().__init__("Speed (rpm)", -3000, 3000, parent)
        
class PowerDashBoard(DashBoard):
    def __init__(self, parent=None):
        super().__init__("Power (W)", 0, 1000, parent) 