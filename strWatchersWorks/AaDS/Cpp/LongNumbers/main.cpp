#include <bits/stdc++.h>
using namespace std;

const int base = 100000;
const int chunk_len = 5;


vector <int> create_long_num(string goal) {
    vector <int> ln;
    int sign;
    if (goal[0] == '-') {
        sign = 1;
        goal.replace(0, 1, "");
    }
    else {
        sign = 0;
    }

    while (goal.length() > chunk_len) {
        ln.push_back(stoi(goal.substr(goal.length() - chunk_len, chunk_len)));
        goal.replace(goal.length() - chunk_len, chunk_len, "");
    }

    ln.push_back(stoi(goal));
    ln.push_back(sign);
    return ln;
}

string chunktostr(int chunk) {
    string result;
    int m = base / 10;
    while (m > 0) {
        char cur_char = chunk / m % 10  + '0';
        result.push_back(cur_char);
        m /= 10;
    }
    return result;
}

void print_long_num(vector <int> ln) {
    vector <int>::iterator ln_it;

    if (ln.back() == 1)
        cout << "-";

    cout <<  *(ln.end() - 2);

    for (ln_it = ln.end() - 3; ln_it >= ln.begin(); --ln_it) {
        int chunk = *ln_it;
        cout << chunktostr(chunk);
    }

    cout << endl;


}

vector <int> sum(vector <int> a, vector <int> b) {

    if (a.size() < b.size()) {
        vector <int> temp = a;
        a = b;
        b = temp;
    }
    vector <int> result;

    int cur_result = 0;

    for (int i = 0; i < b.size() - 1; ++i) {
        cur_result += a[i] + b[i];
        result.push_back(cur_result % base);
        cur_result /= base;
    }

    for (int i = b.size() - 1; i < a.size() - 1; ++i) {
        cur_result += a[i];
        result.push_back(cur_result % base);
        cur_result /= base;
    }

    if (cur_result != 0) {
        result.push_back(cur_result);
    }

    result.push_back(a.back());
    return result;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    string l1, l2;
    cin >> l1 >> l2;
    vector <int> ln1 = create_long_num(l1);
    vector <int> ln2 = create_long_num(l2);
    print_long_num(sum(ln1, ln2));

}

