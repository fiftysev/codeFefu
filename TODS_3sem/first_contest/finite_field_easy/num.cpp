#include "num.h"

Num::Num(int value, int modulo) : value(value), modulo(modulo) {
    if (modulo) {
        this->value = value % modulo;
    } else {
        this->value = value;
    }
}

Num::Num(const Num &other) : Num(other.value) {}
