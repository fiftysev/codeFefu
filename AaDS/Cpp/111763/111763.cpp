#include <iostream>
#include <fstream>

using namespace std;
ifstream input ("input.txt");
ofstream output ("output.txt");

int main () {
    unsigned long long a, b, x, y;

    input >> a >> b;

    x = (a - b) / 2; 
    y = x + b;

    if (a < b || a % 2 != b % 2 || (x & (a - x)) != x) {
        output << -1;
    }
    else {
        output << x << " " << y;
    }
     
}