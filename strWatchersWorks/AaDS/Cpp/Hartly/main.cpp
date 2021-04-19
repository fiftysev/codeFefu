#include <bits/stdc++.h>

#define BYTE_LEN 7

using namespace std;

char get_bit(int goal, int pos) {return (goal >> pos & 1) + '0';}

string gen_alphabet(string &goal_text) {
    map <char, bool> alphabet;
    for (auto letter: goal_text) {
        alphabet[letter] = true;
    }
    string result_alphabet;
    map <char, bool>::iterator alp_iter;
    for (alp_iter = alphabet.begin(); alp_iter != alphabet.end(); ++alp_iter) {
        if (alp_iter->second) {
            result_alphabet.push_back(alp_iter->first);
        }
    }
    return result_alphabet;
}

int calculate_code_len(string &alphabet) {
    return ceil(log2((int) alphabet.length()));
}

string num_to_code(int num, int code_len) {
    string result;
    for (int i = code_len - 1; i >= 0; --i) {
        result.push_back(get_bit(num, i));
    }
    return result;
}

map <char, string> gen_dict(string &alphabet) {
    map <char, string> dict;
    int code_len = calculate_code_len(alphabet);
    for (int i = 0; i < alphabet.length(); ++i) {
        dict[alphabet[i]] = num_to_code(i, code_len);
    }
    return dict;
}

string read_text(string &file_path) {
    ifstream reading_file(file_path);
    string text;
    string tmp;
    while (getline(reading_file, tmp)) {
        text += tmp + "\n";
    }
    reading_file.close();
    return text;

}

char byte_to_char(string byte) {
    int result = 0;
    for (int i = 0; i < byte.length(); ++i) {

        int flag = (byte[i] == '1');
        result += flag;
        result <<= 1;

    }
    return result;
}

void archivate(string file_path) {
    string text = read_text(file_path);
    file_path.replace(file_path.length() - 4, 4,"_arch.txt");
    ofstream archived_file(file_path);

    string alphabet = gen_alphabet(text);
    int alphabet_len = alphabet.length();
    int code_len = calculate_code_len(alphabet);
    map <char, string> dict = gen_dict(alphabet);
    map <char, string>::iterator dict_iterator;
    archived_file << alphabet_len << " " << code_len << " ";

    string translated_text;
    for (auto letter: text) {
        translated_text += dict[letter];
    }
    archived_file << translated_text.length() << endl;

    for (dict_iterator = dict.begin(); dict_iterator != dict.end(); ++dict_iterator) {
        archived_file << (int)dict_iterator->first << " " << dict_iterator->second << endl;
    }

    string archived_text;
    for (int i = 0; i < translated_text.length(); i += BYTE_LEN) {
        archived_text += byte_to_char(translated_text.substr(i * BYTE_LEN, BYTE_LEN));
    }

    archived_file << archived_text;
    archived_file.close();
}

void dearchivate(string file_path, string dearchived_file_name) {
    ifstream archived_file(file_path);
    int alphabet_len, code_len;
    archived_file >> alphabet_len >> code_len;

    map <string, char> dict;
    map <string, char>::iterator dict_iterator;
    int cur_letter;
    string cur_code;
    for (int i = 0; i < alphabet_len; ++i) {
        archived_file >> cur_letter >> cur_code;
        dict[cur_code] = (char)cur_letter;
    }

    string text;
    archived_file >> text;
    ofstream dearchived_file(dearchived_file_name);
    for (int i = 0; i < text.length() / code_len; ++i) {
        dearchived_file << dict[text.substr(i * code_len, code_len)];
    }
    archived_file.close();
    dearchived_file.close();
}

int main () {
    archivate("test1.txt");
    //dearchivate("test1_arch.txt", "unarchived_test1.txt");
}