import tkinter as tk

root = tk.Tk()
frm = tk.Frame(root)
frm.pack()
step_num = 0
dir = 0

def button_press():
    global step_num
    step_num = int(entry.get())
    label["text"] = step_num

def button2_press():
    global dir
    dir = 1 - dir
    button2["text"] = "dir = " + str(dir)

button2 = tk.Button(root, text ="dir = " + str(dir), command = button2_press)
button2.pack()
entry= tk.Entry(root, width= 20)
entry.focus_set()
entry.pack()
button = tk.Button(root, text ="   send   ", command = button_press)
button.pack()
label = tk.Label(root, text = step_num)
label.pack()
root.mainloop()
