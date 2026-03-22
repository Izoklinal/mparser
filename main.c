#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "lib/aList/aList.h"
#include "lib/aString/aString.h"

float do_parenthesis(string str, int* shift);
void multiply(list_f* nums, list_c* ops);
void divide(list_f* nums, list_c* ops);
void sum(list_f* nums, list_c* ops);
float do_math(list_f* nums, list_c* ops);

// 012345678
// 2*(3+4)-1
//   ^
// 
// 012345
// 3+4)-1
//    ^
// return i + 1

static int countOps = 0;

int main() {
    list_f nums = {0};
    list_c ops = {0};
    string source = string_init("2+5^(4/2)-4");

    int count_op = string_count_val(&source, '(');
    int count_cp = string_count_val(&source, ')');

    if (count_op != count_cp) {
        printf("Your string lacks of parenthesis\n");
        return -1;
    }

    float buffer = 0;
    bool isNextNegative = false;
    for (size_t i = 0; i < source.size; i++)
    {
        countOps++;
        char c = source.str[i];
        if (!isdigit(c)) {
            bool isValidChar = false;
            if (isNextNegative) {
                buffer *= -1.0f;
                isNextNegative = false;
            }
            if (c == '-') {
                isNextNegative = true;
                isValidChar = true;
                c = '+';
            } else if (c == '+' || c == '*' || c == '/' || c == '^') {
                isNextNegative = false;
                isValidChar = true;
            } else if (c == '(') {
                string trimmed = string_trim_start(source, i + 1);
                int shift = 0;
                float num = do_parenthesis(trimmed, &shift);
                i += shift;
                buffer = num;
                c = '+';
            }

            if (isValidChar) {
                list_c_add(&ops, c);
                list_f_add(&nums, buffer);
                buffer = 0;
            }
            continue;
        }
        float val = c - '0';
        buffer = (buffer * 10 + val);
    }
    if (isNextNegative) {
        buffer *= -1.0f;
    }
    list_f_add(&nums, buffer);

    // for (size_t i = 0; i < nums.size; i++)
    // {
    //     printf("%d - %f\n", i, nums.items[i]);
    //     if (i < ops.size) {
    //         printf("%d - %c\n", i, ops.items[i]);
    //     }
    // }

    float result = do_math(&nums, &ops);

    printf("Result of equation = %f\nCount of operations: %d", result, countOps);

    return 0;
}

float do_parenthesis(string str, int* shift) {
    list_c ops = {0};
    list_f nums = {0};

    float buffer = 0;
    bool isNextNegative = false;
    for (size_t i = 0; i < str.size; i++)
    {
        countOps++;
        (*shift)++;
        char c = str.str[i];
        if (!isdigit(c)) {
            bool isValidChar = false;
            if (isNextNegative) {
                buffer *= -1.0f;
                isNextNegative = false;
            }
            if (c == '-') {
                isNextNegative = true;
                isValidChar = true;
                c = '+';
            } else if (c == '+' || c == '*' || c == '/') {
                isNextNegative = false;
                isValidChar = true;
            } else if (c == '(') {
                string trimmed = string_trim_start(str, i + 1);
                float num = do_parenthesis(trimmed, shift);
            } else if (c == ')') {
                list_f_add(&nums, buffer);
                break;
            }

            if (isValidChar) {
                list_c_add(&ops, c);
                list_f_add(&nums, buffer);
                buffer = 0;
            }
            continue;
        }
        float val = c - '0';
        buffer = (buffer * 10 + val);
    }
    
    // printf("Numbers in parenthesis:\n");
    // for (size_t i = 0; i < nums.size; i++)
    // {
    //     printf("%f\n", nums.items[i]);
    // }
    
    return do_math(&nums, &ops);
}

void power(list_f* nums, list_c* ops) {
    int idx;
    while((idx = list_c_index_of(ops, '^')) != -1) {
        countOps++;
        float r = 0;
        list_c_take_at(ops, idx);
        float v1 = list_f_take_at(nums, idx);
        float v2 = list_f_take_at(nums, idx);    
        r = pow(v1, v2);
        list_f_insert_at(nums, idx, r);
    }
}

void multiply(list_f* nums, list_c* ops) {
    int idx;
    while((idx = list_c_index_of(ops, '*')) != -1) {
        countOps++;
        float lr = 0;
        list_c_take_at(ops, idx);
        float v1 = list_f_take_at(nums, idx);
        float v2 = list_f_take_at(nums, idx);    
        lr = v1 * v2;
        list_f_insert_at(nums, idx, lr);
    }
}

void divide(list_f* nums, list_c* ops) {
    int idx;
    while((idx = list_c_index_of(ops, '/')) != -1) {
        countOps++;
        float lr = 0;
        list_c_take_at(ops, idx);
        float v1 = list_f_take_at(nums, idx);
        float v2 = list_f_take_at(nums, idx);    
        lr = v1 / v2;
        list_f_insert_at(nums, idx, lr);
    }
}

void sum(list_f* nums, list_c* ops) {
    size_t size = ops->size;
    for (size_t i = 0; i < size; i++)
    {
        countOps++;
        char op = list_c_shift(ops);
        float v1 = list_f_shift(nums);
        float v2 = list_f_shift(nums);
        float lr = v1 + v2;
        list_f_insert_at(nums, 0, lr);
    }
}

float do_math(list_f* nums, list_c* ops) {
    power(nums, ops);
    multiply(nums, ops);
    divide(nums, ops);
    sum(nums, ops);
    return nums->items[0];
}