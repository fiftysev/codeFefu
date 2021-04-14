#include <bits/stdc++.h>
using namespace std;

vector<string> calc_best_play(string *arr, int x, int y, int n);
void copy(string *source, string *dest, int n);

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    cin >> n;
    string game_field[n];
    vector<string> answer, temp;
    for (int i = 0; i < n; ++i)
        cin >> game_field[i];
    for (int y = 0; y < n; ++y)
        for (int x = 0; x < n; ++x)
            if (game_field[y][x] == 'X')
            {
                game_field[y][x] = '.';
                temp = calc_best_play(game_field, x, y, n);
                game_field[y][x] = 'X';
                if (temp.size() > answer.size())
                    answer = temp;
            }
    if (answer.size() < 2)
        cout << "Impossible";
    else
    {
        for (int i = (int)answer.size() - 1; i > 0; --i)
            cout << answer[i] << '-';
        cout << answer[0];
    }
}
vector<string> calc_best_play(string *arr, int x, int y, int n)
{
    vector<string> answer, temp;
    if (x == -1 || y == -1)
        return answer;
    auto *temp_arr = new string[n];
    if (x - 2 >= 0 && y - 2 >= 0 && arr[y - 2][x - 2] == '.' && arr[y - 1][x - 1] == 'O')
    {
        copy(arr, temp_arr, n);
        temp_arr[y - 1][x - 1] = '.';
        temp = calc_best_play(temp_arr, x - 2, y - 2, n);
        if (temp.size() > answer.size())
            answer = temp;
    }
    if (x - 2 >= 0 && y + 2 < n && arr[y + 2][x - 2] == '.' && arr[y + 1][x - 1] == 'O')
    {
        copy(arr, temp_arr, n);
        temp_arr[y + 1][x - 1] = '.';
        temp = calc_best_play(temp_arr, x - 2, y + 2, n);
        if (temp.size() > answer.size())
            answer = temp;
    }
    if (x + 2 < n && y + 2 < n && arr[y + 2][x + 2] == '.' && arr[y + 1][x + 1] == 'O')
    {
        copy(arr, temp_arr, n);
        temp_arr[y + 1][x + 1] = '.';
        temp = calc_best_play(temp_arr, x + 2, y + 2, n);
        if (temp.size() > answer.size())
            answer = temp;
    }
    if (x + 2 < n && y - 2 >= 0 && arr[y - 2][x + 2] == '.' && arr[y - 1][x + 1] == 'O')
    {
        copy(arr, temp_arr, n);
        temp_arr[y - 1][x + 1] = '.';
        temp = calc_best_play(temp_arr, x + 2, y - 2, n);
        if (temp.size() > answer.size())
            answer = temp;
    }
    delete[] temp_arr;
    answer.push_back(string("") + char(x + 'a') + to_string(n - y));
    return answer;
}
void copy(string *source, string *dest, int n)
{
    for (int i = 0; i < n; ++i)
        dest[i] = source[i];
}
