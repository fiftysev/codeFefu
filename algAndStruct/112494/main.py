from math import floor


def operate(a, b, oper):
    if oper == '+':
        return a + b
    elif oper == '-':
        return a - b
    elif oper == '/':
        return floor(a / b)
    else:
        return a * b


expression = input().split()
stack = list()
for element in expression:
    if element.isdecimal():
        stack.append(int(element))
    elif element in '+-/*' and len(stack) >= 2:
        b = stack.pop()
        a = stack.pop()
        if element == '/' and b == 0:
            print("ERROR")
            exit()
        else:
            stack.append(operate(a, b, element))
    else:
        print("ERROR")
        exit()
print("ERROR") if len(stack) > 1 else print(int(stack[0]))
exit()
