#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
  int N, P, sum;
  cin >> N >> P;
  auto *arr = new string[N];
  vector<int> arr_sum;
  for (int i = 0; i < N; i++)
  {
    cin >> arr[i];
    sum = 0;
    for (int j = 0; j < 29; j++)
    {
      if (arr[i][j] >= '0' && arr[i][j] <= '9')
        sum = sum + arr[i][j] - '0';
      if (arr[i][j] >= 'A' && arr[i][j] <= 'Z')
        sum = sum + arr[i][j] - 'A' + 10;
    }
    arr_sum.push_back(sum % P);
  }
  sort(arr_sum.begin(), arr_sum.end());
  bool check;
  for (int n = 0; n <= 875; n++)
  {
    check = false;
    for (int j = 0; j < N; j++)
      if (n % P == arr_sum[j])
      {
        check = true;
        break;
      }
    if (!check)
    {
      sum = n;
      break;
    }
  }
  if (check)
    cout << "Impossible";
  else
  {
    string output;
    output.resize(29, '0');
    output[5] = output[11] = output[17] = output[23] = '-';
    for (int i = 0; i < 29; i++)
    {
      if (output[i] != '-')
      {
        if (sum / 35 > 0)
        {
          sum = sum - 35;
          output[i] = 'Z';
        }
        else
        {
          if (sum >= 0 && sum <= 9)
            output[i] = static_cast<char>(sum + '0');
          else
            output[i] = static_cast<char>(sum - 10 + 'A');
          break;
        }
      }
    }
    cout << output;
  }
  return 0;
}