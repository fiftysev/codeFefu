#include <iostream>
#include <fstream>
#include <string>

unsigned long long merge_and_count (int arr[], int left_edge, int middle, int right_edge) {
    const int tmp_size = right_edge + 1;
    int tmp_arr[tmp_size];


    int i = left_edge;
    int j = middle;
    int k = left_edge;

    unsigned long long inv_count = 0;
    while (i <= middle - 1 && j <= right_edge) {
        if (arr[i] <= arr[j]) {
            tmp_arr[k++] = arr[i++];
        }
        else {
            tmp_arr[k++] = arr[j++];
            inv_count += (middle - i);
        }

    }
    while (i < middle) {
        tmp_arr[k++] = arr[i++];
    }

    while (j <= right_edge) {
        tmp_arr[k++] = arr[j++];
    }

    for (i = left_edge; i <= right_edge; i++) {
        arr[i] = tmp_arr[i];
    }
    return inv_count;
}

unsigned long long sort_and_count (int arr[], int left_edge, int right_edge) {
    unsigned long long count = 0;
    if (right_edge > left_edge) {
        int m = (left_edge + right_edge) / 2;
        count = sort_and_count(arr, left_edge, m);
        count += sort_and_count(arr, m + 1, right_edge);
        count += merge_and_count(arr, left_edge, m + 1, right_edge);
    }
    return count;
}

unsigned long long count_inversions(int arr[], int size) {
    return sort_and_count(arr, 0, size - 1);
}


int main () {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    int arr_size;
    fin >> arr_size;
    const int size = arr_size;
    int arr[size];
    for (int i = 0; i < arr_size; i++) {
        fin >> arr[i];
    }
    fout << count_inversions(arr, arr_size);
}