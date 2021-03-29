# change filename to data

import tkinter as tk


def handler(btn_val_arr, row, column):
    def wrapper(event):
        change_my_and_buttons_life(btn_val_arr, row, column, event)

    return wrapper


def change_my_and_buttons_life(arr, cur_row, cur_column, event):
    arr[cur_row][cur_column] = int(not arr[cur_row][cur_column])
    event.widget['text'] = not event.widget['text']
    with open('data.txt', 'w') as out:
        for row in arr:
            for number in row:
                out.write(str(number) + ' ')
            out.write('\n')


file = open('data.txt', 'r')
button_values_arr = [[int(ch) for ch in line.split()] for line in file]
button_arr = [list() for i in range(len(button_values_arr))]

window = tk.Tk()
window.setvar()
window.title = "Program"
for row_index in range(len(button_values_arr)):
    for column_index in range(len(button_values_arr[row_index])):
        command = handler(button_values_arr, row_index, column_index)
        button_arr[row_index].append(tk.Button(text=button_values_arr[row_index][column_index], height=5, width=5))
        button_arr[row_index][column_index].grid(row=row_index, column=column_index,
                                                 ipadx=10, ipady=10, padx=5, pady=5)
        button_arr[row_index][column_index].bind('<Button-1>', command)

tk.mainloop()
