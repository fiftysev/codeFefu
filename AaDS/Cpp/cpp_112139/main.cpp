#include <iostream>
#include <vector>

using namespace std;

int min(int a, int b, int c) {return min(min(a, b), c);}

int count_distance(string line1, string line2, int len1, int len2) {
    if (len1 > len2) {
        int tmp = len1;
        len1 = len2;
        len2 = tmp;
        string line_tmp = line1;
        line1 = line2;
        line2 = line_tmp;
    }
    vector<int> current_row(len1 + 1);
    for (int i = 0; i < len1 + 1; ++i) {
        current_row[i] = i;
    }

    for (int i = 1; i < len2 + 1; ++i) {
        vector <int> previous_row(len1 + 1);
        previous_row = current_row;
        current_row[0] = i;
        for (int tmp_i = 1; tmp_i < len1 + 1; ++tmp_i) {
            current_row[tmp_i] = 0;
        }
        for (int j = 1; j < len1 + 1; ++j) {
            int add = previous_row[j] + 1;
            int del = current_row[j - 1] + 1;
            int change = previous_row[j - 1];

            if (line1[j - 1] != line2[i - 1]) {
                ++change;
            }
            current_row[j] = min(add, del, change);
        }
    }
    return current_row[len1];
}


int main() {
    int len1, len2;
    string line1, line2;
    cin >> len1 >> line1 >> len2 >> line2;
    cout << count_distance(line1, line2, len1, len2);
}
