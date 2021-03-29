#include <bits/stdc++.h>
map<char, string> codes;
map<char, int> freq;
struct min_heap_node
{
    char data;
    int freq;
    min_heap_node *left, *right;

    min_heap_node(char data, int freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};

struct compare
{
    bool operator()(min_heap_node* l, min_heap_node* r)
    {
        return (l->freq > r->freq);
    }
};

void print_all_codes(min_heap_node* root, string str)
{
    if (!root)
        return;
    if (root->data != '$')
        cout << root->data << ": " << str << "\n";
    print_all_codes(root->left, str + "0");
    print_all_codes(root->right, str + "1");
}


void code_saver(min_heap_node* root, string str)
{
    if (root==nullptr)
        return;
    if (root->data != '$')
        codes[root->data]=str;
    code_saver(root->left, str + "0");
    code_saver(root->right, str + "1");
}

priority_queue<min_heap_node*, vector < min_heap_node *>, compare> minHeap;

void huffman_encode(int size)
{
    struct min_heap_node *left, *right, *top;
    for (auto & v : freq)
        minHeap.push(new min_heap_node(v.first, v.second));
    while (minHeap.size() != 1)
    {
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();
        top = new min_heap_node('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
    code_saver(minHeap.top(), "");
}

void calculate_freqs(string str, int n)
{
    for (int i = 0; i < n; i++){
        freq[str[i]]++;
    }
}

string decode_file(min_heap_node* root, string s)
{
    string ans;
    min_heap_node* curr = root;
    for (char i : s)
    {
        if (i == '0')
            curr = curr->left;
        else
            curr = curr->right;
        if (curr->left==nullptr and curr->right==nullptr)
        {
            ans += curr->data;
            curr = root;
        }
    }
    return ans;
}


int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    string str;
    in >> str;
    string encode_str, decode_str;
    calculate_freqs(str, str.length());
    huffman_encode(str.length());
    for (auto & freqs_el : codes)
        cout << freqs_el.first << "=>" << freqs_el.second << endl;
    for (auto i: str)
        encode_str += codes[i];
    out << "\nЗакодированная\n" << encode_str << endl;
    decode_str = decode_file(minHeap.top(), encode_str);
    out << "\nИсходная\n" << decode_str << endl;
    return 0;
}

