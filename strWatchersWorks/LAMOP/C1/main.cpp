#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m, power_level, weight_category;

    cin >> n >> m;

    vector <vector <int> > all_boxers;
    vector <int> enemies_in_category(m);

    for (int i = 0; i < n; ++i)
    {
        cin >> power_level >> weight_category;
        all_boxers.push_back({power_level, weight_category - 1, 0});
    }

    for (int i = 0; i < n; ++i)
    {
        cin >> power_level >> weight_category;
        all_boxers.push_back({power_level, weight_category - 1, 1});
        enemies_in_category[weight_category - 1]++;
    }

    sort(all_boxers.begin(), all_boxers.end());

    vector <int> defeated_enemies_in_category(m);
    int best_difference = 0, result = 0;

    for (int i = 0; i < n * 2; ++i)
    {
        if (all_boxers[i][2] == 1)
        {
            defeated_enemies_in_category[all_boxers[i][1]]++;
        }
        else
        {
            int cur_category = all_boxers[i][1];
            int victorious_enemies = enemies_in_category[cur_category] - defeated_enemies_in_category[cur_category];
            int current_score = defeated_enemies_in_category[cur_category] - victorious_enemies;
            result += current_score;

            for (int j = 0; j < m; ++j)
            {
                if (j != cur_category)
                {
                    int changed_victorious_enemies = enemies_in_category[j] - defeated_enemies_in_category[j];
                    int changed_score = defeated_enemies_in_category[j] - changed_victorious_enemies;
                    best_difference = max(best_difference, changed_score - current_score);
                }
            }
        }
    }


    cout << result + best_difference;
}