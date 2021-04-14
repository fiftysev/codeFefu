import tkinter as tk


def handler(func):
    def wrapper(*args):
        def wrapper2(event):
            func(*args, event)
        return wrapper2
    return wrapper


@handler
def change_my_and_buttons_life(values_arr, row_index, column_index, event):
    values_arr[row_index][column_index] = int(not values_arr[row_index][column_index])
    event.widget['text'] = not event.widget['text']

    with open("data.txt", 'w') as out:
        for line in values_arr:
            for num in line:
                out.write(str(num) + " ")
            out.write("\n")


file = open('data.txt', 'r')
button_values_arr = [[int(ch) for ch in line.split()] for line in file]
print(button_values_arr)
button_arr = [list() for i in range(len(button_values_arr))]


window = tk.Tk()
window.title = "tkinterHell"
for cur_row_index in range(len(button_values_arr)):
    for cur_column_index in range(len(button_values_arr[cur_row_index])):
        button_arr[cur_row_index].append(tk.Button(text=button_values_arr[cur_row_index][cur_column_index]))
        button_arr[cur_row_index][cur_column_index].grid(row=cur_row_index, column=cur_column_index,
                                                         ipadx=10, ipady=10, padx=5, pady=5)

        command = change_my_and_buttons_life(button_values_arr, cur_row_index, cur_column_index)
        button_arr[cur_row_index][cur_column_index].bind('<Button-1>', command)

tk.mainloop()
