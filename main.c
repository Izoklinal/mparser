#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lib/aList/aList.h"
#include "lib/aString/aString.h"

void parse(char str[], list_f* l, list_c* ops);
void multiply(list_f* nums, list_c* ops);
void divide(list_f* nums, list_c* ops);
void sum(list_f* nums, list_c* ops);
float domath(list_f* nums, list_c* ops);

// 2*(3+4)-1

int main() {
    list_f nums = {0};
    list_c ops = {0};
    string source = string_init("2-2*(10+2)-2");

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
            } else if (c == '+' || c == '*' || c == '/') {
                isNextNegative = false;
                isValidChar = true;
            } else if (c == '(') {
                string trimmed = string_trim_start(source, i + 1);
                // here we gonna call a recursive function
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

    for (size_t i = 0; i < nums.size; i++)
    {
        printf("%d - %f\n", i, nums.items[i]);
    }

    return 0;
}

void parse(char str[], list_f* nums, list_c* ops) {
    float buf = 0;
    float dir = 1;
    for (size_t i = 0; i < strlen(str); i++)
    {
        if (!isdigit(str[i])) {
            if (str[i] == '-') {
                dir = -1;
                continue;
            } else {
                dir = 1;
                list_c_add(ops, str[i]);
            }
            list_f_add(nums, buf);
            buf = 0;
            continue;
        }
        float vi = str[i] - '0';
        buf = (buf * 10 + vi) * dir;
    }
    list_f_add(nums, buf);
}

void doparentheses(list_f* nums, list_c* ops) {

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

float domath(list_f* nums, list_c* ops) {
    multiply(nums, ops);
    divide(nums, ops);
    sum(nums, ops);
    return nums->items[0];
}