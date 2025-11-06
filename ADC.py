import serial
import time




port_name = 'COM3'
baud_rate = 4800
data = []
times = []

try:
    ser = serial.Serial(port_name, baud_rate)
    print(f"Connected to {port_name}.")
    time.sleep(2)
    
    while True:
        if ser.in_waiting > 0:
            msg = ser.readline().decode().replace('\x00', '')
            if msg == "START_READING\n":
                print("Sampling data...")
                t0 = time.time()
                while 1:
                    if ser.in_waiting > 0:
                        msg = ser.readline().decode().replace('\x00', '')
                        if (msg == "STOP_READING\n"):
                            break
                        msg2 = msg.replace('\n', '').lstrip('0')
                        if msg2 == '':
                            data.append(0)
                        else:
                            data.append(int(msg2))
                        times.append(time.time() - t0)
                print(data)
                print(times)
            else:
                print(msg)
            continue
        time.sleep(0.1)
except serial.SerialException as e:
    print(f"Error opening or communicating with serial port: {e}.")
except KeyboardInterrupt:
    print("Exiting.")
finally:
    ser.close()
    print("Serial port closed.")