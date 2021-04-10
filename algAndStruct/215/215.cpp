#include <string>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    const int base = 6;
    string str;
    bool is_neg;
    getline(cin, str);
    vector<int> digits;
    if (str.length() < 7)
    {
        cout << str;
        return 0;
    }
    if (str[0] == '-')
    {
        is_neg = true;
        str.erase(0, 1);
    }
    for (int i = 0; i < str.length(); i += base)
    {
        digits.push_back(atoi(str.substr(i, 6).c_str()));
    }
    string result;
    if (is_neg)
        cout << '-';
    for (int i = 0; i < digits.size(); i++)
    {
        cout << digits[i];
    }
    cout << result;
}