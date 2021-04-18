#include <bits/stdc++.h>

#include <utility>

using namespace std;

const int base = 10000;
const int chunk_len = 4;

string chunk_to_string(int);

struct ln {
    vector <int> value;
    bool sign;

    explicit ln () {
        value = vector<int>();
        sign = false;

    }

    explicit ln (string goal) {
        if (goal[0] == '-') {
            sign = true;
            goal.replace(0, 1, "");
        }
        else {
            sign = false;
        }
        value = vector <int>();
        while (goal.length() > chunk_len) {
            value.push_back(stoi(goal.substr(goal.length() - chunk_len, chunk_len)));
            goal.replace(goal.length() - chunk_len, chunk_len, "");
        }
        value.push_back(stoi(goal));
    }

    explicit ln (vector <int> value, bool sign) {
        this->value = move(value);
        this->sign = sign;
    }

    explicit ln(int value) {
        string goal = to_string(value);
        ln result = ln(goal);
        this->value = result.value;
        this->sign = result.sign;
    }

    void print() {
        vector <int>::iterator ln_it;

        if (sign)
            cout << "-";

        cout <<  *(value.end() - 1);

        for (ln_it = value.end() - 2; ln_it >= value.begin(); --ln_it) {
            int chunk = *ln_it;
            cout << chunk_to_string(chunk);
        }

        cout << endl;
    }

    ln shift(int rad_count) {
        ln result = ln();
        for (int i = 0; i < rad_count; ++i) {
            result.value.push_back(0);
        }
        for (int num: this->value) {
            result.value.push_back(num);
        }
        return result;
    }

    ln sum(ln b) {
        if (this->value.size() < b.value.size()) {
            vector <int> temp = this->value;
            this->value = b.value;
            b.value = temp;
        }
        vector <int> result_value;
        int cur_result = 0;
        for (int i = 0; i < b.value.size(); ++i) {
            cur_result += this->value[i] + b.value[i];
            result_value.push_back(cur_result % base);
            cur_result /= base;
        }

        for (int i = b.value.size(); i < this->value.size(); ++i) {
            cur_result += this->value[i];
            result_value.push_back(cur_result % base);
            cur_result /= base;
        }
        if (cur_result != 0) {
            result_value.push_back(cur_result);
        }

        ln result = ln(result_value, false);
        return result;
    }

    ln multiple_with_int(int b) {
        int cur_result = 0;
        vector <int> result_value;
        bool b_s = b < 0;
        bool result_sign = this->sign && b_s;

        if (b_s) b *= -1;

        for (int i : this->value) {
            cur_result += i * b;
            result_value.push_back(cur_result % base);
            cur_result /= base;
        }
        if (cur_result) {
            result_value.push_back(cur_result);
        }

        ln result = ln(result_value, result_sign);
        return result;
    }


    ln multiple_with_ln(const ln& b) {
        ln result = ln(0);
        for (int i = 0; i < b.value.size(); ++i) {
            result = result.sum(this->multiple_with_int(b.value[i]).shift(i));
        }
        return result;
    }


};

string chunk_to_string(int chunk) {
    string result;
    int m = base / 10;
    while (m > 0) {
        char cur_char = chunk / m % 10  + '0';
        result.push_back(cur_char);
        m /= 10;
    }
    return result;

}

ln factorial(int a) {
    ln result = ln(1);
    for (int i = 2; i <= a; ++i) {
        result = result.multiple_with_int(i);
    }
    return result;
}

ln double_factorial(int a) {
    ln result = ln(1);
    for (int i = a; i >= 2; i-=2) {
        result = result.multiple_with_int(i);
    }
    return result;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int t1;
    cin >> t1;
    double_factorial(t1).print();
}