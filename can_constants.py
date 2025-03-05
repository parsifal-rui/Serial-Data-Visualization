# CAN 消息 ID 定义
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

# 控制命令类型
CMD_TYPE_SPEED = 0x01     # 速度控制
CMD_TYPE_POSITION = 0x02  # 位置控制
CMD_TYPE_TORQUE = 0x03    # 转矩控制
CMD_TYPE_STOP = 0x04      # 停止命令 