#include <bits/stdc++.h>

using namespace std;


class MaxHeap
{
    vector<long long> arr;

    static int parent(int i)
    {
        return (i - 1) / 2;
    }

    static int left(int i)
    {
        return (2 * i + 1);
    }

    static int right(int i)
    {
        return (2 * i + 2);
    }

    void heapifyDown(int i)
    {
        int l = left(i);
        int r = right(i);
        int largest = i;
        int heap_size = (int) arr.size();

        if (l < heap_size and arr[l] > arr[largest])
            largest = l;

        if (r < heap_size and arr[r] > arr[largest])
            largest = r;

        if (largest != i)
        {
            swap(arr[i], arr[largest]);

            heapifyDown(largest);
        }
    }

    void heapifyUp(int i)
    {
        if (i != 0 and arr[parent(i)] < arr[i])
        {
            swap(arr[i], arr[parent(i)]);
            heapifyUp(parent(i));
        }
    }

public:
    int size() const
    {
        return (int) arr.size();
    }

    long long getMax()
    {
        return arr[0];
    }

    void push(long long key)
    {
        arr.push_back(key);
        int index = size() - 1;
        heapifyUp(index);
    }

    void pop()
    {
        arr[0] = arr.back();
        arr.pop_back();
        heapifyDown(0);
    }

    long long sum()
    {
        long long result = 0;
        for (auto i: arr)
        {
            result += i;
        }
        return result;
    }
};




int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;

    cin >> n >> m;
    MaxHeap students;
    long long temp;

    for (int i = 0; i < n; ++i)
    {
        cin >> temp;
        students.push(temp);
    }

    for (int i = 0; i < m; ++i)
    {
        temp = students.getMax();
        students.pop();
        students.push(temp / 10);
    }
    cout << students.sum();
    return 0;
}