from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtCore import QTimer, Qt
from datetime import datetime
import sys
import time
import os
import math
import numpy as np
from can import Message

# 添加字体图标支持
from PyQt5.QtGui import QFontDatabase, QFont

from pyqt5.new_design import Ui_MainWindow
from utils.constants import *
from gui.plot_window import PlotWindow
from can_bus import VirtualCANBus, RealCANBus, MotorData
from data_logger import DataLogger
from warning_system import WarningSystem
from warning_dialog import WarningSettingsDialog, WarningHistoryDialog
from dashboard import PositionDashBoard, SpeedDashBoard, PowerDashBoard, CurrentLineChart

class MainQtWindow(QtWidgets.QMainWindow):
    def __init__(self, can_bus):
        super(MainQtWindow, self).__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        
        # 设置所有图标
        self.setup_icons()
        
        self.can_bus = can_bus
        self.data_logger = None
        self.plot_window = None
        
        # 设置定时器用于轮询CAN消息
        self.timer = QTimer()
        self.timer.timeout.connect(self.poll_messages)
        self.timer.start(10)  # 100ms轮询间隔
        
        # 连接信号和槽
        self.connect_signals()
        
        # 初始化表格
        self.init_tables()
        
        # 添加连接状态
        self.connected = False
        self.ui.StatusLabel.mousePressEvent = self.toggle_connection
        
        # 添加警告系统
        self.warning_system = WarningSystem()
        
        # 创建仪表盘和图表
        self.position_dashboard = PositionDashBoard()
        self.speed_dashboard = SpeedDashBoard()
        self.power_dashboard = PowerDashBoard()
        self.current_chart = CurrentLineChart()
        
        # 替换原有的Widget
        for widget, container in [
            (self.position_dashboard, self.ui.PosDashboard),
            (self.speed_dashboard, self.ui.SpeedDashboard),
            (self.power_dashboard, self.ui.PowerDashboard),
            (self.current_chart, self.ui.currentLineChart)
        ]:
            layout = container.layout()
            if layout:
                layout.addWidget(widget)
            else:
                layout = QtWidgets.QVBoxLayout(container)
                layout.addWidget(widget)
                layout.setContentsMargins(0, 0, 0, 0)
        
        # 添加电机状态标志
        self.motor_running = False
        
        # 设置速度输入框验证器
        speed_validator = QtGui.QDoubleValidator(-3000, 3000, 1)
        self.ui.lineEdit.setValidator(speed_validator)
        self.ui.lineEdit.setPlaceholderText("输入目标速度 (-3000 ~ 3000 rpm)")
        
        # 添加回车键响应
        self.ui.lineEdit.returnPressed.connect(lambda: self.send_control(CMD_SPEED_UP))
        
    def connect_signals(self):
        """连接信号和槽"""
        # 页面切换按钮
        self.ui.MenuButton.clicked.connect(lambda: self.ui.stackedWidget.setCurrentIndex(0))
        self.ui.ViewButton.clicked.connect(lambda: self.ui.stackedWidget.setCurrentIndex(1))
        self.ui.ContriolButton.clicked.connect(lambda: self.ui.stackedWidget.setCurrentIndex(2))
        
        # 控制按钮
        self.ui.controlButton_acc.clicked.connect(lambda: self.send_control(CMD_SPEED_UP))
        self.ui.pushButton_7.clicked.connect(lambda: self.send_control(CMD_SPEED_DOWN))
        self.ui.pushButton_6.clicked.connect(self.toggle_motor)
        self.ui.pushButton_8.clicked.connect(lambda: self.send_control(CMD_REVERSE))
        
        # 警告设置按钮
        self.ui.WarningSetting.clicked.connect(self.show_warning_settings)
        self.ui.WarningHis.clicked.connect(self.show_warning_history)
        
    def init_tables(self):
        """初始化表格"""
        # 警告表格
        self.ui.warningTable.setColumnCount(2)
        self.ui.warningTable.setHorizontalHeaderLabels(['类型', '时间'])
        self.ui.warningTable.horizontalHeader().setSectionResizeMode(
            QtWidgets.QHeaderView.Stretch)
            
        # 数据表格
        self.ui.tableWidget.setColumnCount(2)
        self.ui.tableWidget.setHorizontalHeaderLabels(['位置', '速度'])
        self.ui.tableWidget.horizontalHeader().setSectionResizeMode(
            QtWidgets.QHeaderView.Stretch)
            
        # 设置定时更新
        self.update_timer = QTimer()
        self.update_timer.timeout.connect(self.update_table_data)
        self.update_timer.start(1000)  # 1秒更新一次
        
        # 存储最新数据
        self.current_position = 0
        self.current_speed = 0
        
    def poll_messages(self):
        """轮询CAN消息"""
        msg = self.can_bus.recv(timeout=0)
        if msg:
            addr, value = self.can_bus.parse_message(msg)
            if addr is not None:
                self.can_bus.update_motor_data(addr, value)
                self.update_display()
            
    def update_display(self):
        """更新显示"""
        data = self.can_bus.data
        
        # 更新电流信息
        current_info = (f"Ia={data.ia:.1f}A\n"
                       f"Ib={data.ib:.1f}A\n"
                       f"Ic={data.ic:.1f}A\n")
               
        self.ui.textBrowser_2.setText(current_info)
        
        # 更新电流图表
        self.current_chart.update_current(data.ia, data.ib, data.ic)
        
        # 更新速度信息
        self.speed_dashboard.update_value(data.speed_fed)
        
        # 更新位置信息
        angle = data.position * 360.0 / 8192
        self.position_dashboard.update_value(angle)
        
        # 计算功率
        voltage = 24.0  # 假设电压为24V
        # 使用三相电流计算功率
        power = voltage * (abs(data.ia) + abs(data.ib) + abs(data.ic))
        self.power_dashboard.update_value(power)
        
    def update_table_data(self):
        """定时更新表格数据"""
        time_str = datetime.now().strftime('%H:%M:%S')
        
        # 插入新行
        self.ui.tableWidget.insertRow(0)
        self.ui.tableWidget.setVerticalHeaderItem(0, QtWidgets.QTableWidgetItem(time_str))
        
        # 设置数据
        self.ui.tableWidget.setItem(0, 0, QtWidgets.QTableWidgetItem(f"{self.current_position:.1f}°"))
        self.ui.tableWidget.setItem(0, 1, QtWidgets.QTableWidgetItem(f"{self.current_speed:.0f}"))
        
        # 限制最大行数为10
        while self.ui.tableWidget.rowCount() > 15:
            self.ui.tableWidget.removeRow(15)
        
    def toggle_motor(self):
        """切换电机启停状态"""
        if self.motor_running:
            self.send_control(CMD_STOP)
            self.motor_running = False
            self.ui.pushButton_6.setText("⏵ Start")  # 使用播放图标
            self.ui.pushButton_6.setStyleSheet("""
                QPushButton {
                    background-color: #4CAF50;
                    color: white;
                    border: 1px solid #CCCCCC;
                    border-radius: 10px;
                    padding: 5px;
                    font-size: 15pt;
                }
                QPushButton:hover {
                    background-color: #45a049;
                }
                QPushButton:pressed {
                    background-color: #398038;
                }
            """)
        else:
            self.send_control(CMD_START)
            self.motor_running = True
            self.ui.pushButton_6.setText("⏻ Stop")  # 使用停止图标
            self.ui.pushButton_6.setStyleSheet("""
                QPushButton {
                    background-color: #f44336;
                    color: white;
                    border: 1px solid #CCCCCC;
                    border-radius: 10px;
                    padding: 5px;
                    font-size: 15pt;
                }
                QPushButton:hover {
                    background-color: #da190b;
                }
                QPushButton:pressed {
                    background-color: #d32f2f;
                }
            """)
            
    def send_control(self, cmd):
        """发送控制命令"""
        try:
            # 根据命令类型构造对应的字符串命令
            command = None
            if cmd == CMD_SPEED_UP:
                if self.ui.lineEdit.text():  # 如果有输入具体速度
                    try:
                        target_speed = float(self.ui.lineEdit.text())
                        # 限制速度范围
                        target_speed = max(min(target_speed, MAX_SPEED), MIN_SPEED)
                        command = f"SPD {target_speed:.0f}"
                    except ValueError:
                        QtWidgets.QMessageBox.warning(self, "警告", "请输入有效的数字!")
                        return
                else:
                    # 保持ACCE前缀，但添加默认增量
                    command = "ACCE 100"  # 默认加速100rpm
            elif cmd == CMD_SPEED_DOWN:
                command = "DECE 100"  # 默认减速100rpm
            elif cmd == CMD_STOP:
                command = "MOT OFF"
            elif cmd == CMD_START:
                command = "MOT ON"
            elif cmd == CMD_REVERSE:
                command = "DIR REV"
            else:
                QtWidgets.QMessageBox.warning(self, "警告", "未知的命令类型!")
                return

            if command:
                # 创建并发送消息
                msg = Message(
                    arbitration_id=CAN_ID_CONTROL,
                    data=command.encode('ascii'),  # 将字符串转换为字节数组
                    is_extended_id=False
                )
                self.can_bus.send(msg)
                
                # 清空输入框
                self.ui.lineEdit.clear()
                
                print(f"发送控制命令: {command}")
            
        except Exception as e:
            QtWidgets.QMessageBox.critical(self, "错误", f"发送失败: {str(e)}")
            
    def show_warning_settings(self):
        """显示警告设置对话框"""
        dialog = WarningSettingsDialog(self.warning_system, self)
        dialog.exec_()
        
    def show_warning_history(self):
        """显示警告历史对话框"""
        dialog = WarningHistoryDialog(self.warning_system, self)
        dialog.exec_()

    def toggle_connection(self, event):
        """切换连接状态"""
        try:
            if not self.connected:
                # 尝试连接
                if self.can_bus.connect():
                    self.connected = True
                    self.ui.StatusLabel.setText("☰ Connected")
                    self.ui.StatusLabel.setStyleSheet("""
                        QLabel {
                            background-color: #4CAF50;
                            color: white;
                            text-align: center;
                            padding: 5px;
                            font-size: 20pt;
                            border-radius: 5px;
                        }
                    """)
                    # 启动数据更新
                    self.timer.start()
                    self.update_timer.start()
            else:
                # 断开连接
                if self.can_bus.disconnect():
                    self.connected = False
                    self.ui.StatusLabel.setText("☰ Disconnected")
                    self.ui.StatusLabel.setStyleSheet("""
                        QLabel {
                            background-color: #F44336;
                            color: white;
                            text-align: center;
                            padding: 5px;
                            font-size: 20pt;
                            border-radius: 5px;
                        }
                    """)
                    # 停止数据更新
                    self.timer.stop()
                    self.update_timer.stop()
        except Exception as e:
            QtWidgets.QMessageBox.critical(self, "错误", f"连接操作失败: {str(e)}")

    def setup_icons(self):
        """设置所有图标"""
        # 设置Logo和图片
        try:
            # 使用绝对路径
            base_dir = os.path.dirname(os.path.abspath(__file__))
            logo_path = os.path.join(base_dir, "static", "logo.png")
            pic_path = os.path.join(base_dir, "static", "pic.png")
            
            # 检查文件是否存在
            if not os.path.exists(logo_path):
                print(f"Warning: Logo file not found at {logo_path}")
                return
            if not os.path.exists(pic_path):
                print(f"Warning: Picture file not found at {pic_path}")
                return
            
            # 方法1：直接设置Label的固定大小
            self.ui.label.setFixedSize(100, 100)      # Logo大小
            self.ui.label_5.setFixedSize(200, 200)    # Picture大小
            self.ui.label_2.setFixedSize(200, 200)    # Picture大小
            
            # 方法2：手动指定图片缩放大小
            logo_pixmap = QtGui.QPixmap(logo_path).scaled(
                150, 150,  # 指定具体的宽度和高度
                QtCore.Qt.KeepAspectRatio,
                QtCore.Qt.SmoothTransformation
            )
            pic_pixmap = QtGui.QPixmap(pic_path).scaled(
                200, 200,  # 指定具体的宽度和高度
                QtCore.Qt.KeepAspectRatio,
                QtCore.Qt.SmoothTransformation
            )
            
            # 设置图片
            self.ui.label.setPixmap(logo_pixmap)
            self.ui.label_5.setPixmap(pic_pixmap)
            self.ui.label_2.setPixmap(pic_pixmap)
            
            # 可选：设置对齐方式
            self.ui.label.setAlignment(QtCore.Qt.AlignCenter)
            self.ui.label_5.setAlignment(QtCore.Qt.AlignCenter)
            self.ui.label_2.setAlignment(QtCore.Qt.AlignCenter)
            # 设置是否自适应大小（如果设为True，图片会填充整个Label）
            self.ui.label.setScaledContents(False)  # 改为False以使用固定大小
            self.ui.label_5.setScaledContents(False)
            self.ui.label_2.setScaledContents(False)

        except Exception as e:
            print(f"Error loading images: {str(e)}")
        
        # 菜单按钮图标
        self.ui.MenuButton.setText("☰ Menu")        # fa-ellipsis-v
        self.ui.ViewButton.setText("📊 View")        # fa-bar-chart
        self.ui.ContriolButton.setText("⬆ Control") # fa-upload
        
        # 控制按钮图标
        self.ui.controlButton_acc.setText("⏩ Accelerate")    # fa-toggle-right
        self.ui.pushButton_7.setText("⏪ Decelerate")        # fa-toggle-left
        self.ui.pushButton_8.setText("↩ Turnover")          # fa-reply
        self.ui.pushButton_6.setText("⏻ Stop")              # fa-power-off
        
        # 设置按钮图标
        self.ui.WarningSetting.setText("⚙ Settings")        # fa-cog
        self.ui.WarningHis.setText("⟲ History")            # fa-history
        
        # 标签图标
        self.ui.StatusLabel.setText("☰ Disconnected")
        self.ui.StatusLabel.setStyleSheet("""
            QLabel {
                background-color: #F44336;
                color: white;
                text-align: center;
                padding: 5px;
                font-size: 20pt;
                border-radius: 5px;
                cursor: pointer;
            }
        """)
        self.ui.StatusLabel.setCursor(QtCore.Qt.PointingHandCursor)  # 设置鼠标指针样式
        
        # 统一设置按钮样式
        buttons = [
            self.ui.MenuButton, self.ui.ViewButton, self.ui.ContriolButton,
            self.ui.controlButton_acc, self.ui.pushButton_7, self.ui.pushButton_8,
            self.ui.pushButton_6, self.ui.WarningSetting, self.ui.WarningHis
        ]
        
        for button in buttons:
            button.setStyleSheet("""
                QPushButton {
                    background-color: white;
                    color: black;
                    border: 1px solid #CCCCCC;
                    border-radius: 10px;
                    padding: 5px;
                    font-size: 15pt;
                }
                QPushButton:hover {
                    background-color: #E0E0E0;
                }
                QPushButton:pressed {
                    background-color: #50B56A;
                    color: white;
                }
            """)
        
        # 设置标签样式
        self.ui.StatusLabel.setStyleSheet("""
            QLabel {
                background-color: #4362F0;
                color: white;
                text-align: center;
                padding: 5px;
                font-size: 20pt;
                border-radius: 5px;
            }
        """)

    def update_warning_table(self, warnings):
        """更新警告表格"""
        time_str = datetime.now().strftime('%m-%d %H:%M:%S')
        
        for warning in warnings:  # warnings现在只包含新警告
            # 检查是否已存在相同类型的警告
            existing_row = -1
            for row in range(self.ui.warningTable.rowCount()):
                item = self.ui.warningTable.item(row, 0)
                if item and item.text() == warning.value:
                    existing_row = row
                    break
            
            if existing_row >= 0:
                # 更新已存在警告的时间
                self.ui.warningTable.setItem(existing_row, 1, 
                    QtWidgets.QTableWidgetItem(time_str))
                # 移动到表格顶部
                self.ui.warningTable.removeRow(existing_row)
                self.ui.warningTable.insertRow(0)
                self.ui.warningTable.setItem(0, 0, 
                    QtWidgets.QTableWidgetItem(warning.value))
                self.ui.warningTable.setItem(0, 1, 
                    QtWidgets.QTableWidgetItem(time_str))
            else:
                # 添加新警告到顶部
                self.ui.warningTable.insertRow(0)
                self.ui.warningTable.setItem(0, 0, 
                    QtWidgets.QTableWidgetItem(warning.value))
                self.ui.warningTable.setItem(0, 1, 
                    QtWidgets.QTableWidgetItem(time_str))
            
            # 设置单元格对齐方式
            for col in range(2):
                item = self.ui.warningTable.item(0, col)
                if item:
                    item.setTextAlignment(Qt.AlignCenter)
        
        # 限制警告表格最大行数
        while self.ui.warningTable.rowCount() > 100:  # 保留最近100条警告
            self.ui.warningTable.removeRow(100)

    def send_motor_command(self, cmd_type: int, value: float = 0.0):
        """发送电机控制命令"""
        if not self.can_bus.is_connected:
            self.show_message("错误", "请先连接CAN设备")
            return
        
        if self.can_bus.send_control_command(cmd_type, value):
            self.show_message("成功", "命令已发送")
        else:
            self.show_message("错误", "命令发送失败")

    def on_start_clicked(self):
        """启动电机"""
        self.send_motor_command(CMD_START)

    def on_stop_clicked(self):
        """停止电机"""
        self.send_motor_command(CMD_STOP)

    def on_speed_set_clicked(self):
        """设置速度"""
        try:
            speed = float(self.speed_input.text())
            self.send_motor_command(CMD_SPEED_SET, speed)
        except ValueError:
            self.show_message("错误", "请输入有效的速度值")

def main():
    app = QtWidgets.QApplication(sys.argv)
    
    # 根据配置选择CAN总线类型
    USE_VIRTUAL_CAN = True  # 可以通过配置文件或命令行参数设置
    
    if USE_VIRTUAL_CAN:
        bus = VirtualCANBus()
    else:
        bus = RealCANBus(channel='can0', bitrate=500000)
    
    # 创建主窗口
    window = MainQtWindow(bus)
    window.show()
    
    sys.exit(app.exec_())

if __name__ == '__main__':
    main() 