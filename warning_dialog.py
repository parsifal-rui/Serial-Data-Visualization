from PyQt5 import QtWidgets
from PyQt5.QtCore import Qt

class WarningSettingsDialog(QtWidgets.QDialog):
    def __init__(self, warning_system, parent=None):
        super().__init__(parent)
        self.warning_system = warning_system
        self.setup_ui()
        
    def setup_ui(self):
        self.setWindowTitle("警告设置")
        layout = QtWidgets.QFormLayout(self)
        
        # 创建输入框
        self.current_max = QtWidgets.QDoubleSpinBox()
        self.current_max.setRange(0, 100)
        self.current_max.setValue(self.warning_system.settings.thresholds['current_max'])
        
        self.current_min = QtWidgets.QDoubleSpinBox()
        self.current_min.setRange(0, 10)
        self.current_min.setValue(self.warning_system.settings.thresholds['current_min'])
        
        self.speed_max = QtWidgets.QSpinBox()
        self.speed_max.setRange(0, 5000)
        self.speed_max.setValue(self.warning_system.settings.thresholds['speed_max'])
        
        self.power_max = QtWidgets.QSpinBox()
        self.power_max.setRange(0, 1000)
        self.power_max.setValue(self.warning_system.settings.thresholds['power_max'])
        
        # 添加到布局
        layout.addRow("最大电流 (A):", self.current_max)
        layout.addRow("最小电流 (A):", self.current_min)
        layout.addRow("最大转速 (rpm):", self.speed_max)
        layout.addRow("最大功率 (W):", self.power_max)
        
        # 添加按钮
        buttons = QtWidgets.QDialogButtonBox(
            QtWidgets.QDialogButtonBox.Ok | QtWidgets.QDialogButtonBox.Cancel
        )
        buttons.accepted.connect(self.accept)
        buttons.rejected.connect(self.reject)
        layout.addRow(buttons)
        
    def accept(self):
        # 保存设置
        self.warning_system.settings.thresholds.update({
            'current_max': self.current_max.value(),
            'current_min': self.current_min.value(),
            'speed_max': self.speed_max.value(),
            'power_max': self.power_max.value(),
        })
        super().accept()

class WarningHistoryDialog(QtWidgets.QDialog):
    def __init__(self, warning_system, parent=None):
        super().__init__(parent)
        self.warning_system = warning_system
        self.setup_ui()
        
    def setup_ui(self):
        self.setWindowTitle("警告历史")
        layout = QtWidgets.QVBoxLayout(self)
        
        # 创建表格
        self.table = QtWidgets.QTableWidget()
        self.table.setColumnCount(2)
        self.table.setHorizontalHeaderLabels(['警告类型', '时间'])
        self.table.horizontalHeader().setSectionResizeMode(
            QtWidgets.QHeaderView.Stretch
        )
        
        # 填充数据
        self.update_table()
        
        # 添加导出按钮
        export_btn = QtWidgets.QPushButton("导出CSV")
        export_btn.clicked.connect(self.export_history)
        
        layout.addWidget(self.table)
        layout.addWidget(export_btn)
        
    def update_table(self):
        history = self.warning_system.warning_history
        self.table.setRowCount(len(history))
        
        for i, record in enumerate(history):
            self.table.setItem(i, 0, QtWidgets.QTableWidgetItem(record['type'].value))
            time_str = record['time'].strftime('%Y-%m-%d %H:%M:%S')
            self.table.setItem(i, 1, QtWidgets.QTableWidgetItem(time_str))
            
    def export_history(self):
        filename, _ = QtWidgets.QFileDialog.getSaveFileName(
            self,
            "导出警告历史",
            "",
            "CSV文件 (*.csv)"
        )
        if filename:
            if self.warning_system.export_history(filename):
                QtWidgets.QMessageBox.information(self, "成功", "警告历史已导出")
            else:
                QtWidgets.QMessageBox.warning(self, "错误", "导出失败") 