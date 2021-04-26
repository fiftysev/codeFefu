#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int n;
  cin >> n;
  vector<int> nails(n + 1);
  vector<int> dp(n + 1);
  for (int i = 1; i <= n; i++)
  {
    cin >> nails[i];
  }
  sort(nails.begin(), nails.end());
  dp[2] = nails[2] - nails[1];
  dp[3] = nails[3] - nails[1];
  for (int j = 4; j <= n; j++)
  {
    dp[j] = min(dp[j - 1], dp[j - 2]) + nails[j] - nails[j - 1];
  }
  cout << dp[n];
};