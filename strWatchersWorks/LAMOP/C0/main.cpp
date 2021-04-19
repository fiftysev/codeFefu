#include <bits/stdc++.h>
using namespace std;

void build(int *arr, int *tree, int v, int left_edge, int right_edge) {
    if (left_edge == right_edge) {
       tree[v] = arr[left_edge];
    }
    else {
        int mid_point = (left_edge + right_edge) / 2;
        build(arr, tree, 2 * v + 1, left_edge, mid_point);
        build(arr, tree, 2 * v + 2, mid_point + 1, right_edge);
        tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
    }
}

int get_max(int *tree, int v, int left_edge, int right_edge, int left, int right) {
    if (left > right_edge || right < left_edge) {
        return INT_MIN;
    }
    if (left <= left_edge && right >= right_edge) {
        return tree[v];
    }
    int mid = (left_edge + right_edge) / 2;
    int max1 = get_max(tree, 2 * v + 1, left_edge, mid, left, right);
    int max2 = get_max(tree, 2 * v + 2, mid + 1, right_edge, left, right);
    return max(max1, max2);
}
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    cin >> n;
    int *arr = new int[n];
    int *tree = new int[n * 4];

    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    build(arr, tree, 0, 0, n - 1);
    int L = 0, R = 0, m;

    cin >> m;
    char action;

    for (int i = 0; i < m; ++i) {
        cin >> action;
        if (action == 'R') {
            ++R;
        }
        else {
            ++L;
        }

        cout << get_max(tree, 0, 0, n - 1, L, R) << " ";
    }
    return 0;
}