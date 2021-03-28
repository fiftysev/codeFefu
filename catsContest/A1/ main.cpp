#include <fstream>
#include <vector>
using namespace std;



unsigned long long merge (vector<int>&arr, vector<int> &tempArray, int firstIndex, int middleIndex, int lastIndex) {
    int i, j, k;
    unsigned long long invCount = 0;

    i = firstIndex;
    j = middleIndex;
    k = firstIndex;

    while ((i <= middleIndex - 1) && (j <= lastIndex)) {
        if (arr[i] <= arr[j]) {
            tempArray[k++] = arr[i++];
        }
        else {
        tempArray[k++] = arr[j++];
        invCount = invCount + (middleIndex - i);
        }
    }
    while (i <= middleIndex - 1) {
        tempArray[k++] = arr[i++];
    }
    while (j <= lastIndex) {
        tempArray[k++] = arr[j++];
    }
    for (i = firstIndex; i <= lastIndex; i++) {
        arr[i] = tempArray[i];
    }
    return invCount;
}



unsigned long long mergeSort (vector<int> &arr, vector<int> &tempArray, int firstIndex, int lastIndex) {
    unsigned long long middleIndex, invCount = 0;
    if (lastIndex > firstIndex) {
    middleIndex = (lastIndex + firstIndex) / 2;
    invCount = mergeSort (arr, tempArray, firstIndex, middleIndex);
    invCount += mergeSort (arr, tempArray, middleIndex + 1 , lastIndex);
    invCount += merge (arr, tempArray, firstIndex, middleIndex + 1, lastIndex);
    }
    return invCount;
}

unsigned long long invCounter (vector<int> &arr, int arraySize) {
    vector <int> tempArray (arr.size());
    return mergeSort (arr, tempArray, 0, arraySize - 1);
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n;
    in >> n;
    vector <int> arr(n);
    for (int i = 0; i < n; i++) {
        in >> arr[i];
    }
    
    out << invCounter(arr, arr.size());
}