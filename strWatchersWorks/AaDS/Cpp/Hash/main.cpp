#include <bits/stdc++.h>

#define ALPHABET_LEN 128
#define ull unsigned long long

using namespace std;

ull h1(string line, ull hash_code_range) {
    ull key = int(line[0]) * ALPHABET_LEN + int(line[1]);
    for (int i = 2; i < line.length(); ++i) {
        key = (key * ALPHABET_LEN + int(line[i])) % hash_code_range;
    }
    return key;
}

bool inserts(int *map, ull index) {
    return map[index];
}

ull hash_generator(string line, ull hash_code_range, int *map) {
    ull hash_code = h1(line, hash_code_range);
    while (inserts(map, hash_code)) {
        ++hash_code;
    }
    map[hash_code] = true;
    return hash_code;
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
    getline(cin, cur_line);
    while (cur_line != "0") {
        getline(cin, cur_line);
        cout << h1(cur_line, hash_code_range) << endl;
    }
}

int main() {
   map_emulator();
}
