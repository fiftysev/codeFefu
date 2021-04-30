#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int findIndex(vector<int> &v, int left, int right, int key)
{
  while (right - left > 1)
  {
    int mid = left + (right - left) / 2;
    if (v[mid] >= key)
      right = mid;
    else
      left = mid;
  }
  return right;
}

void LIS(vector<int> arr, int n)
{
  vector<int> dp(n + 1, INFINITY);
  vector<int> pos(n + 1, 0);
  vector<int> prev(n, 0);
  dp[0] = int(-INFINITY);
  int length = 0;
  pos[0] = -1;
  for (int i = 0; i < n; i++)
  {
    int j = findIndex(dp, -1, dp.size(), arr[i]);
    if (dp[j - 1] < arr[i] && arr[i] < dp[j])
    {
      dp[j] = arr[i];
      pos[j] = i;
      prev[i] = pos[j - 1];
      length = max(length, j);
    }
  }
  vector<int> answer;
  int p = pos[length];
  while (p != -1)
  {
    answer.push_back(p);
    p = prev[p];
  }
  reverse(answer.begin(), answer.end());
  cout << length << endl;
  for (auto item : answer)
  {
    cout << item + 1 << " ";
  }
}

int main()
{
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int n;
  cin >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; ++i)
    cin >> arr[i];
  LIS(arr, n);
  return 0;
}