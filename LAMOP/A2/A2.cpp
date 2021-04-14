#include <iostream>
#include <fstream>
#include <vector>

#define WORD_LEN 3


void radix_sort(std::string *words_array, int array_size) {
    for(int i = WORD_LEN - 1; i >= 0; --i) {
        std::vector<std::string> buckets[58];
        int current_bucket_index;
        for (int j = 0; j < array_size; j++) {
            current_bucket_index = words_array[j][i] - 'A';
            buckets[current_bucket_index].push_back(words_array[j]);
        }
        int index = 0;
        for (auto & bucket : buckets) {
            for (auto & letter : bucket) {
                words_array[index++] = letter;
            }
        }
    }
}


int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    int size;
    fin >> size;
    auto *array = new std::string[size];
    for (int i = 0; i < size; i++) {
        fin >> array[i];
    }

    radix_sort(array, size);

    for (int i = 0; i < size; i++) {
        fout << array[i] << "\n";
    }

    return 0;
}
