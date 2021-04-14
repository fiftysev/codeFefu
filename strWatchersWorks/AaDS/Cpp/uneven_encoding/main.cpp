#include <iostream>
#include <fstream>

#define MAX_ALPHABET_LEN 256



int* generate_compressed_alphabet(std::string& text) {
    int *alphabet = new int[MAX_ALPHABET_LEN];
    for(int i = 0; i < MAX_ALPHABET_LEN; i++) {
        alphabet[i] = 0;
    }
    for(char letter : text) {
        alphabet[letter]++;
    }
    return alphabet;
}

int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    std::string text;
    fin >> text;
    int* alphabet = generate_compressed_alphabet(text);

    for (int i = 0; i < MAX_ALPHABET_LEN; i++) {
        if(alphabet[i]) {
            fout << char(i) << ":" << alphabet[i] << std::endl;
        }
    }
}