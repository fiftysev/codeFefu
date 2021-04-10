#include <iostream>
using namespace std;
int main()
{
  int N, res = 0;
  cin >> N;
  string str_arr[N];
  for (int n = 0; n < N; n++)
    cin >> str_arr[n];
  for (int n = 0; n < N; n++)
    for (int i = 0; i < 7; i++)
    {
      if (str_arr[n][i] >= 'a' && str_arr[n][i] <= 'c')
        str_arr[n][i] = '2';
      if (str_arr[n][i] >= 'd' && str_arr[n][i] <= 'f')
        str_arr[n][i] = '3';
      if (str_arr[n][i] >= 'g' && str_arr[n][i] <= 'i')
        str_arr[n][i] = '4';
      if (str_arr[n][i] >= 'j' && str_arr[n][i] <= 'l')
        str_arr[n][i] = '5';
      if (str_arr[n][i] >= 'm' && str_arr[n][i] <= 'o')
        str_arr[n][i] = '6';
      if (str_arr[n][i] >= 'p' && str_arr[n][i] <= 's')
        str_arr[n][i] = '7';
      if (str_arr[n][i] >= 't' && str_arr[n][i] <= 'v')
        str_arr[n][i] = '8';
      if (str_arr[n][i] >= 'w' && str_arr[n][i] <= 'z')
        str_arr[n][i] = '9';
    }
  for (int i = 0; i < N - 1; i++)
    for (int j = i + 1; j < N; j++)
      if (str_arr[i] == str_arr[j])
        str_arr[i] = "*";
  for (int n = 0; n < N; n++)
    if (str_arr[n] != "*")
      res++;
  cout << res;
  return 0;
}