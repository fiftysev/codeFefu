#include <bits/stdc++.h>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

struct node {
    int amount;
    char letter;
    bool is_letter;
    node *left, *right;

    node(char letter, int amount) {
        this->letter = letter;
        this->amount = amount;
        this->is_letter = true;
        this->left = this->right = nullptr;
    }

    node(node* left, node *right) {
        this->left = left;
        this->right = right;
        this->amount = left->amount + right->amount;
        this->is_letter = false;
        this->letter = '0';
    }
};

struct comparator {
    bool  operator() (node *l, node *r) const {
        return l->amount < r->amount;
    }
};

void print(node *root, unsigned k=0) {
    if (root) {
        print(root->left, k + 3);
        for (unsigned i = 0; i < k; ++i) fout << "  ";

        if (root->is_letter) fout << root->amount << " (" << root->letter << ")" << endl;
        else fout << root->amount << endl;
        print(root->right, k + 3);
    }
}

vector<bool> code;
map<char, vector<bool> > table;

void build_table(node *root) {
    if (root->left) {
        code.push_back(false);
        build_table(root->left);
    }
    if (root->right) {
        code.push_back(true);
        build_table(root->right);
    }

    if (root->is_letter) table[root->letter] = code;

    code.pop_back();
}

int main() {
    string input;
    getline(fin, input);
    map<char, int> dict;
    for (char & i : input) {
        dict[i]++;
    }

    list<node *> tree;
    map<char, int>::iterator ii;
    for(ii = dict.begin(); ii != dict.end(); ++ii) {
        node *tmp = new node(ii->first, ii->second);
        tree.push_back(tmp);
    }

    while (tree.size() != 1) {
        tree.sort(comparator());
        node *left_son = tree.front();
        tree.pop_front();
        node *right_son = tree.front();
        tree.pop_front();

        node *parent = new node(left_son, right_son);
        tree.push_back(parent);
    }
    node *root = tree.front();
    build_table(root);


    fout << "Словарь: " << endl;
    map <char , vector<bool> >::iterator itr;
    for (itr = table.begin(); itr != table.end(); ++itr) {
        fout << itr->first << ":";
        for (auto el: itr->second) {
            fout << el;
        }
        fout << endl;
    }


    fout << "Сжатый текст: " << endl;
    for (char letter : input) {
        vector<bool> letter_code = table[letter];

        for (auto && value : letter_code) {
            fout << value;
        }
    }
}
