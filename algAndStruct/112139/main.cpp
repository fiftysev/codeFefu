#include <iostream>
#include <string>
using namespace std;

int min(int a, int b, int c) {return min(min(a, b), c);}

int calcDistance (string firstString, string secondString, int m, int n) {
    int calcMx[m + 1][n + 1];
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0) calcMx[i][j] = j;
            else if (j == 0) calcMx[i][j] = i;
            else if (firstString[i - 1] == secondString[j - 1]) calcMx[i][j] = calcMx[i - 1][j - 1];
            else calcMx[i][j] = 1 + min(calcMx[i][j - 1], calcMx[i - 1][j], calcMx[i - 1][j - 1]);
        }
    }
    return calcMx[m][n];
}


int main() {
    int m, n;
    string firstString, secondString;
    cin >> m >> firstString >> n >> secondString;
    cout << calcDistance(firstString, secondString, m ,n);
}