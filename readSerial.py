import serial
import time

current = time.time()
ser = serial.Serial('COM4', baudrate=115200)
f = open("test.txt", "w")
notInterupt = True
while ((time.time() - current) <= 5):
    print(time.time() - current)
    try:
        data_raw = ser.readline()
        new_data_raw = int(data_raw.decode()[:-1])
        real = (new_data_raw * (3.3/4095))
        f.write(f"{time.time() - current};{real}\n")
    except KeyboardInterrupt:
        notInterupt = False
        ser.close()
ser.close()

