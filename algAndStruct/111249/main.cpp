#include <iostream>
using namespace std;


int oddCheck (string line) {
    int res = 0;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == '1') res++;
    }
    return res % 2;
}

int main() {
    string line;
    getline(cin, line);
    if (line.length() > 1){
        if (line[line.length() - 1] == 'e') {
            line.replace(line.length() - 1, 1, 1 ,'0');
        }
        else line.replace(line.length() - 1, 1, 1 ,'1');
        }
    else {
        if (line == "e") {
            line = "0";
        }
        else line = '1';
    }
    oddCheck(line) ? line.replace(line.length() - 1, 1, 1 ,'1') : line.replace(line.length() - 1, 1, 1 ,'0');
    cout << line;
    return 0;
}