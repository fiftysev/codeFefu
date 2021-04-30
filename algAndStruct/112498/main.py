import re


def operate(a, b, oper):
    if oper == '+':
        return a + b
    elif oper == '-':
        return a - b
    elif oper == '/':
        return a // b
    else:
        return a * b


def from_infix_to_postfix():
    priority = {
        '*': 3,
        '/': 3,
        '+': 2,
        '-': 2,
        '(': 1,
    }
    text = input().strip()
    expression_infix = re.split("([+*/()-])", text)
    postfix_expr = list()
    operator_stack = list()
    for element in expression_infix:
        if element == '':
            continue
        elif element.isdecimal():
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
    return " ".join(postfix_expr)


print(from_infix_to_postfix())
