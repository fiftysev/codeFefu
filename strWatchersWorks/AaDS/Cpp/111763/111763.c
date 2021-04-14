#include <stdio.h>

int main() {
    FILE *input_file = fopen("input.txt", "r");
    FILE *output_file = fopen("output.txt", "w");

    unsigned long long a, b, x, y;
    
    fscanf(input_file, "%llu %llu", &a, &b);

    x = (a - b) / 2;
    y = x + b;

    if (a < b || a % 2 != b % 2 || (x ^ y) != b) {
         fprintf(output_file, "-1\n");
    }
    else {
        fprintf(output_file, "%llu %llu\n", x, y);
    } 
}