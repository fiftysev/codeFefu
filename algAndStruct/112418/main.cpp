#include <fstream>
#include <string>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

void processFunction();
string cryptCaesar(string line, int k);



int main() {
    processFunction();
}

void processFunction() {
    string line;
    int cryptIndex = 1;
    while(getline(in, line)){
        out << cryptCaesar(line, cryptIndex++) << '\n';
    }
}

string cryptCaesar(string line, int k) {
    string result;
    for (char i : line) {
        char temp = i;
        if (temp >= 'a' && temp <= 'z'){
            temp = char(int(temp + k - 97) % 26 + 97);
            result += temp;
        }
        else if (temp >= 'A' && temp <= 'Z') {
            temp = char(int(temp + k - 65) % 26 + 65);
            result += temp;
        }
        else result += temp;
    }
    return result;
}