from flask import Flask, render_template, jsonify
import random
import serial
import serial.tools.list_ports

app = Flask(__name__)

# Simulate serial data reading (replace with actual serial data reading)
def read_serial_data():
    # Handle serial communication with proper exception handling in real implementation
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
    return render_template('testcharts.html')

@app.route('/data')
def data():
    # Fetch the motor data (from serial communication in real-world case)
    serial_data = read_serial_data()
    return jsonify(serial_data)

if __name__ == '__main__':
    app.run(debug=True, port=5002, threaded=True)
