#include <iostream>

using namespace std;

int count_hemming_destination(string word1, string word2) {
    int count = 0;

    for (size_t i = 0; i < word1.length(); i++) {
        if (word1[i] != word2[i]) count++;
    }

    return count;
}

int main() {
    int n, m;
    string word1, word2;
    cin >> n;
    cin >> word1;
    cin >> m;
    cin >> word2;

    if (n == m) {
        cout << count_hemming_destination(word1, word2);
    }
    else if (n > m){
        int min_count = n;
        int now_count = 0;
        for (int i = 0; i <= n - m; i++) {
            now_count = count_hemming_destination(word1.substr(i, m + i), word2);
            now_count = min(now_count, min_count);
            cout << now_count + n - m;
        }
    }
    else if (n < m) {
        int min_count = m;
        int now_count = 0;
        for (int i = 0; i <= m - n; i++) {
            now_count = count_hemming_destination(word1, word2.substr(i, n + i));
            now_count = min(now_count, min_count);
            cout << now_count + m - n;
        }
    }
    return 0;
}
