#include <fstream>
using namespace std;
ifstream in("input.txt");
ofstream out("output.txt");

int oddCheck (int value) {
    int res = 0;
    while (value) {
        res += value & 1;
        value >>= 1;
    }
    return res % 2;
}

int main() {
    int byte;
    in >> byte;
    oddCheck(byte) ? byte = (byte << 1) | 1 : byte = (byte << 1) | 0;
    out << bitset<8>(byte);
    return 0;
}