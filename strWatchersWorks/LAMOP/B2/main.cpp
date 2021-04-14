#include <fstream>
#include <vector>
using namespace std;
ofstream fout("output.txt");

void print_arr(const vector<int>& num) {
    for (auto element : num) {
        fout << element << " ";
    }
    fout << endl;
}

void gen_summations(int n) {
    static vector<int> res;
    if (n == 0) {
        print_arr(res);
    }
    for (int i = 1; i <= n; i++) {
        if (res.empty() || i <= res[res.size() - 1]) {
            res.push_back(i);
            gen_summations(n - i);
            res.pop_back();
        }
        else {
            break;
        }
    }


}



int main () {
    ifstream fin("input.txt");

    int n;
    fin >> n;
    gen_summations(n);
    return 0;
}