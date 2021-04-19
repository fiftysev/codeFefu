#include <iostream>
#include <string>
#include <vector>
using namespace std;

class longNum
{
    static const int base = 1000;
    vector<int> digits;
    bool is_neg;

public:
    explicit longNum()
    {
        digits = vector<int>();
        is_neg = false;
    }
    explicit longNum(vector<int> digits, bool is_neg)
    {
        this->digits = move(digits);
        this->is_neg = is_neg;
    }
    explicit longNum(string str)
    {
        if (str[0] == '-')
            is_neg = true;
        else
            is_neg = false;
        for (int i = int(str.length()); i > 0; i -= 3)
        {
            if (i < 3)
                digits.push_back(atoi(str.substr(0, i).c_str()));
            else
                digits.push_back(atoi(str.substr(i - 3, 3).c_str()));
        }
        while (digits.size() > 1 && digits.back() == 0)
            digits.pop_back();
    }
    explicit longNum(int val)
    {
        string value = to_string(val);
        longNum res = longNum(value);
        this->digits = res.digits;
        this->is_neg = res.is_neg;
    }
    void print()
    {
        if (is_neg)
        {
            printf("-");
        }
        printf("%d", digits.empty() ? 0 : digits.back());
        for (int i = int(digits.size() - 2); i >= 0; i--)
        {
            printf("%03d", digits[i]);
        }
    }

    longNum shift(int n)
    {
        longNum result = longNum();
        for (int i = 0; i < n; i++)
        {
            result.digits.push_back(0);
        }
        for (int num : this->digits)
        {
            result.digits.push_back(num);
        }
        return result;
    }

    longNum add(longNum num2)
    {
        if (this->digits.size() < num2.digits.size())
        {
            vector<int> temp = this->digits;
            this->digits = num2.digits;
            num2.digits = temp;
        }
        vector<int> result;
        int cur = 0;
        for (int i = 0; i < num2.digits.size(); i++)
        {
            cur += this->digits[i] + num2.digits[i];
            result.push_back(cur % base);
            cur /= base;
        }
        for (int i = num2.digits.size(); i < this->digits.size(); i++)
        {
            cur += this->digits[i];
            result.push_back(cur % base);
            cur /= base;
        }
        if (cur != 0)
            result.push_back(cur);
        longNum result_l = longNum(result, false);
        return result_l;
    }
    longNum multiplyInt(int num)
    {
        int cur = 0;
        vector<int> result;
        bool sign_s = num < 0;
        bool res_is_neg = this->is_neg && sign_s;

        if (sign_s)
            num *= -1;

        for (int i : this->digits)
        {
            cur += i * num;
            result.push_back(cur % base);
            cur /= base;
        }
        if (cur)
            result.push_back(cur);
        longNum result_l = longNum(result, res_is_neg);
        return result_l;
    }

    longNum multipleLong(const longNum &num)
    {
        longNum res = longNum(0);
        for (int i = 0; i < num.digits.size(); i++)
        {
            res = res.add(this->multiplyInt(num.digits[i]).shift(i));
        }
        return res;
    }

    int divideShort(int num)
    {
        int carry = 0;
        for (int i = this->digits.size() - 1; i >= 0; i--)
        {
            long long cur = this->digits[i] + carry * 1ll * base;
            this->digits[i] = int(cur / num);
            carry = int(cur % num);
        }
        while (this->digits.size() > 1 && this->digits.back() == 0)
        {
            this->digits.pop_back();
        }
        return carry;
    }
};
longNum factorial(int n)
{
    longNum res = longNum(1);
    for (int i = 2; i <= n; i++)
    {
        res = res.multiplyInt(i);
    }
    return res;
}

longNum double_factorial(int n)
{
    longNum res = longNum(1);
    for (int i = n; i > 0; i -= 2)
    {
        res = res.multiplyInt(i);
    }
    return res;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    string str1;
    string str2;
    cin >> str1 >> str2;
    longNum num1 = longNum(str1);
    int num2 = atoi(str2.c_str());
    int carry = num1.divideShort(num2);
    num1.print();
    cout << endl;
    cout << carry;
    return 0;
}