#include <bits/stdc++.h>

using namespace std;

vector <int> gen_new_arr(vector <int> &arr){
    stack <int> st;
    vector <int> result(arr.size());
    for (int i = arr.size() - 1; i >= 0; --i) {
        while (!st.empty() && arr[i] >= st.top()) {
            st.pop();
        }
        if (st.empty()) result[i] = arr[i];
        if (!st.empty() && arr[i] < st.top()) result[i] = st.top();
        st.push(arr[i]);
    }
    return result;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int size;
    cin >> size;
    vector <int> arr(size);
    for (int i = 0; i < size; ++i) {
        cin >> arr[i];
    }
    vector <int> res = gen_new_arr(arr);
    for (auto num: res) {
        cout << num << " ";
    }
}