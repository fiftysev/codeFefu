#include <iostream>

struct stack {
    int nums[16];
    int head = 0;

    int pop() {
        return nums[--head];
    }

    void push(int x) {
        nums[head++] = x;
    }

    void print_all_objects() const {
        for (int i = 0; i < head; i++) {
            std::cout << nums[i] << " ";
        }
        std::cout << std::endl;
    }
};

void gen_combinations(int set[], int n, int k, int h = 0, int i = 0) {
    static stack answer;
    if (h == k) answer.print_all_objects();
    else {
        for (int j = i; j < n; j++) {
            answer.push(set[j]);
            gen_combinations(set, n, k, h+1, j+1);
            answer.pop();
        }
    }
}


int main() {
    int n, k;
    std::cin >> n >> k;
    int set[n];
    for(int i = 1 ; i <= n; i++) {
        set[i - 1] = i;
    }
    gen_combinations(set, n, k);
    return 0;
}
