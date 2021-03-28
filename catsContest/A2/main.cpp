#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <cctype>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

int bucketSort (string *array, int N, int iter) {
    vector<string> buckets[58];
    int bucketsIndex;
    for (int i = 0; i < N; i++) {
        bucketsIndex = array[i][iter] - 65;
        buckets[bucketsIndex].push_back(array[i]);
    }
    int index = 0;
    for (int i = 0; i < 58; i++) {
        for (int j = 0; j < buckets[i].size(); j++) {
            array[index++] = buckets[i][j];
        }
    }
    if (iter == 0) {
        return 0;
    }
    else {
        iter--;
        return bucketSort(array, N, iter);
    }
}

int main() {
    int N;
    in >> N;
    string *array = new string[N];
    for (int i = 0; i < N; i++) {
        in >> array[i];
    }
    bucketSort(array, N, 2);
    for (int i = 0; i < N; i++) {
        out << array[i] << "\n";
    }
    return 0;
}