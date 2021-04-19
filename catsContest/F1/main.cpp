#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct maxHeap
{
private:
  vector<long long> A;
  int PARENT(int i)
  {
    return (i - 1) / 2;
  }
  int LEFT(int i)
  {
    return (2 * i + 1);
  }
  int RIGHT(int i)
  {
    return (2 * i + 2);
  }
  void heapify_down(int i)
  {
    int left = LEFT(i);
    int right = RIGHT(i);
    int largest = i;
    if (left < size() && A[left] > A[i])
    {
      largest = left;
    }
    if (right < size() && A[right] > A[largest])
    {
      largest = right;
    }
    if (largest != i)
    {
      swap(A[i], A[largest]);
      heapify_down(largest);
    }
  }
  void heapify_up(int i)
  {
    if (i && A[PARENT(i)] < A[i])
    {
      swap(A[i], A[PARENT(i)]);
      heapify_up(PARENT(i));
    }
  }

public:
  unsigned int size()
  {
    return A.size();
  }
  void push(long long key)
  {
    A.push_back(key);
    int index = size() - 1;
    heapify_up(index);
  }
  void pop()
  {
    A[0] = A.back();
    A.pop_back();
    heapify_down(0);
  }
  int top()
  {
    return A.at(0); // or return A[0];
  }
  long long heapSum()
  {
    long long res = 0;
    for (auto i : A)
    {
      res += i;
    }
    return res;
  }
};

int main()
{
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int n;
  cin >> n;
  int m;
  cin >> m;
  maxHeap heap;
  long long temp;
  for (int i = 0; i < n; i++)
  {
    cin >> temp;
    heap.push(temp);
  }
  for (int i = 0; i < m; ++i)
  {
    temp = heap.top();
    heap.pop();
    heap.push(temp / 10);
  }
  cout << heap.heapSum();
  return 0;
}
