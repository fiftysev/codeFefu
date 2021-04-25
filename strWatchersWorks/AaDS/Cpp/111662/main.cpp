#include <bits/stdc++.h>
using namespace std;

bool inserts(string& line, char goal) {
    return any_of(line.begin(), line.end(), goal);
}

int main() {
    map <int, string> numpad;
    numpad[2] = "abc";
    numpad[3] = "def";
    numpad[4] = "ghi";
    numpad[5] = "jkl";
    numpad[6] = "mno";
    numpad[7] = "pqrs";
    numpad[8] = "tuv";
    numpad[9] = "wxyz";
    map <string, bool> tele_numbers;
    int companies_count;
    cin >> companies_count;
    string current_company;
    map <int, string>::iterator it;
    for (int i = 0; i < companies_count; ++i) {
        cin >> current_company;
        for (auto letter: current_company) {
            for (it = numpad.begin(); it != numpad.end(); ++it) {

            }
        }
    }
    return 0;
}