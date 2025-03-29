import serial
import time

# Change COM3 to your actual port (check Device Manager)
ser = serial.Serial('COM3', 38500, timeout=2)

while True:
    data = ser.readline().decode(errors='replace').strip()  # Replaces invalid characters with placeholder (usually '?')
    if data:
        print(data)
    ser.write("10123".encode('utf-8'))  
    time.sleep(1)  # Delay 1 second before the next read