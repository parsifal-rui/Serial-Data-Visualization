from flask import Flask, render_template, jsonify
import random
import serial
import serial.tools.list_ports

app = Flask(__name__)

# Simulate serial data reading (you can replace this with actual serial data reading)
def read_serial_data():
    # Here, you'd use pySerial to connect and read data from the serial port.
    # Simulating some random data for now.
    # Assume there are only 2 motors
    
    motor_data = {
        'Motor_1': {
            'Speed': random.randint(1200, 1500),
            'Voltage': random.uniform(200, 250),
            'Current': random.uniform(5, 10)
        },
        'Motor_2': {
            'Speed': random.randint(1200, 1500),
            'Voltage': random.uniform(200, 250),
            'Current': random.uniform(5, 10)
        }
    }
    return motor_data

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/data')
def data():
    # Fetch the motor data (in real-world case, from serial communication)
    serial_data = read_serial_data()
    return jsonify(serial_data)

if __name__ == '__main__':
    app.run(debug=True, port=5001)
