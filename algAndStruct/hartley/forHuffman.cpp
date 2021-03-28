#include <iostream>
#include <string>
#include <map>
#include <fstream>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

char* decToBin(int x, int wordLength ) {
    auto* num = new char[wordLength];
    for (int i = wordLength - 1; i >= 0; i--) {
        num[i] = (x & 1) + '0';
        x >>= 1;
    }
    return num;
}
 
int main() 
{
    string s;
    getline(in, s);
    map <char, int> m;
    for (int i = 0; i < s.size(); i++) m[s[i]]++;
    for (auto element = m.begin(); element != m.end(); element++) {
        cout << element->first << " " << element->second << endl;
    }
}