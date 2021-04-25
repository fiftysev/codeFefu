#include <bits/stdc++.h>

#define ALPHABET_LEN 78
#define ull unsigned long long

using namespace std;

ull h1(string line, ull hash_code_range) {
    ull key = line[0];
    for (int i = 1; i < line.length(); i++) {
        key = (key * ALPHABET_LEN + line[i]) % hash_code_range ;
    }
    return key;
}

void map_emulator() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int lines_count;
    int hash_code_range;
    string cur;
    cin >> hash_code_range >> lines_count;
    getline(cin, cur);
    for (int i = 0; i < lines_count; ++i) {
        getline(cin, cur);
        cout << h1(cur, hash_code_range) << endl;
    }

}
int main() {
   map_emulator();
}

