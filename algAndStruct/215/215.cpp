#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
using namespace std;

ifstream in ("input.txt");
ofstream out ("output.txt");



bool cmp (pair<string, string> a, pair<string, string> b) {
    return a.first.length() > b.first.length();
}


void processFunction() {
    int n, r;
    string temp;
    in >> r >> n;
    getline(in, temp);
    vector< pair <string, string> > replaceElements(r);
    for (int i = 0; i < r; i ++)
    {
        getline(in, replaceElements[i].first);
        getline(in, replaceElements[i].second);
    }
    sort(replaceElements.begin(), replaceElements.end(), cmp);
    for (int i = 0; i < n; i++) {
        string line;
        getline(in, line);
        vector <string> text(line.length() + 1);
        text[0] = "";
        for (int j = 1; j < line.length() + 1; j++) {
            text += temp[j - 1]

            for (auto element : replaceElements)
            {
                int replaceLen = element.first.size();
                if (replaceLen <= j && line.compare(j - replaceLen, replaceLen, element.first) == 0 &&
                    text[j - replaceLen].length() < text[j].length())
                    text[j] = text[j - replaceLen] + element.second;
            }     
        }
        out << text[line.length()] << endl;
    }
}

int main()
{
    processFunction();
    return 0;
}