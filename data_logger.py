import csv
import json
import time
from datetime import datetime
import threading
from queue import Queue
import sqlite3
from utils.constants import *

class DataLogger:
    def __init__(self, db_path='motor_data.db'):
        self.db_path = db_path
        self.recording = False
        self.data_queue = Queue()
        self._init_db()
        
    def _init_db(self):
        conn = sqlite3.connect(self.db_path)
        c = conn.cursor()
        
        # 创建数据表
        c.execute('''CREATE TABLE IF NOT EXISTS motor_data
                    (timestamp REAL,
                     msg_id INTEGER,
                     data BLOB,
                     parsed_data TEXT)''')
        
        conn.commit()
        conn.close()
        
    def start_recording(self):
        self.recording = True
        threading.Thread(target=self._record_loop, daemon=True).start()
        
    def stop_recording(self):
        self.recording = False
        
    def add_message(self, msg, parsed_data):
        if self.recording:
            self.data_queue.put((msg, parsed_data))
            
    def _record_loop(self):
        conn = sqlite3.connect(self.db_path)
        c = conn.cursor()
        
        while self.recording:
            try:
                msg, parsed_data = self.data_queue.get(timeout=1.0)
                c.execute('INSERT INTO motor_data VALUES (?, ?, ?, ?)',
                         (msg.timestamp, msg.arbitration_id, 
                          bytes(msg.data), json.dumps(parsed_data)))
                conn.commit()
            except:
                continue
                
        conn.close()
        
    def export_csv(self, start_time, end_time, filename):
        conn = sqlite3.connect(self.db_path)
        c = conn.cursor()
        
        with open(filename, 'w', newline='') as csvfile:
            writer = csv.writer(csvfile)
            writer.writerow(['Timestamp', 'ID', 'Data', 'Parsed Data'])
            
            for row in c.execute('''SELECT * FROM motor_data 
                                  WHERE timestamp BETWEEN ? AND ?''',
                               (start_time, end_time)):
                writer.writerow(row)
                
        conn.close()
        
    def get_replay_data(self, start_time, end_time):
        conn = sqlite3.connect(self.db_path)
        c = conn.cursor()
        
        data = []
        for row in c.execute('''SELECT * FROM motor_data 
                              WHERE timestamp BETWEEN ? AND ?
                              ORDER BY timestamp''',
                           (start_time, end_time)):
            data.append(row)
            
        conn.close()
        return data 