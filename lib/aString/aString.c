#include "aString.h"
#include "string.h"
#include "stdio.h"

string string_init(char* str) {
    string s = {
        str,
        strlen(str)
    };
    return s;
}

string string_copy(string str) {
    char buf[str.size];
    snprintf(buf, str.size + 1, "%s", str.str);
    return string_init(buf);
}

void string_trim_start(string* str, int idx) {
    if (str->size - idx <= 0) {
        str->size = 0;
        return;
    }
    str->str = &str->str[idx];
    str->size = str->size - idx;
}
string string_trim_end(string str, int idx) {
    string s = {0};
    if (str.size - idx <= 0) {
        s.size = 0;
        return s;
    }
    s.str = &str.str[str.size - idx];
    s.size = str.size - idx;
    return s;
}

int string_count_val(string* str, char val) {
    int count = 0;
    for (size_t i = 0; i < str->size; i++)
    {
        if (str->str[i] == val) {
            count++;
        }
    }
    return count;
}

void string_clear(string* str) {
    if (str) {
        free(str->str);
        str->str = NULL;
        str->size = 0;
    }
}