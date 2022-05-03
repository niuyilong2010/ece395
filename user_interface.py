import serial
import tkinter as tk


# ser = serial.Serial()
# ser.baudrate = 115200
# ser.port = 'COM5'
# ser.open()
# a = [65,66,67,68]
# byte_array = bytearray(a)
# while 1:
#     a = int(input())
#     byte_data = a.to_bytes(4,'little')
#     #print(byte_data)
#     ser.write(byte_data)
#     s = ser.read(2)
#     print(s)


# ser = serial.Serial()
# ser.baudrate = 115200
# ser.port = 'COM5'
# ser.open()

# root = tk.Tk()
# frm = tk.Frame(root)
# frm.pack()
# step_num = 0
# dir = 0

# def button_press():
#     global step_num
#     step_num = int(entry.get())
#     if dir == 1:
#         step_num += (1<<16)
#     byte_data = step_num.to_bytes(4,'little')
#     ser.write(byte_data)
#     s = ser.read(2)
#     #print(s)
#     if dir == 1:
#         step_num -= (1<<16)
#     label["text"] = step_num

# def button2_press():
#     global dir
#     dir = 1 - dir
#     button2["text"] = "dir = " + str(dir)

# button2 = tk.Button(root, text ="dir = " + str(dir), command = button2_press)
# button2.pack()
# entry= tk.Entry(root, width= 20)
# entry.focus_set()
# entry.pack()
# button = tk.Button(root, text ="   send   ", command = button_press)
# button.pack()
# label = tk.Label(root, text = step_num)
# label.pack()
# root.mainloop()

ser = serial.Serial()
ser.baudrate = 115200
ser.port = 'COM5'
ser.open()

root = tk.Tk()
frm = tk.Frame(root)
frm.pack()
step_num = 0
step_num_bot = 0
dir = 0
dir_bot = 0

def button_press():
    global step_num
    global step_num_bot
    step_num = int(entry.get())
    step_num_bot = int(entrybot.get())
    step_num = step_num + (int(entrybot.get()) << 32)
    if dir == 1:
        step_num += (1<<16)
    if dir_bot == 1:
        step_num += (1<<48)
    byte_data = step_num.to_bytes(8,'little')
    print(byte_data)
    ser.write(byte_data)

    step_num = step_num - (int(entrybot.get()) << 32)
    s = ser.read(2)
    print(s)
    if dir == 1:
        step_num -= (1<<16)
    if dir_bot == 1:
        step_num -= (1<<48)
    label["text"] = "top step num = " + str(step_num)
    label_bot["text"] = "bot step num = " + str(step_num_bot)

def button2_press():
    global dir
    dir = 1 - dir
    button2["text"] = "dir = " + str(dir)

def button3_press():
    global dir_bot
    dir_bot = 1 - dir_bot
    button3["text"] = "dir_bot = " + str(dir_bot)

button2 = tk.Button(root, text ="dir = " + str(dir), command = button2_press)
button2.pack()
entry= tk.Entry(root, width= 20)
entry.focus_set()
entry.pack()
button3 = tk.Button(root, text ="dir_bot = " + str(dir_bot), command = button3_press)
button3.pack()
entrybot= tk.Entry(root, width= 20)
entrybot.focus_set()
entrybot.pack()
button = tk.Button(root, text ="   send   ", command = button_press)
button.pack()
label = tk.Label(root, text = "top step num = 0")
label.pack()
label_bot = tk.Label(root, text = "bot step num = 0")
label_bot.pack()
root.mainloop()