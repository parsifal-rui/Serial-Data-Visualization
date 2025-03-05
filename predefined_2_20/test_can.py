import can
import threading

def receive_can_messages(bus):
    while True:
        message = bus.recv(timeout=0)  # 阻塞，直到接收到消息
        if message:
            print(f"Received: {message.data.decode()}")  # 打印接收到的消息

def send_command(bus):
    while True:
        user_input = input("Enter command (e.g., LED1/2 ON/OFF) or 'exit' to quit: ").strip()  # 获取用户输入
        if user_input.lower() == 'exit':  # 输入 'exit' 以退出
            break
        # 将用户输入格式化为 CAN 消息
        command = user_input.upper()  # 转换为大写形式
        if len(command) <= 8:
            message = can.Message(arbitration_id=0x123, data=command.encode(), is_extended_id=False)
            bus.send(message)
            print(f"Sent: {command}")
        print("Message is too long.")

def main():
    bus = can.interface.Bus(channel='PCAN_USBBUS1', interface='pcan', bitrate=500000)  # 根据具体接口修改参数

    # 创建线程处理接收消息
    receive_thread = threading.Thread(target=receive_can_messages, args=(bus,))
    receive_thread.start()

    # 发送消息
    send_command(bus)

    # 等待接收线程结束
    receive_thread.join()

if __name__ == "__main__":
    main()
