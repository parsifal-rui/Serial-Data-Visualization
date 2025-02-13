# CAN ID定义
CAN_ID_CURRENT = 0x201    # 电流数据
CAN_ID_VOLTAGE = 0x202    # 电压数据
CAN_ID_SPEED = 0x203      # 速度数据
CAN_ID_CONTROL = 0x204    # 控制指令

# 故障码定义
FAULT_NONE = 0x0000       # 正常
FAULT_OVER_CURRENT = 0x0001  # 过流
FAULT_OVER_VOLTAGE = 0x0002  # 过压
FAULT_OVER_TEMP = 0x0004     # 过温
FAULT_STALL = 0x0008         # 堵转
FAULT_COMM = 0x0010          # 通信故障

# 控制命令定义
CMD_START = 0x01          # 启动电机
CMD_STOP = 0x02          # 停止电机
CMD_SPEED = 0x03         # 设置速度
CMD_MODE = 0x04          # 设置模式
CMD_CLEAR_FAULT = 0x05    # 清除故障
CMD_JOG = 0x06           # 点动运行
CMD_POSITION = 0x07      # 位置控制
CMD_AUTO_TUNING = 0x08   # 参数自学习
CMD_INERTIA_ID = 0x09    # 惯量识别
CMD_RESONANCE_DET = 0x0A # 共振检测

# 运行模式
MODE_SPEED = 0x01        # 速度模式
MODE_TORQUE = 0x02       # 转矩模式
MODE_POSITION = 0x03     # 位置模式
MODE_HOME = 0x04         # 回零模式

# 参数限值
MAX_CURRENT = 200.0      # 最大电流(A)
MAX_VOLTAGE = 400.0      # 最大电压(V)
MAX_SPEED = 5000        # 最大转速(rpm)
MAX_TEMP = 85.0         # 最高温度(℃) 