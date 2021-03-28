#include <iostream>
#include <string>
using namespace std;


int main() {
    string line;
    getline(cin, line);
    if (line.length() > 1){
    if (line[line.length() - 1] == 'e') {
        line.replace(line.length() - 1, 1, 1 ,'1');
    }
    else line.replace(line.length() - 1, 1, 1 ,'0');
    }
    else {
        if (line == "e") {
            line = "0";
        }
        else line = '1';
    }
    cout << line;
}