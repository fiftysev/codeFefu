#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;
long long baseLen = 1e7;
long long dig_size = 10;
long long add_zero = baseLen / dig_size;
vector<long long> getNum(istream &is)
{
  string snum;
  vector<long long> vnum;
  unsigned long long dig = 1;
  long long n = 0;
  is >> snum;
  for (auto it = snum.crbegin(); it != snum.crend(); ++it)
  {
    n += (*it - '0') * dig;
    dig *= dig_size;
    if (dig == baseLen)
    {
      vnum.push_back(n);
      n = 0;
      dig = 1;
    }
  }
  if (n != 0)
  {
    vnum.push_back(n);
  }
  return vnum;
}

void extend_vec(vector<long long> &v, size_t len)
{
  while (len & (len - 1))
  {
    ++len;
  }

  v.resize(len);
}

vector<long long> multiply(const vector<long long> &num1, const vector<long long> &num2)
{
  size_t len = num1.size();
  vector<long long> result(2 * len);
  for (size_t i = 0; i < len; ++i)
  {
    for (size_t j = 0; j < len; ++j)
    {
      result[i + j] += num1[i] * num2[j];
    }
  }

  return result;
}

vector<long long> karatsubaMultiply(const vector<long long> &num1, const vector<long long> &num2)
{
  size_t len = num1.size();
  vector<long long> result(2 * len);
  size_t k = len / 2;
  if (len < 15)
  {
    return multiply(num1, num2);
  }
  vector<long long> Xr{num1.begin(), num1.begin() + k};
  vector<long long> Xl{num1.begin() + k, num1.end()};
  vector<long long> Yr{num2.begin(), num2.begin() + k};
  vector<long long> Yl{num2.begin() + k, num2.end()};
  vector<long long> R1 = karatsubaMultiply(Xl, Yl);
  vector<long long> R2 = karatsubaMultiply(Xr, Yr);
  vector<long long> Xlr(k);
  vector<long long> Ylr(k);
  for (size_t i = 0; i < k; i++)
  {
    Xlr[i] = Xl[i] + Xr[i];
    Ylr[i] = Yl[i] + Yr[i];
  }

  vector<long long> R3 = karatsubaMultiply(Xlr, Ylr);

  for (size_t i = 0; i < len; ++i)
  {
    R3[i] -= R2[i] + R1[i];
  }

  for (size_t i = 0; i < len; ++i)
  {
    result[i] = R2[i];
  }
  for (size_t i = len; i < 2 * len; ++i)
  {
    result[i] = R1[i - len];
  }
  for (size_t i = k; i < len + k; ++i)
  {
    result[i] += R3[i - k];
  }
  return result;
}

void final(vector<long long> &v)
{
  for (size_t i = 0; i < v.size(); i++)
  {
    v[i + 1] += v[i] / baseLen;
    v[i] %= baseLen;
  }
}

void print_res(const vector<long long> &v, ostream &os)
{
  auto it = v.crbegin();

  // Passing leading zeroes
  while (!*it)
  {
    ++it;
  }

  while (it != v.crend())
  {
    long long z = -1;
    auto num = *it;

    if (num == 0)
    {
      num += 1;
    }

    if (num < add_zero)
    {
      z = 1;

      while ((num *= dig_size) < add_zero)
      {
        ++z;
      }
    }

    if (z > 0)
    {
      while (z--)
      {
        os << '0';
      }
    }
    os << *it++;
  }

  os << endl;
}

int main()
{
  // freopen("input.txt", "r", stdin);
  // freopen("output.txt", "w", stdout);
  vector<long long> num1;
  vector<long long> result;
  result.push_back(1);
  num1.push_back(2);
  int f;
  cin >> f;
  if (f == 2)
  {
    result = karatsubaMultiply(num1, result);
    final(result);
    print_res(result, cout);
  }
  else
  {
    for (int i = 0; i < f; i++)
    {
      extend_vec(result, (int)result.size());
      extend_vec(num1, (int)result.size());
      result = karatsubaMultiply(result, num1);
      final(result);
    }
  }
  print_res(result, cout);
  return 0;
}