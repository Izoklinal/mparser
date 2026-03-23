#include "mparser.h"
#include "../aString/aString.h"
#include "../aList/aList.h"
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

float mparser_parse(string str, int* shift) {
    list_c ops = {0};
    list_f nums = {0};

    bool isEndedWithP = false;
    float buffer = 0;
    bool isNextNegative = false;
    int blockNegIdx = 0;
    bool isDecimфl = false;
    float multiplier = 1;
    for (size_t i = 0; i < str.size; i++)
    {
        (*shift)++;
        char c = str.str[i];
        if (!isdigit(c)) {
            bool isValidChar = false;
            if (c == '.') {
                isDecimфl = true;
                continue;
            }
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
                buffer = mparser_parse(trimmed, &localShift);
                string_clear(&trimmed);
                (*shift) += localShift;
                i += localShift;
            } else if (c == ')') {
                if (isDecimфl) {
                    buffer /= multiplier;
                    multiplier = 1;
                    isDecimфl = false;
                }
                if (isNextNegative && blockNegIdx != i) {
                    buffer *= -1.0f;
                    isNextNegative = false;
                }
                list_f_add(&nums, buffer);
                isEndedWithP = true;
                break;
            }
            
            if (isValidChar) {
                if (isDecimфl) {
                    buffer /= multiplier;
                    multiplier = 1;
                    isDecimфl = false;
                }
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
        if (isDecimфl) {
            multiplier *= 10;
        }
    }
    if (!isEndedWithP) {
        if (isDecimфl) {
            buffer /= multiplier;
            multiplier = 1;
            isDecimфl = false;
        }
        if (isNextNegative) {
            buffer *= -1.0f;
        }
        list_f_add(&nums, buffer);
    }
    float r = mparser_do_math(&nums, &ops);
    // list_f_clear(&nums);
    // list_c_clear(&ops);
    return r;
}

void mparser_power(list_f* nums, list_c* ops) {
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

void mparser_root(list_f* nums, list_c* ops) {
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

void mparser_multiply(list_f* nums, list_c* ops) {
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

void mparser_divide(list_f* nums, list_c* ops) {
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

void mparser_sum(list_f* nums, list_c* ops) {
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

float mparser_do_math(list_f* nums, list_c* ops) {
    mparser_root(nums, ops);
    mparser_power(nums, ops);
    mparser_multiply(nums, ops);
    mparser_divide(nums, ops);
    mparser_sum(nums, ops);
    return nums->items[0];
}