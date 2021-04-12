#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

bool comparator(pair<string, string> a, pair<string, string> b) {
    return a.first.length() > b.first.length();
}

int main() {
    int dict_len, lines_in_text_count;
    string temp;
    fin >> dict_len >> lines_in_text_count;
    getline(fin, temp);
    vector<pair<string, string>> dict_of_replacements(dict_len);
    for (int i = 0; i < dict_len; i++) {
        getline(fin, dict_of_replacements[i].first);
        getline(fin, dict_of_replacements[i].second);
    }
    sort(dict_of_replacements.begin(), dict_of_replacements.end(), comparator);
    for (int i = 0; i < lines_in_text_count; i++) {
        getline(fin, temp);
        vector <string> text(temp.length() + 1);
        text[0] = "";
        for (int j = 1; j < temp.length() + 1; j++) {
            text[j] = text[j - 1] + temp[j - 1];

            for (auto replacement: dict_of_replacements) {
                int replacement_len = replacement.first.size();
                if (replacement_len <= j and temp.compare(j - replacement_len, replacement_len, replacement.first) == 0 && \
                text[j - replacement_len].length() < text[j].length()) {
                    text[j] = text[j - replacement_len] + replacement.second;
                }
            }
        }
        fout << text[temp.length()] << endl;
    }

}