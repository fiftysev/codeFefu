#include <bits/stdc++.h>

using namespace std;

int ctoint(string &alphabet, char c) {
    for (int i = 0; i < alphabet.length(); ++i) {
        char el = alphabet[i];
        if (el == c) {
            return i;
        }
    }
    return -1;
}

char shift(string &alphabet, int key, char c) {
    int result_index = (ctoint(alphabet, c) + key + 1) % (int)alphabet.length();
    char result = alphabet[result_index];
    return result;
}

string cipher(string &goal_line, string &key) {
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    string result_line;
    int separated_key[key.length()];
    for (int i = 0; i < key.length(); ++i) {
        separated_key[i] = ctoint(alphabet, key[i]);
    }

    for (int i = 0; i < goal_line.length(); ++i) {
        int cur_key_index = i % (int)key.length();
        result_line.push_back(shift(alphabet, separated_key[cur_key_index], goal_line[i]));
    }
    return result_line;
}

int main() {
    string test;
    string key;
    getline(cin, test);
    getline(cin, key);
    string test_result = cipher(test, key);
    cout << test_result << endl;
}