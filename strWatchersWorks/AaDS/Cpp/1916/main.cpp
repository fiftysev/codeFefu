#include <bits/stdc++.h>

using namespace std;
#define END 9

map <int, map <string, int> > gen_transition_table() {
    map <int, map <string, int> >  transition_table;
    transition_table[1]["sign"] = 2;
    transition_table[1]["digit"] = 3;

    transition_table[2]["digit"] = 3;

    transition_table[3]["digit"] = 3;
    transition_table[3]["dot"] = 4;
    transition_table[3]["exponent"] = 6;
    transition_table[3]["void"] = END;

    transition_table[4]["digit"] = 5;

    transition_table[5]["digit"] = 5;
    transition_table[5]["void"] = END;
    transition_table[5]["exponent"] = 6;

    transition_table[6]["sign"] = 7;
    transition_table[6]["digit"] = 8;

    transition_table[7]["digit"] = 8;

    transition_table[8]["digit"] = 8;
    transition_table[8]["void"] = END;

    return transition_table;
}

bool is_sign(char goal) {
    return goal == '-' or goal == '+';
}

bool is_exponent(char goal) {
    return goal == 'E' or goal == 'e';
}

bool is_dot(char goal) {
    return goal == '.';
}



int check_const (string& goal) {
    int current_state = 1;
    string current_char_type;
    map <int, map <string, int> > transition_table = gen_transition_table();
    for (auto letter: goal) {
        if (is_sign(letter)) {
            current_char_type = "sign";
        }
        else if (isdigit(letter)) {
            current_char_type = "digit";
        }

        else if (is_dot(letter)) {
            current_char_type = "dot";
        }

        else if (is_exponent(letter)) {
            current_char_type = "exponent";
        }
        else {
            current_char_type = "error";
        }
        current_state = transition_table[current_state][current_char_type];
        if (current_state == 0) return 0;
    }

    current_state = transition_table[current_state]["void"];

    return current_state;
}

bool is_float_const(string& goal) {
    return (check_const(goal) == END);
}

int main() {
    string goal;
    cin >> goal;

    if (is_float_const(goal)) {
        cout << "YES";
    }
    else {
        cout << "NO";
    }
}
