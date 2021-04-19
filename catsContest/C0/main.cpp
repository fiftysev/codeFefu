#include <iostream>
#include <algorithm>
using namespace std;

void build(int *arr, int *tree, int v, int treeLeft, int treeRight)
{
  if (treeLeft == treeRight)
    tree[v] = arr[treeLeft];
  else
  {
    int treeMedian = (treeLeft + treeRight) / 2;
    build(arr, tree, 2 * v + 1, treeLeft, treeMedian);
    build(arr, tree, 2 * v + 2, treeMedian + 1, treeRight);
    tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
  }
}

int treeMax(int *tree, int v, int treeLeft, int treeRight, int left, int right)
{
  if (left > treeRight || treeLeft > right)
    return INT_MIN;
  if (left <= treeLeft && right >= treeRight)
    return tree[v];
  int treeMedian = (treeLeft + treeRight) / 2;
  int max1 = treeMax(tree, 2 * v + 1, treeLeft, treeMedian, left, right);
  int max2 = treeMax(tree, 2 * v + 2, treeMedian + 1, treeRight, left, right);
  return max(max1, max2);
}

int main()
{
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int n;
  cin >> n;
  int *arr = new int[n];
  int *tree = new int[4 * n];
  for (int i = 0; i < n; i++)
    cin >> arr[i];
  build(arr, tree, 0, 0, n - 1);
  int L = 0, R = 0, m;
  cin >> m;
  char action;
  for (int i = 0; i < m; i++)
  {
    cin >> action;
    if (action == 'R')
      R++;
    else
      L++;
    cout << treeMax(tree, 0, 0, n - 1, L, R) << " ";
  }
  return 0;
}
