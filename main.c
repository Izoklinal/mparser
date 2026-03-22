#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "lib/aList/aList.h"
#include "lib/aString/aString.h"

float do_parenthesis(string str, int* shift);
void root(list_f* nums, list_c* ops);
void power(list_f* nums, list_c* ops);
void multiply(list_f* nums, list_c* ops);
void divide(list_f* nums, list_c* ops);
void sum(list_f* nums, list_c* ops);
float do_math(list_f* nums, list_c* ops);

int main() {
    list_f nums = {0};
    list_c ops = {0};
    string source = string_init("27v3");

    int count_op = string_count_val(&source, '(');
    int count_cp = string_count_val(&source, ')');

    if (count_op != count_cp) {
        printf("Your string lacks of parenthesis\n");
        return -1;
    }

    float buffer = 0;
    bool isNextNegative = false;
    int blockNegIdx = 0;
    for (size_t i = 0; i < source.size; i++)
    {
        char c = source.str[i];
        if (!isdigit(c)) {
            bool isValidChar = false;
            if (c == '-') {
                isNextNegative = true;
                blockNegIdx = i;
                isValidChar = true;
                c = '+';
            } else if (c == '+' || c == '*' || c == '/' || c == '^' || c == 'v') {
                isNextNegative = false;
                isValidChar = true;
            } else if (c == '(') {
                string trimmed = string_trim_start(source, i + 1);
                int shift = 0;
                buffer = do_parenthesis(trimmed, &shift);
                i += shift;
                c = '+';
            }
            
            if (isValidChar) {
                if (isNextNegative && blockNegIdx != i) {
                    buffer *= -1.0f;
                    isNextNegative = false;
                }
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

    float result = do_math(&nums, &ops);

    printf("Result of equation = %f\n", result);

    return 0;
}

float do_parenthesis(string str, int* shift) {
    list_c ops = {0};
    list_f nums = {0};

    float buffer = 0;
    bool isNextNegative = false;
    int blockNegIdx = 0;
    for (size_t i = 0; i < str.size; i++)
    {
        (*shift)++;
        char c = str.str[i];
        if (!isdigit(c)) {
            bool isValidChar = false;
            if (c == '-') {
                isNextNegative = true;
                blockNegIdx = i;
                isValidChar = true;
                c = '+';
            } else if (c == '+' || c == '*' || c == '/' || c == '^' || c == 'v') {
                isNextNegative = false;
                isValidChar = true;
            } else if (c == '(') {
                string trimmed = string_trim_start(str, i + 1);
                int localShift = 0;
                buffer = do_parenthesis(trimmed, &localShift);
                (*shift) += localShift;
                i += localShift;
            } else if (c == ')') {
                if (isNextNegative && blockNegIdx != i) {
                    buffer *= -1.0f;
                    isNextNegative = false;
                }
                list_f_add(&nums, buffer);
                break;
            }
            
            if (isValidChar) {
                if (isNextNegative && blockNegIdx != i) {
                    buffer *= -1.0f;
                    isNextNegative = false;
                }
                list_c_add(&ops, c);
                list_f_add(&nums, buffer);
                buffer = 0;
            }
            continue;
        }
        float val = c - '0';
        buffer = (buffer * 10 + val);
    }
    return do_math(&nums, &ops);
}

void power(list_f* nums, list_c* ops) {
    int idx;
    while((idx = list_c_index_of(ops, '^')) != -1) {
        float r = 0;
        list_c_take_at(ops, idx);
        float v1 = list_f_take_at(nums, idx);
        float v2 = list_f_take_at(nums, idx);    
        r = pow(v1, v2);
        list_f_insert_at(nums, idx, r);
    }
}

void root(list_f* nums, list_c* ops) {
    int idx;
    while((idx = list_c_index_of(ops, 'v')) != -1) {
        float r = 0;
        list_c_take_at(ops, idx);
        float v1 = list_f_take_at(nums, idx);
        float v2 = list_f_take_at(nums, idx);
        r = pow(v1, 1.0f / v2);
        list_f_insert_at(nums, idx, r);
    }
}

void multiply(list_f* nums, list_c* ops) {
    int idx;
    while((idx = list_c_index_of(ops, '*')) != -1) {
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
        char op = list_c_shift(ops);
        float v1 = list_f_shift(nums);
        float v2 = list_f_shift(nums);
        float lr = v1 + v2;
        list_f_insert_at(nums, 0, lr);
    }
}

float do_math(list_f* nums, list_c* ops) {
    root(nums, ops);
    power(nums, ops);
    multiply(nums, ops);
    divide(nums, ops);
    sum(nums, ops);
    return nums->items[0];
}