#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selectionSort(int *arr, int n) {
    int i, j, min_idx;

    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        swap(&arr[min_idx], &arr[i]);
    }
}

int main() {
    int n, p, sum;
    scanf("%d %d", &n, &p);
    char **arr = (char **)malloc(n * sizeof(char*));
    int *arr_sum = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = (char *)malloc(29 * sizeof(char));
        for (int k = 0; k < 29; k++) {
            scanf("%c", &arr[i][k]);
        }
        sum = 0;
        for (int j = 0; j < 29; j++) {
            if (arr[i][j] >= '0' && arr[i][j] <= '9') {
                sum = sum + arr[i][j] - '0';
            }
            if (arr[i][j] >= 'A' && arr[i][j] <= 'Z') {
                sum = sum + arr[i][j] - 'A' + 10;
            }
        }
        arr_sum[i] = sum % p;
    }
    selectionSort(arr_sum, n);
    char check;
    for (int n = 0; n < 876; n++) {
        check = 0;
        for (int j = 0; j < n; j++) {
            if (n % p == arr_sum[j]) {
                check = 1;
                break;
            }
        }
        if (!check) {
            sum = n;
            break;
        }
    }
    if (check) {
        printf("%s", "Impossible");
    } else {
        char *output = (char *)malloc(29 * sizeof(char));
        for (int i = 0; i < 29; i++) {
            output[i] = '0';
        }
        output[5] = output[11] = output[17] = output[23] = '-';
        for (int i = 0; i < 29; i++) {
            if (output[i] != '-') {
                if (sum / 35 > 0) {
                    sum = sum - 35;
                    output[i] = 'Z';
                } else {
                    if (sum >= 0 && sum <= 9)
                        output[i] = (sum + '0');
                    else
                        output[i] = (sum - 10 + 'A');
                    break;
                }
            }
        }
        for (int i = 0; i < 29; i++) {
            printf("%c", output[i]);
        }
    }
    return 0;
}