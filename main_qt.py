from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtCore import QTimer
from datetime import datetime
import sys
import time

from pyqt5.design import Ui_MainWindow
from utils.constants import *
from gui.plot_window import PlotWindow
from can_simulator import VirtualCANMessage, VirtualCANBus, MotorSimulator
from data_logger import DataLogger

class MainQtWindow(QtWidgets.QMainWindow):
    def __init__(self, can_bus):
        super(MainQtWindow, self).__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        
        self.can_bus = can_bus
        self.data_logger = None
        self.plot_window = None
        
        # 设置定时器用于轮询CAN消息
        self.timer = QTimer()
        self.timer.timeout.connect(self.poll_messages)
        self.timer.start(10)  # 10ms轮询间隔
        
        # 初始化UI组件
        self.setup_ui()
        
        # 连接信号和槽
        self.connect_signals()
        
    def setup_ui(self):
        """初始化UI组件"""
        # 设置窗口标题和大小
        self.setWindowTitle("电机监控系统")
        self.setMinimumSize(1000, 700)  # 设置最小窗口大小
        
        # 调整主布局间距
        self.ui.widget.setContentsMargins(20, 10, 20, 10)  # 设置主widget的边距
        self.ui.verticalLayout.setSpacing(15)  # 设置垂直布局的间距
        
        # 设置按钮文本
        self.ui.pushButton.setText("菜单")
        self.ui.pushButton_2.setText("监控")
        self.ui.pushButton_3.setText("控制")
        self.ui.pushButton_8.setText("设置")
        
        # 设置控制按钮
        self.ui.pushButton_4.setText("加速")
        self.ui.pushButton_5.setText("减速")
        self.ui.pushButton_6.setText("停止")
        self.ui.pushButton_7.setText("反向")
        
        # 调整顶部菜单栏
        self.ui.menu.setMaximumHeight(60)
        self.ui.menu.setStyleSheet("""
            QFrame {
                background-color: #1E88E5;
                border-radius: 10px;
            }
        """)
        
        # 调整按钮位置和大小
        for btn in [self.ui.pushButton, self.ui.pushButton_2, self.ui.pushButton_3]:
            btn.setFixedSize(120, 40)
            btn.setStyleSheet("""
                QPushButton {
                    background-color: #2196F3;
                    color: white;
                    border-radius: 5px;
                    font-size: 14px;
                    font-weight: bold;
                }
                QPushButton:hover {
                    background-color: #1976D2;
                }
            """)
        
        # 调整左侧边栏
        self.ui.sidebar_2.setFixedWidth(250)
        self.ui.sidebar_2.setStyleSheet("""
            QFrame {
                background-color: white;
                border-radius: 10px;
                border: 1px solid #E0E0E0;
            }
        """)
        
        # 创建状态显示区
        self.status_text = QtWidgets.QLabel(self.ui.status)
        self.status_text.setGeometry(QtCore.QRect(10, 10, 230, 60))
        self.status_text.setText("系统状态: 正常")
        self.status_text.setStyleSheet("""
            QLabel {
                background-color: #E8F5E9;
                border: 1px solid #C8E6C9;
                border-radius: 5px;
                padding: 10px;
                font-size: 13px;
                font-weight: bold;
            }
        """)
        
        # 创建警告显示区
        self.warning_text = QtWidgets.QTextEdit(self.ui.warnings)
        self.warning_text.setGeometry(QtCore.QRect(10, 10, 230, 120))
        self.warning_text.setReadOnly(True)
        self.warning_text.setStyleSheet("""
            QTextEdit {
                background-color: #FFF3E0;
                border: 1px solid #FFE0B2;
                border-radius: 5px;
                padding: 10px;
                font-size: 12px;
            }
        """)
        
        # 创建数据表格
        self.data_table = QtWidgets.QTableWidget(self.ui.real_time_table)
        self.data_table.setGeometry(QtCore.QRect(0, 0, 700, 500))
        self.data_table.setColumnCount(4)
        self.data_table.setHorizontalHeaderLabels(['时间', 'ID', '数据', '解析'])
        self.data_table.horizontalHeader().setSectionResizeMode(3, QtWidgets.QHeaderView.Stretch)
        self.data_table.setStyleSheet("""
            QTableWidget {
                background-color: white;
                border: 1px solid #E0E0E0;
                border-radius: 8px;
                padding: 5px;
            }
            QTableWidget::item {
                padding: 8px;
                border-bottom: 1px solid #F5F5F5;
            }
            QHeaderView::section {
                background-color: #2196F3;
                color: white;
                padding: 8px;
                border: none;
                font-weight: bold;
            }
        """)
        
        # 添加页面标题
        self.page_titles = {
            0: "系统监控",
            1: "电机控制",
            2: "系统菜单"
        }
        
        self.page_title = QtWidgets.QLabel(self.ui.mainbody)
        self.page_title.setGeometry(QtCore.QRect(270, 10, 300, 40))
        self.page_title.setStyleSheet("""
            QLabel {
                color: #1976D2;
                font-size: 18px;
                font-weight: bold;
            }
        """)
        self.update_page_title(0)  # 设置初始标题
        
        # 添加状态更新动画
        self.status_animation = QtCore.QPropertyAnimation(self.status_text, b"geometry")
        self.status_animation.setDuration(200)
        
        # 添加数据更新提示
        self.update_indicator = QtWidgets.QLabel(self.ui.mainbody)
        self.update_indicator.setGeometry(QtCore.QRect(900, 10, 16, 16))
        self.update_indicator.setStyleSheet("""
            QLabel {
                background-color: #4CAF50;
                border-radius: 8px;
            }
        """)
        self.update_indicator.hide()
        
    def connect_signals(self):
        """连接信号和槽"""
        # 页面切换按钮
        self.ui.pushButton.clicked.connect(lambda: self.ui.mainview.setCurrentIndex(2))  # 菜单页
        self.ui.pushButton_2.clicked.connect(lambda: self.ui.mainview.setCurrentIndex(0))  # 监控页
        self.ui.pushButton_3.clicked.connect(lambda: self.ui.mainview.setCurrentIndex(1))  # 控制页
        
        # 控制按钮
        self.ui.pushButton_4.clicked.connect(lambda: self.send_control(CMD_SPEED_UP))
        self.ui.pushButton_5.clicked.connect(lambda: self.send_control(CMD_SPEED_DOWN))
        self.ui.pushButton_6.clicked.connect(lambda: self.send_control(CMD_STOP))
        self.ui.pushButton_7.clicked.connect(lambda: self.send_control(CMD_REVERSE))
        
        # 设置按钮
        self.ui.pushButton_8.clicked.connect(self.show_settings)
        
        # 添加页面切换标题更新
        self.ui.mainview.currentChanged.connect(self.update_page_title)
        
    def poll_messages(self):
        """轮询CAN消息"""
        msg = self.can_bus.recv(timeout=0)
        if msg:
            self.update_display(msg)
            
    def update_display(self, msg):
        """更新显示"""
        # 更新表格
        time_str = datetime.now().strftime('%H:%M:%S.%f')[:-3]
        data_str = ' '.join(f'{b:02X}' for b in msg.data)
        parsed_str = self.parse_message(msg)
        
        row = self.data_table.rowCount()
        self.data_table.insertRow(0)
        self.data_table.setItem(0, 0, QtWidgets.QTableWidgetItem(time_str))
        self.data_table.setItem(0, 1, QtWidgets.QTableWidgetItem(f'{msg.arbitration_id:X}'))
        self.data_table.setItem(0, 2, QtWidgets.QTableWidgetItem(data_str))
        self.data_table.setItem(0, 3, QtWidgets.QTableWidgetItem(parsed_str))
        
        # 限制表格行数
        if self.data_table.rowCount() > 100:
            self.data_table.removeRow(self.data_table.rowCount() - 1)
            
        # 显示更新指示器
        self.update_indicator.show()
        QtCore.QTimer.singleShot(100, self.update_indicator.hide)
        
    def parse_message(self, msg):
        """解析CAN消息"""
        try:
            import struct
            data = bytes(msg.data)
            
            if msg.arbitration_id == CAN_ID_CURRENT:
                ia = struct.unpack('<f', data[0:4])[0]
                ib = struct.unpack('<f', data[4:8])[0]
                ic = struct.unpack('<f', data[8:12])[0]
                return f"Ia={ia:.1f}A, Ib={ib:.1f}A, Ic={ic:.1f}A"
                
            elif msg.arbitration_id == CAN_ID_SPEED:
                speed_ref = struct.unpack('<f', data[0:4])[0]
                speed_actual = struct.unpack('<f', data[4:8])[0]
                return f"Speed={speed_actual:.0f}rpm, Target={speed_ref:.0f}rpm"
                
            elif msg.arbitration_id == CAN_ID_POSITION:
                position = struct.unpack('<f', data[0:4])[0]
                angle = position * 360.0 / 8192
                return f"Position={position:.0f}, Angle={angle:.1f}°"
                
        except Exception as e:
            print(f"解析错误: {str(e)}")
        return "Unknown message"
        
    def send_control(self, cmd):
        """发送控制命令"""
        try:
            msg = VirtualCANMessage(
                arbitration_id=CAN_ID_CONTROL,
                data=[cmd, 0, 0, 0, 0, 0, 0, 0]
            )
            self.can_bus.send(msg)
        except Exception as e:
            QtWidgets.QMessageBox.critical(self, "错误", f"发送失败: {str(e)}")
            
    def show_settings(self):
        """显示设置对话框"""
        # TODO: 实现设置对话框
        QtWidgets.QMessageBox.information(self, "提示", "设置功能开发中...")

    def update_page_title(self, index):
        """更新页面标题"""
        self.page_title.setText(self.page_titles.get(index, ""))

def main():
    app = QtWidgets.QApplication(sys.argv)
    
    # 创建CAN总线和模拟器
    bus = VirtualCANBus()
    simulator = MotorSimulator(bus)
    
    # 创建主窗口
    window = MainQtWindow(bus)
    window.show()
    
    # 启动模拟器
    simulator.start_simulation()
    
    sys.exit(app.exec_())

if __name__ == '__main__':
    main() 