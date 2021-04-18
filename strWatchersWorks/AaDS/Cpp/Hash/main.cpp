#include <bits/stdc++.h>

#define ALPHABET_LEN 128
#define ull unsigned long long

using namespace std;

ull h1(string word, ull hash_code_range) {
    ull key = int(word[0]);
    for (int i = 1; i < word.length(); ++i) {
        key = (key * ALPHABET_LEN + int(word[i])) % hash_code_range;
    }
    return key;
}

int main() {
    string line;
    ull hc_range;
    getline(cin, line);
    cin >> hc_range;

    cout << h1(line, hc_range);
}
