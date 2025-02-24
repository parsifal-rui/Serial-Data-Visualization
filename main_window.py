from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtCore import QTimer
from datetime import datetime
import sys
import time

from pyqt5.design import Ui_MainWindow
from utils.constants import *
from gui.plot_window import PlotWindow
from can_simulator import VirtualCANMessage

class MainWindow(QtWidgets.QMainWindow):
    def __init__(self, can_bus):
        super(MainWindow, self).__init__()
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
        # 创建数据表格
        self.table = QtWidgets.QTableWidget(self.ui.mainbody)
        self.table.setGeometry(QtCore.QRect(189, 0, 321, 241))
        self.table.setColumnCount(4)
        self.table.setHorizontalHeaderLabels(['时间', 'ID', '数据', '解析'])
        self.table.horizontalHeader().setSectionResizeMode(3, QtWidgets.QHeaderView.Stretch)
        
        # 创建状态显示区
        self.status_label = QtWidgets.QLabel(self.ui.status)
        self.status_label.setGeometry(QtCore.QRect(10, 10, 81, 61))
        self.status_label.setText("状态: 正常")
        
        # 创建警告显示区
        self.warning_text = QtWidgets.QTextEdit(self.ui.warnings)
        self.warning_text.setGeometry(QtCore.QRect(10, 10, 81, 91))
        self.warning_text.setReadOnly(True)
        
        # 设置按钮功能
        self.ui.pushButton.setText("开始记录")
        self.ui.pushButton_2.setText("导出数据")
        self.ui.pushButton_3.setText("显示波形")
        
        # 控制按钮
        self.ui.pushButton_4.setText("加速")
        self.ui.pushButton_5.setText("减速")
        self.ui.pushButton_6.setText("停止")
        self.ui.pushButton_7.setText("反向")
        
    def connect_signals(self):
        """连接信号和槽"""
        self.ui.pushButton.clicked.connect(self.toggle_recording)
        self.ui.pushButton_2.clicked.connect(self.export_data)
        self.ui.pushButton_3.clicked.connect(self.show_plot_window)
        
        # 控制按钮
        self.ui.pushButton_4.clicked.connect(lambda: self.send_control(CMD_SPEED_UP))
        self.ui.pushButton_5.clicked.connect(lambda: self.send_control(CMD_SPEED_DOWN))
        self.ui.pushButton_6.clicked.connect(lambda: self.send_control(CMD_STOP))
        self.ui.pushButton_7.clicked.connect(lambda: self.send_control(CMD_REVERSE))
        
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
        
        row = self.table.rowCount()
        self.table.insertRow(0)
        self.table.setItem(0, 0, QtWidgets.QTableWidgetItem(time_str))
        self.table.setItem(0, 1, QtWidgets.QTableWidgetItem(f'{msg.arbitration_id:X}'))
        self.table.setItem(0, 2, QtWidgets.QTableWidgetItem(data_str))
        self.table.setItem(0, 3, QtWidgets.QTableWidgetItem(parsed_str))
        
        # 更新波形显示
        if self.plot_window:
            self.plot_window.update_plot(msg.timestamp, msg.arbitration_id, msg.data)
            
        # 更新数据记录
        if self.data_logger and self.data_logger.recording:
            self.data_logger.add_message(msg, parsed_str)
            
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
            
    def toggle_recording(self):
        """切换记录状态"""
        if self.data_logger:
            if not self.data_logger.recording:
                self.data_logger.start_recording()
                self.ui.pushButton.setText("停止记录")
            else:
                self.data_logger.stop_recording()
                self.ui.pushButton.setText("开始记录")
                
    def export_data(self):
        """导出数据"""
        if self.data_logger:
            try:
                filename = f"motor_data_{datetime.now().strftime('%Y%m%d_%H%M%S')}.csv"
                self.data_logger.export_csv(time.time()-3600, time.time(), filename)
                QtWidgets.QMessageBox.information(self, "成功", f"数据已导出到 {filename}")
            except Exception as e:
                QtWidgets.QMessageBox.critical(self, "错误", f"导出失败: {str(e)}")
                
    def show_plot_window(self):
        """显示波形窗口"""
        if not self.plot_window:
            self.plot_window = PlotWindow(self)
            
    def set_data_logger(self, logger):
        """设置数据记录器"""
        self.data_logger = logger

if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    
    # 创建CAN总线和模拟器
    from can_simulator import VirtualCANBus, MotorSimulator
    bus = VirtualCANBus()
    simulator = MotorSimulator(bus)
    
    # 创建数据记录器
    from data_logger import DataLogger
    logger = DataLogger()
    
    # 创建主窗口
    window = MainWindow(bus)
    window.set_data_logger(logger)
    window.show()
    
    # 启动模拟器
    simulator.start_simulation()
    
    sys.exit(app.exec_()) 