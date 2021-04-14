input_line = input()

mod = input_line[-1]
even_bits_count = 0
for bit_index in range(len(input_line) - 1):
    cur_bit = int(input_line[bit_index])
    even_bits_count += cur_bit

print(input_line[:-1], end="")
if mod == 'e':
    print(int(not even_bits_count % 2 == 0))
else:
    print(int(even_bits_count % 2 == 0))
