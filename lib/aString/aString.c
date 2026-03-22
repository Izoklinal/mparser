#include "aString.h"
#include "string.h"

// privet
// 012356
// size 6

string string_init(char* str) {
    string s = {
        str,
        strlen(str)
    };
    return s;
}

string string_trim_start(string str, int idx) {
    string s = {0};
    if (str.size - idx <= 0) {
        s.size = 0;
        return s;
    }
    s.str = &str.str[idx];
    s.size = str.size - idx;
    return s;
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