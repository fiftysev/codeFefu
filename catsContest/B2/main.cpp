#include <fstream>
#include <vector>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");


void printArr(vector<int> num) {
    for (auto element : num) {
        out << element << " ";
    }
    out << endl;
}


void process(int n) {
    vector<int> num(n);
    fill(num.begin(), num.end(), 1);
    printArr(num);
    while (num.size() > 1) {
        int sum = num.back();
        num.pop_back();
        int i = num.size() - 1;
        while (i > 0 && num[i - 1] == num[i]) {
            sum += num.back();
            num.pop_back();
            --i;
        }
        num[i] += 1;
        sum -= 1;
        for (int i = 0; i < sum; i++) {
            num.push_back(1);
        }
        printArr(num);
    }
}


int main () {
    int n;
    in >> n;
    process(n);
    return 0;
}