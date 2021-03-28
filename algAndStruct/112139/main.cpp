#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int min(int x, int y, int z) {return min (min(x, y), z);}

int calcDistance(string firstString, string secondString, int m, int n) {
    if (m == 0) return n;
    if (n == 0) return m;
    if (firstString[m - 1] == secondString[n - 1]) {
        return calcDistance(firstString, secondString, m - 1, n - 1);
    }
    return 1 + min(calcDistance(firstString, secondString, m, n - 1),
                   calcDistance(firstString, secondString, m - 1, n),
                   calcDistance(firstString, secondString, m - 1, n - 1)
                   );
}

int main() {
    int m, n;
    string firstString, secondString;
    cin >> m >> firstString >> n >> secondString;
    cout << calcDistance(firstString, secondString, m, n);
    return 0;
}