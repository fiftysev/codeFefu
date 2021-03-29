import tkinter as tk
from functools import partial


def change_my_and_buttons_life(event):
    # global button_values_arr
    # values_index = str(event.widget.cget('textvariable')).split()
    # # print(dir(event.widget['textvariable']))
    # button_values_arr[int(values_index[0])][int(values_index[1])] = int(not button_values_arr[int(values_index[0])][int(values_index[1])])
    event.widget['text'] = 1
    print(event.widget['text'])


file = open('input.txt', 'r')
button_values_arr = [[int(ch) for ch in line.split()] for line in file]
print(button_values_arr)
button_arr = [list() for i in range(len(button_values_arr))]


window = tk.Tk()
window.setvar()
window.title = "Program"
for row_index in range(len(button_values_arr)):
    for column_index in range(len(button_values_arr[row_index])):
        button_arr[row_index].append(tk.Button(text=button_values_arr[row_index][column_index]))
        button_arr[row_index][column_index].grid(row=row_index, column=column_index,
                                                 ipadx=10, ipady=10, padx=5, pady=5)
        button_arr[row_index][column_index].bind('<Button-1>', change_my_and_buttons_life)




tk.mainloop()
