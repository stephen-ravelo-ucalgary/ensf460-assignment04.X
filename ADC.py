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
            msg = ser.readline().decode()
            print(repr(msg))
            if msg == "START_READING\n":
                t0 = time.time()
                while 1:
                    if ser.in_waiting > 0:
                        msg = ser.readline().decode()
                        if (msg == "STOP_READING\n"):
                            break
                        data.append(msg)
                        times.append(time.time() - t0)
                print(data)
                print(times)
            continue
        time.sleep(0.1)
except serial.SerialException as e:
    print(f"Error opening or communicating with serial port: {e}.")
except KeyboardInterrupt:
    print("Exiting.")
finally:
    ser.close()
    print("Serial port closed.")