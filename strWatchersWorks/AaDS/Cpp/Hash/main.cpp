#include <bits/stdc++.h>

#define ALPHABET_LEN 78
#define ull long long

using namespace std;

ull h1(string line, ull hash_code_range) {
    ull key = line[0];
    for (int i = 1; i < line.length(); i++) {
        key = (key * ALPHABET_LEN + line[i]) % hash_code_range ;
    }
    return key;
}

bool inserts(int *map, ull index) {
    return map[index];
}

void map_emulator() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    ull hash_code_range;
    cin >> hash_code_range;
    int *map_emu = new int[hash_code_range];
    for (ull i = 0; i < hash_code_range; ++i){
        map_emu[i] = false;
    }
    string cur_line;
    getline(cin, cur_line);

int main() {
   map_emulator();
}

