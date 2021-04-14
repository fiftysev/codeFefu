def read_file(file_path: str):
    with open(file_path, 'r') as fin:
        return fin.readline()


def count_all_elements(data: str):
    alphabet = [0 for _ in range(256)]
    for element in data:
        alphabet[int(element)] += 1

    print()


print(read_file("input.txt"))
