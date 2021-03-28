#include <fstream>
#include <vector>
#include <string>
using namespace std;

int bucketSort (string* words, int amountOfWords, int iter) {
    vector <string> buckets[58];
    for (int i = 0; i < amountOfWords; i++) {
        int bucketIndex = words[i][iter] - 65;
        buckets[bucketIndex].push_back(words[i]);
    }
    int indexForArr = 0;
    for (int i = 0; i < 58; i++) 
        for (int j = 0; j < buckets[i].size(); j++) 
            words[indexForArr++] = buckets[i][j];
    iter--;
    if (iter == -1) return 0;
    else bucketSort(words, amountOfWords, iter);
}

int main() {
    fstream fin ("input.txt");
    fstream fout("output.txt");
    int amountOfWords; fin >> amountOfWords;
    string* words = new string[amountOfWords];
    for (int i = 0; i < amountOfWords; i++)
        fin >> words[i];
    bucketSort(words, amountOfWords, 2);
    for (int i = 0; i < amountOfWords; i++)
        fout << words[i] << "\n";
    return 0;
}