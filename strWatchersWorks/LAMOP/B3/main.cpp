#include <bits/stdc++.h>
using namespace std;

fstream fin("input.txt");
ofstream fout("output.txt");

int members_count, questions_count;

struct test_member {
    int correct_answers_count;
    string answer;
};

int get_bit(int goal, int pos) {
    return (goal >> pos) & 1;
}

void print_answers(int model) {
    for (int i = 0; i < questions_count; ++i) {
        (get_bit(model, i)) ? fout << "+" : fout << "-";
    }
}

void gen_correct_answer(vector <test_member> &members) {
    for (int cur_model = 0; cur_model < 1 << questions_count; ++cur_model) {

        bool correct_flag = true;

        for (int i = 0; i < members_count; ++i) {

            int hemming_distance = 0;

            for (int j = 0; j < questions_count; ++j) {

                int cur_bit = get_bit(cur_model, j);
                if (cur_bit != (members[i].answer[j] == '+')) {
                    ++hemming_distance;
                }

            }
            if (hemming_distance != (questions_count - members[i].correct_answers_count)) {

                correct_flag = false;
                break;

            }
        }

        if (correct_flag) {
            print_answers(cur_model);
            return;
        }
    }
}

int main() {

    fin >> members_count >> questions_count;
    vector <test_member> members(members_count);
    for (auto &member: members) {
        fin >> member.answer >> member.correct_answers_count;
    }

    gen_correct_answer(members);
}