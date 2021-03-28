#include <fstream>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");


void combinations(int n, int k, int *arr, int *combination, int combinationIndex, int arrayIndex)
{
    if (combinationIndex == k) 
    {
        for (int j = 0; j < k; j++)
           out << combination[j] << " ";
        out << endl;
        return;
    }
    if (arrayIndex == n) 
        return;
    combination[combinationIndex] = arr[arrayIndex]; 
    combinations(n, k, arr, combination, combinationIndex + 1, arrayIndex + 1); 
    combinations(n, k, arr, combination, combinationIndex , arrayIndex + 1); 
}


void process() {
    int n, k;
    in >> n >> k;
    int *arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = i + 1;
    }
    int *combination = new int[k];
    combinations(n, k, arr, combination, 0, 0);
    return;
}

int main()
{
    process();
    return 0;
}
