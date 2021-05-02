import re
from math import *


def operate(a, b, oper):
    if oper == '+':
        return a + b
    elif oper == '-':
        return a - b
    elif oper == '/':
        return a / b
    elif oper == '*':
        return a * b
    elif oper == 'sin':
        return sin(a)
    elif oper == 'cos':
        return cos(a)
    elif oper == 'sqrt':
        return sqrt(a)
    elif oper == 'abs':
        return abs(a)


def from_infix_to_prefix(expression_infix, vars):
    priority = {
        'sin': 4,
        'cos': 4,
        'abs': 4,
        'sqrt': 4,
        '*': 3,
        '/': 3,
        '+': 2,
        '-': 2,
        '(': 1,
    }
    postfix_expr = list()
    operator_stack = list()
    for element in expression_infix:
        if element == '':
            continue
        elif (element.isdecimal() or element.isalpha()) and element not in ['sin', 'cos', 'sqrt', 'abs']:
            if element in vars.keys():
                postfix_expr.append(vars[element])
            else:
                postfix_expr.append(element)
        elif element == '(':
            operator_stack.append(element)
        elif element == ')':
            top_op = operator_stack.pop()
            while top_op != '(':
                postfix_expr.append(top_op)
                top_op = operator_stack.pop()
        else:
            while (len(operator_stack) != 0) and (priority[operator_stack[len(operator_stack) - 1]] >= priority[element]):
                postfix_expr.append(operator_stack.pop())
            operator_stack.append(element)
    while len(operator_stack) > 0:
        postfix_expr.append(operator_stack.pop())
    return postfix_expr


def postfix_calc(expression):
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
        elif element in ['cos', 'sin', 'sqrt', 'abs'] and len(stack) >= 1:
            b = stack.pop()
            stack.append(operate(b, 0, element))
        else:
            print("ERROR")
            exit()
    print("ERROR") if len(stack) > 1 else print(
        "{:.3f}".format(float(stack[0])))
    exit()


variables = {}
with open('input.txt', 'r') as finput:
    text = finput.readline().strip()
    inf_expr = re.split("([+*/()-])", text)
    text = finput.read().splitlines()
    for line in text:
        temp = line.split("=")
        variables[temp[0]] = temp[1]

expr = from_infix_to_prefix(inf_expr, variables)
postfix_calc(expr)
