def correct_split(text: str):

    for el in text:
        if el.isalpha():


def shift(c: chr, length: int):
    if c.is_alpha():
        if c.is_lower():
            return chr((c - ord('a') + length) % 26 + ord('a'))
        else:
            return chr((c - ord('A') + length) % 26 + ord('A'))

