#include <iostream>
#include <fstream>

std::ifstream in("input.txt");
std::ofstream out("output.txt");

int main () { 
    std::string word1, word2;

    in >> word1;
    in >> word2;

    int count = 0;

    for (size_t i = 0; i < word1.length(); i++) {
        if (word1[i] != word2[i]) count++;
    } 

    out << count << std::endl;
}