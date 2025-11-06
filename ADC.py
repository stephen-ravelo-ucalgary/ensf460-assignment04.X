'''
File Name: ADC.py
Assignment: Assignment 4
Lab Section: B02
Completed by: Stephen Ravelo, Aaron Lauang, Alexa Gonzalez
Submission Date: November 7, 2025
 '''

import serial
import time
import pandas as pd
import matplotlib.pyplot as plt

port_name = '/dev/tty.usbserial-0001'
# port_name = 'COM3'
baud_rate = 4800
buffer = []
voltage = []
sample_times = []

try:
    # Connect python program to USB UART
    ser = serial.Serial(port_name, baud_rate)
    print(f"Connected to {port_name}.")
    time.sleep(2)
    
    while True:
        if ser.in_waiting > 0:
            msg = ser.readline().decode().replace('\x00', '').replace('\n', '')
            if msg == "START_READING":
                print("Sampling data...")
                t0 = time.time()

                # Receive ADC values from the C program that is transmitted to the UART
                while 1:
                    if ser.in_waiting > 0:
                        sample_msg = ser.readline().decode().replace('\x00', '').replace('\n', '')
                        if (sample_msg == "STOP_READING"):
                            break
                        buffer_data = sample_msg.lstrip('0')
                        if buffer_data == '':
                            buffer.append(0)
                            voltage.append(0)
                        else:
                            buffer.append(int(buffer_data))
                            voltage.append(float(buffer_data) * 0.00322265625)
                        sample_times.append(time.time() - t0)
                
                # Print buffer, voltage, and time values into the terminal
                print("Digital ADC Buffer Values:")
                print(buffer)
                print("ADC Input Voltage Values:")
                print(voltage)
                print("Sample Times:")
                print(sample_times)

                # Save data into a CSV file
                df = pd.DataFrame({
                    'Sample Time (seconds)': sample_times,
                    'Digital ADC Buffer': buffer,
                    'ADC Input Voltage (volts)': voltage
                })
                df.to_csv('data.csv', index=False)

                # Output the graphs of buffer vs. time, and voltage vs. time
                fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(8, 6), sharex=True)

                ax1.plot(sample_times, buffer, 'b-o', label='Buffer')
                ax1.set_ylabel('Digital ADC Buffer')
                ax1.set_xlabel('Sample Time (seconds)')
                ax1.set_title('Digital ADC Buffer vs. Sample Time')
                ax1.legend()
                ax1.grid(True)

                ax2.plot(sample_times, voltage, 'r-o', label='Voltage')
                ax2.set_ylabel('ADC Input Voltage (volts)')
                ax2.set_xlabel('Sample Time (seconds)')
                ax2.set_title('ADC Input Voltage vs. Sample Time')
                ax2.legend()
                ax2.grid(True)

                plt.tight_layout()
                plt.show()

            else:
                print(msg)

            # Clear data
            buffer.clear()
            voltage.clear()
            sample_times.clear()

            continue
        time.sleep(0.1)
except serial.SerialException as e:
    print(f"Error opening or communicating with serial port: {e}.")
except KeyboardInterrupt:
    print("Exiting.")
finally:
    ser.close()
    print("Serial port closed.")
