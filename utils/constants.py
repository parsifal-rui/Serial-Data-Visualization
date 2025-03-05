# CAN ID定义
MOTOR_CURRENT_ID = 0x201    # 三相电流数据
MOTOR_VOLTAGE_ID = 0x202    # 三相电压数据
MOTOR_SPEED_ID = 0x203      # 速度数据
MOTOR_POSITION_ID = 0x204   # 位置数据
MOTOR_CONTROL_ID = 0x200    # 控制命令

# 控制命令定义
CMD_STOP = 2       # 停止电机
CMD_START = 1       # 启动电机
CMD_SPEED_UP = 3   # 加速
CMD_SPEED_DOWN = 4 # 减速
CMD_REVERSE = 5    # 反转
CMD_SPEED_SET = 6  # 设置速度
CMD_POSITION_SET = 0x03    # 设置位置
CMD_MODE_SET = 0x04        # 设置模式

# 电机状态定义
STATUS_STOP = 0x00         # 停止状态
STATUS_RUNNING = 0x01      # 运行状态
STATUS_ERROR = 0x02        # 错误状态

# 故障码定义
FAULT_NONE = 0x0000       # 正常
FAULT_OVER_CURRENT = 0x0001  # 过流
FAULT_OVER_VOLTAGE = 0x0002  # 过压
FAULT_OVER_TEMP = 0x0004     # 过温
FAULT_STALL = 0x0008         # 堵转
FAULT_COMM = 0x0010          # 通信故障

# 运行模式
MODE_SPEED = 0x01        # 速度模式
MODE_TORQUE = 0x02       # 转矩模式
MODE_POSITION = 0x03     # 位置模式
MODE_HOME = 0x04         # 回零模式

# 参数限值
MAX_CURRENT = 200.0      # 最大电流(A)
MAX_VOLTAGE = 400.0      # 最大电压(V)
MAX_SPEED = 3000         # 最大转速 ±3000rpm
MAX_TEMP = 85.0         # 最高温度(℃)

# CAN 消息 ID
CAN_ID_CONTROL = 0x200  # 控制命令ID

# 电机数据 ID
CAN_ID_IA = 0x100       # Ia 电流
CAN_ID_IB = 0x101       # Ib 电流
CAN_ID_IC = 0x102       # Ic 电流
CAN_ID_ID = 0x103       # Id 电流
CAN_ID_IQ = 0x104       # Iq 电流
CAN_ID_SPEED_REF = 0x105  # 速度参考值
CAN_ID_SPEED_FED = 0x106  # 速度反馈值
CAN_ID_POSITION = 0x107   # 位置反馈值

# 电机参数
MIN_SPEED = -3000 # 最小转速 (rpm) 