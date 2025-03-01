from enum import Enum
from datetime import datetime
import csv
import os

class WarningType(Enum):
    OVERCURRENT = "过流"
    UNDERCURRENT = "欠流"
    OVERSPEED = "超速"
    POWER_HIGH = "功率过大"
    SOFTWARE_ERROR = "软件错误"
    CONNECTION_ERROR = "连接错误"

class WarningSettings:
    def __init__(self):
        # 默认阈值设置
        self.thresholds = {
            'current_max': 15.0,    # A
            'current_min': 0.1,     # A
            'speed_max': 3000,      # rpm
            'power_max': 500,       # W
        }
        
class WarningSystem:
    def __init__(self):
        self.settings = WarningSettings()
        self.warning_history = []  # 完整的警告历史
        self.active_warnings = {}  # 当前活跃的警告 {WarningType: start_time}
        
    def check_warnings(self, ia, ib, ic, speed, voltage=24.0):
        """检查所有可能的警告"""
        current_time = datetime.now()
        warnings = []
        new_warnings = []  # 新出现的警告
        
        # 检查过流
        max_current = max(abs(ia), abs(ib), abs(ic))
        if max_current > self.settings.thresholds['current_max']:
            warnings.append(WarningType.OVERCURRENT)
            
        # 检查欠流
        if max_current < self.settings.thresholds['current_min']:
            warnings.append(WarningType.UNDERCURRENT)
            
        # 检查超速
        if abs(speed) > self.settings.thresholds['speed_max']:
            warnings.append(WarningType.OVERSPEED)
            
        # 检查功率
        power = max_current * voltage
        if power > self.settings.thresholds['power_max']:
            warnings.append(WarningType.POWER_HIGH)
            
        # 更新警告历史和活跃警告
        for warning in warnings:
            # 添加到完整历史记录
            warning_record = {
                'type': warning,
                'time': current_time,
            }
            self.warning_history.append(warning_record)
            
            # 检查是否是新警告
            if warning not in self.active_warnings:
                self.active_warnings[warning] = current_time
                new_warnings.append(warning)
        
        # 检查已结束的警告
        ended_warnings = []
        for warning in list(self.active_warnings.keys()):
            if warning not in warnings:
                ended_warnings.append(warning)
                
        # 移除已结束的警告
        for warning in ended_warnings:
            del self.active_warnings[warning]
            
        return new_warnings  # 只返回新出现的警告
        
    def get_active_warnings(self):
        """获取当前活跃的警告及其开始时间"""
        return self.active_warnings.copy()
        
    def export_history(self, filename):
        """导出警告历史到CSV文件"""
        if not self.warning_history:
            return False
            
        try:
            with open(filename, 'w', newline='', encoding='utf-8') as f:
                writer = csv.writer(f)
                writer.writerow(['警告类型', '时间'])
                for record in self.warning_history:
                    writer.writerow([
                        record['type'].value,
                        record['time'].strftime('%Y-%m-%d %H:%M:%S.%f')[:-3]
                    ])
            return True
        except Exception as e:
            print(f"导出失败: {str(e)}")
            return False 