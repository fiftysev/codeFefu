#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int ALPH_N = 78;

long long hash_gen(vector<long long> code_arr, int hashcode_len)
{
  long long key = code_arr[0];
  for (int i = 1; i < code_arr.size(); i++)
  {
    key = (key * ALPH_N + code_arr[i]) % hashcode_len;
  }
  return key;
}

int main()
{
  int hashcode_len = 78;
  string word;
  getline(cin, word);
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