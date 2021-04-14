fin = open("input.txt")
shift = 1
for line in fin:
    res = str()
    for i in range(len(line.strip())):
        if line[i].isalpha():
            if line[i].islower():
                res += chr((ord(line[i]) + shift - ord('a')) % 26 + ord('a'))
            elif line[i].isupper():
                res += chr((ord(line[i]) + shift - ord('A')) % 26 + ord('A'))
        else:
            res += line[i]
    shift += 1
    print(res)
