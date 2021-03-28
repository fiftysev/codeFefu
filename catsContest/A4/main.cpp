#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
ifstream in("input.txt");
ofstream out("output.txt");

bool cmp (int a, int b) {
    return a < b;
}

int main() {
    int n;
    string currentLine;
    in >> n;
    int lineLength;
    int zeroZero = 0;
    int oneOne = 0;
    vector <int> oneZero;
    vector <int> zeroOne;
    for (int i = 0; i < n; i++) {
        in >> lineLength >> currentLine;
        if (currentLine[0] == '1') {
            if (currentLine[lineLength - 1] == '1') {
                oneOne += lineLength;
            }
            else {
                oneZero.push_back(lineLength);
            }
        }
        else {
            if (currentLine[lineLength - 1] == '1') {
                zeroOne.push_back(lineLength);
            }
            else {
                zeroZero += lineLength;
            }
        }
    }

    if (oneZero.empty() && zeroOne.empty()) {
        out << max(zeroZero, oneOne);
    }
    else {
        sort(oneZero.begin(), oneZero.end(), cmp);
        sort(zeroOne.begin(), zeroOne.end(), cmp);
        int res = oneOne + zeroZero;
        int breakpoint = min(zeroOne.size(), oneZero.size()) + 1;
        for (int i = 0; i < breakpoint; i++) {
            if (!zeroOne.empty()) {
                res += zeroOne.back();
                zeroOne.pop_back();
            }
            if (!oneZero.empty()) {
                res += oneZero.back();
                oneZero.pop_back();
            }
        }
        out << res;
    }
}