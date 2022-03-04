import serial
ser = serial.Serial()
ser.baudrate = 115200
ser.port = 'COM5'
ser.open()
a = [65,66,67,68]
byte_array = bytearray(a)
while 1:
    a = int(input())
    byte_data = a.to_bytes(4,'little')
    #print(byte_data)
    ser.write(byte_data)
    s = ser.read(2)
    print(s)