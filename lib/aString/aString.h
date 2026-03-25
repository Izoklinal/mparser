#ifndef ASTRING_H
#define ASTRING_H

#include <stdlib.h>

typedef struct string{
    char* str;
    size_t size;
} string;

string string_copy(string str); // copies the string
string string_init(char* str); // initializes string
void string_trim_start(string* str, int idx); // trims string from the left to passed index and returns a new string
string string_trim_end(string str, int idx); // trims string from the right to passed index and returns a new string
int string_count_val(string* str, char val); // counts how many times given char appear in string
void string_clear(string* str); // frees the memory

#endif