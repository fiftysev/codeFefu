#include <string>
#include <cmath>

std::string FormatString(int num, unsigned int capacity) {
    std::string s;
    while (capacity != std::to_string(num).length()) {
        --capacity;
        s += '0';
    }
    s += std::to_string(num);
    return s;
}

class Date{
 public:
    Date() {
        year = 0;
        month = 0;
        day = 0;
    }
    explicit Date(int year, int month, int day) :
        year(year), month(month), day(day) {}

    bool IsLeap() const {
        return (
                !(year % 400) ||
                (!(year % 4) &&
                (year % 100)));
    }

    std::string ToString() const {
        return FormatString(day, 2) + '.' + \
        FormatString(month, 2) + '.' + FormatString(year, 4);
    }

    Date DaysLater(int days) {
        Date res(year, month, day);
        if (
                (days >= 366 && this->IsLeap()) ||
                (days >= 365 && !(this->IsLeap()))) {
            res.year++;
            this->IsLeap() ? days -= 366 : days -= 365;
        }
        while (days >= months[res.month]) {
            days -= months[res.month];
            if (this->IsLeap() && res.month == 2 && res.year == year) {
                days--;
            }
            res.month++;
        }
        res.day = day + days;
        return res;
    }

    int DaysLeft(const Date& other) const {
        int difference = 0;
        int datemonth = other.month;
        if (other.year > year) {
            this->IsLeap() ? difference += 366 : difference += 365;
        }
        while (datemonth > 1 && datemonth > month) {
            difference += months[datemonth - 1];
            if (this->IsLeap() && datemonth - 1 == 2 && other.year == year) {
                difference++;
            }
            datemonth--;
        }
        if (other.day > day) {
            difference += (other.day - day);
        }
        return difference;
    }

 private:
    int year;
    int month;
    int day;
    int months[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
};
