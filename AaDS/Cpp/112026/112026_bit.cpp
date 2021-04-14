#include <iostream>
#include <fstream>
#include <string>


std::ifstream in("input.txt");
std::ofstream out("output.txt");

int count_hamming_distance(char first_char, char second_char) {
    char mask = 1;
    int count = 0;
    for (size_t i = 0; i < 8; i++) {
        count += ((first_char & mask) >> i != (second_char & mask) >> i);
        mask <<= 1;
    }
    return count;
}

int main() {
    std::string word1, word2;

    getline(in, word1);
    getline(in, word2);

    int count = 0;
    for (size_t i = 0; i < word1.length(); i++) {
        count = count_hamming_distance(word1[i], word2[i]);
        out << count << std::endl;
    }
}