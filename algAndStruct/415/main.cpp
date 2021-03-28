#include <iostream>
#include <string>
using namespace std;
string caesarDecrypt (string line, int k) {
    string result;
    for (char i : line) {
        char temp = i;
        temp -= k;
        if (temp < 'A') {
            temp = temp + 'Z' - 'A' + 1;
            result += temp;
        }
        else result += temp;
    }
    return result;
}

int main() {
    string str;
    cin >> str;
    int k;
    cin >> k;
    cout << caesarDecrypt(str,k);
}