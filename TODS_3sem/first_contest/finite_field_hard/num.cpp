#include "num.h"

Num::Num(int value, int modulo) : value(value), modulo(modulo) {
    if (modulo) {
        this->value = value % modulo;
    } else {
        this->value = value;
    }
}

Num &Num::operator=(const Num &other) {
    value = other.value;
    modulo = 0;
    return *this;
}


Num Num::operator+(int num) {
    return Num(value + num, 0);
}

Num Num::operator+(const Num &other) {
    return Num(value + other.value, other.modulo);
}

Num Num::operator-(int num) {
    return Num(value - num, 0);
}

Num Num::operator-(const Num &other) {
    return Num(value - other.value, other.modulo);
}

Num Num::operator*(int num) {
    return Num(value * num, 0);
}

Num Num::operator*(const Num &other) {
    return Num(value * other.value, other.modulo);
}

Num &Num::operator+=(int num) {
    value = (static_cast<int64_t>(value) + num) % modulo;
    return *this;
}

Num &Num::operator+=(const Num &other) {
    value = (static_cast<int64_t>(value) + other.value) % modulo;
    return *this;
}

Num &Num::operator-=(int num) {
    if ((static_cast<int64_t>(value) - num) % modulo >= 0) {
        value = (static_cast<int64_t>(value) - num) % modulo;
    } else {
        value = modulo - (abs(static_cast<int64_t>(value) \
        - num) % modulo);
    }
    return *this;
}

Num &Num::operator-=(const Num &other) {
    if ((static_cast<int64_t>(value) - other.value) % modulo >= 0) {
        value = (static_cast<int64_t>(value) - other.value) % modulo;
    } else {
        value = modulo - (abs(static_cast<int64_t>(value) \
        - other.value) % modulo);
    }
    return *this;
}

Num &Num::operator*=(int num) {
    value = (static_cast<int64_t>(value) * num) % modulo;
    return *this;
}

Num &Num::operator*=(const Num &other) {
    value = (static_cast<int64_t>(value) * other.value) % modulo;
    return *this;
}
