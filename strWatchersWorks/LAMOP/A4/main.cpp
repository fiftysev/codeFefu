#include <fstream>
#include <vector>

using namespace std;

void bubble_sort(int *arr, int len) {
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int days_count;
    string cur_day;
    fin >> days_count;
    int len;
    int logs_00 = 0;
    int logs_11 = 0;
    int *logs_10 = new int[500000];
    int logs_10_len = 0;
    int *logs_01 = new int[500000];
    int logs_01_len = 0;
    for (int i = 0; i < days_count; i++) {
        fin >> len >> cur_day;
        if (cur_day[0] == '1') {
            if (cur_day[len - 1] == '1') {
                logs_11 += len;
            }
            else {
                logs_10[logs_10_len++] = len;
            }
        }
        else {
            if (cur_day[len - 1] == '1') {
                logs_01[logs_01_len++] = len;
            }
            else {
                logs_00 += len;
            }
        }
    }


    if (logs_01_len == 0 and logs_10_len == 0) {
        fout << max(logs_00, logs_11);
    }
    else {
        bubble_sort(logs_01, logs_01_len);
        bubble_sort(logs_10, logs_10_len);

        int res = logs_11 + logs_00;
        for (int i = 0; i < min(logs_10_len, logs_01_len) + 1; i++) {
            if (i < logs_10_len) {
                res += logs_10[i];
            }
            if (i < logs_01_len) {
                res += logs_01[i];
            }
        }
        fout << res;
    }
}
