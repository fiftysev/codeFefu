#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int ALPH_N = 128;

long long hash_gen(vector<long long> code_arr, int hashcode_len)
{
  long long key = code_arr[0] * ALPH_N + code_arr[1];
  for (int i = 2; i < code_arr.size(); i++)
  {
    key = (key * ALPH_N + code_arr[i]) % hashcode_len;
  }
  return key;
}

int main()
{
  int hashcode_len;
  cin >> hashcode_len;
  string word;
  cin >> word;
  vector<long long> code_arr;
  code_arr.reserve(word.length());
  for (char i : word)
  {
    code_arr.push_back(int(i));
  }
  long long result = hash_gen(code_arr, hashcode_len);
  cout << result;
  return 0;
}