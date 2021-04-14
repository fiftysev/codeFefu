#include <iostream>
#include <fstream>
#include <bitset>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

unsigned is_count_bits_odd(unsigned byte) {
    unsigned count = 0;
    unsigned all_units = byte ^ 0;
    for (int i = 0; i < 7; i++) {
        count += all_units & 1;
        all_units >>= 1;
    }
    return (count % 2 == 1) ? 1 : 0;
}

unsigned modify_number(unsigned byte, unsigned odd_bit) {
    byte <<= 1;
    byte += odd_bit;
    return byte;
}

void add_odd_bit() {
    unsigned byte;
    in >>byte;
    out << "Начальное значение\n" << bitset<8>(byte) << endl;
    byte = modify_number(byte, is_count_bits_odd(byte));
    out << "Значение с добавленным битом четности\n" << bitset<8>(byte) << endl;

}

int main () { 
    for (int i = 0; i < 4; i++) {
        add_odd_bit();
    }
}