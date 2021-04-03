#include <iostream>
#include <string>
#include <vector>
using namespace std;

int P, Q;
bool right_key;
struct test
{
  string answers;
  int score;
};

int bit_mask(int a, int b) { return (a >> b) & 1; }

void print_answer(int i)
{
  for (int j = 0; j < Q; ++j)
  {
    if (bit_mask(i, j))
      cout << "+";
    else
      cout << "-";
  }
}

void check_test(vector<test> &a)
{
  for (int i = 0; i < (1 << Q); ++i)
  {
    right_key = true;
    for (int j = 0; j < P; ++j)
    {
      int no_match = 0;
      for (int k = 0; k < Q; ++k)
      {
        int key = bit_mask(i, k);
        if (key != (a[j].answers[k] == '+'))
        {
          no_match++;
        }
      }
      if (no_match != (Q - a[j].score))
      {
        right_key = false;
        break;
      }
    }
    if (right_key)
    {
      print_answer(i);
      break;
    }
  }
}

int main()
{
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  cin >> P >> Q;
  vector<string> key;
  vector<test> member(P);

  for (auto &i : member)
  {
    cin >> i.answers >> i.score;
    if (i.score == Q)
    {
      cout << i.answers;
      return 0;
    }
  }

  check_test(member);
  return 0;
}
