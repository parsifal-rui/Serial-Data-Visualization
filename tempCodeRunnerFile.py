
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