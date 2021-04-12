#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
vector<string> solve(string *arr, int x, int y, int n);
string intToString(int num);
void copy(string *source, string *dest, int n);

int main()
{
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int n;
  cin >> n;
  string gameArea[n];
  vector<string> answer, temp;
  for (int i = 0; i < n; ++i)
    cin >> gameArea[i];
  for (int y = 0; y < n; ++y)
    for (int x = 0; x < n; ++x)
      if (gameArea[y][x] == 'X')
      {
        gameArea[y][x] = '.';
        temp = solve(gameArea, x, y, n);
        gameArea[y][x] = 'X';
        if (temp.size() > answer.size())
          answer = temp;
      }
  if (answer.size() < 2)
    cout << "Impossible";
  else
  {
    for (int i = answer.size() - 1; i > 0; --i)
      cout << answer[i] << '-';
    cout << answer[0];
  }
}
vector<string> solve(string *arr, int x, int y, int n)
{
  vector<string> answer, temp;
  if (x == -1 || y == -1)
    return answer;
  auto *tempArr = new string[n];
  if (x - 2 >= 0 && y - 2 >= 0 && arr[y - 2][x - 2] == '.' && arr[y - 1][x - 1] == 'O')
  {
    copy(arr, tempArr, n);
    tempArr[y - 1][x - 1] = '.';
    temp = solve(tempArr, x - 2, y - 2, n);
    if (temp.size() > answer.size())
      answer = temp;
  }
  if (x - 2 >= 0 && y + 2 < n && arr[y + 2][x - 2] == '.' && arr[y + 1][x - 1] == 'O')
  {
    copy(arr, tempArr, n);
    tempArr[y + 1][x - 1] = '.';
    temp = solve(tempArr, x - 2, y + 2, n);
    if (temp.size() > answer.size())
      answer = temp;
  }
  if (x + 2 < n && y + 2 < n && arr[y + 2][x + 2] == '.' && arr[y + 1][x + 1] == 'O')
  {
    copy(arr, tempArr, n);
    tempArr[y + 1][x + 1] = '.';
    temp = solve(tempArr, x + 2, y + 2, n);
    if (temp.size() > answer.size())
      answer = temp;
  }
  if (x + 2 < n && y - 2 >= 0 && arr[y - 2][x + 2] == '.' && arr[y - 1][x + 1] == 'O')
  {
    copy(arr, tempArr, n);
    tempArr[y - 1][x + 1] = '.';
    temp = solve(tempArr, x + 2, y - 2, n);
    if (temp.size() > answer.size())
      answer = temp;
  }
  delete[] tempArr;
  answer.push_back(string("") + char(x + 'a') + intToString(n - y));
  return answer;
}
void copy(string *source, string *dest, int n)
{
  for (int i = 0; i < n; ++i)
    dest[i] = source[i];
}

string intToString(int num)
{
  string temp;
  while (num > 0)
  {
    temp += (char)(num % 10) + '0';
    num /= 10;
  }
  reverse(temp.begin(), temp.end());
  return temp;
}