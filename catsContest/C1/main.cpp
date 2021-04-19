#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int n, m, level, weightCat;
  cin >> n >> m;
  vector<vector<int> > a;
  vector<int> enemiesInWeightCat(m);
  for (int i = 0; i < n; i++)
  {
    cin >> level >> weightCat;
    a.push_back({level, weightCat - 1, 0}); // последнее значение при push_back - флаг команды
  }
  for (int i = 0; i < n; i++)
  {
    cin >> level >> weightCat;
    a.push_back({level, weightCat - 1, 1});
    enemiesInWeightCat[weightCat - 1]++; //считаем количество соперников в весовой категории
  }
  sort(a.begin(), a.end()); // сортируем в порядке возрастания уровня мастерства
  vector<int> count(m);
  int bestDifference = 0, ans = 0;
  for (int i = 0; i < n * 2; i++)
  { // до n*2, тк N в каждой команде
    if (a[i][2] == 1)
    {
      count[a[i][1]]++; // если встретился противник, считаем сколько на данный момент встретили в этой весовой категории
    }
    else
    {
      int cur_score = 2 * count[a[i][1]] - enemiesInWeightCat[a[i][1]];
      /*
            Счет при бое текущего бойца = количеству уже встретившихся соперников в весовой категории
            текущего бойца х2 - общее количество соперников в весовой категории
            Собственно это и есть та самая разница в очках, на которую мы и будем опираться
            при поиске того, кого стоило бы заменить
            */
      ans += cur_score;
      for (int j = 0; j < m; j++)
      {
        if (j != a[i][1])
        {
          bestDifference = max(bestDifference, 2 * count[j] - enemiesInWeightCat[j] - cur_score);
          /*
                    Лучшая разница - максимум из уже посчитанной лучшей разницы и текущий счет в другой весовой категории
                     -разница которую получили для текущего бойца
                    */
        }
      }
    }
  }
  cout << ans + bestDifference; // В ответ идет общая сумма всех результатов раунда + лучшая разница в очках которую мы посчитали (я и мой алгоритм)

  return 0;
}