# CAN ID定义
CAN_ID_CURRENT = 0x201    # 电流数据
CAN_ID_VOLTAGE = 0x202    # 电压数据
CAN_ID_SPEED = 0x203      # 速度数据
CAN_ID_CONTROL = 0x200    # 控制命令ID
CAN_ID_POSITION = 0x205   # 位置数据
CAN_ID_STATUS = 0x201     # 状态数据ID

# 故障码定义
FAULT_NONE = 0x0000       # 正常
FAULT_OVER_CURRENT = 0x0001  # 过流
FAULT_OVER_VOLTAGE = 0x0002  # 过压
FAULT_OVER_TEMP = 0x0004     # 过温
FAULT_STALL = 0x0008         # 堵转
FAULT_COMM = 0x0010          # 通信故障

# 控制命令
CMD_START = 0x01      # 启动
CMD_STOP = 3          # 停止
CMD_SPEED_UP = 1     # 加速
CMD_SPEED_DOWN = 2   # 减速
CMD_REVERSE = 4      # 反转

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