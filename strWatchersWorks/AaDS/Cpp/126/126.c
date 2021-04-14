#include <stdio.h>

int main() {
    int user_input;
    int zero_index;
    scanf("%d %d", &user_input, &zero_index);
    int mask = ~(1 << zero_index);
    printf("%d", user_input & mask);
}