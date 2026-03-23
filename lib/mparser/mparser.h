#ifndef MPARSER_H
#define MPARSER_H

#include "../aString/aString.h"
#include "../aList/aList.h"

float mparser_parse(string str, int* shift);
void mparser_root(list_f* nums, list_c* ops);
void mparser_power(list_f* nums, list_c* ops);
void mparser_multiply(list_f* nums, list_c* ops);
void mparser_divide(list_f* nums, list_c* ops);
void mparser_sum(list_f* nums, list_c* ops);
float mparser_do_math(list_f* nums, list_c* ops);

#endif