#include "aList.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>

#pragma region add
int list_s_add(list_s *l, const char *val) {
    if (l->size >= l->capacity) {
        size_t new_capacity = (l->capacity == 0) ? 4 : l->capacity * 2;
        char **new_items    = realloc(l->items, sizeof(char*) * new_capacity);
        if (new_items == NULL) return 1;
        l->items    = new_items;
        l->capacity = new_capacity;
    }
    l->items[l->size] = malloc(strlen(val) + 1);
    strcpy(l->items[l->size], val);
    l->size++;
    return 0;
}
int list_c_add(list_c *l, char val) {
    if (l->size >= l->capacity) {
        size_t new_capacity = (l->capacity == 0) ? 4 : l->capacity * 2;
        char *new_items     = realloc(l->items, new_capacity);
        if (new_items == NULL) return 1;
        l->items    = new_items;
        l->capacity = new_capacity;
    }
    l->items[l->size] = val;
    l->size++;
    return 0;
}
int list_i_add(list_i *l, int val) {
    if (l->size >= l->capacity) {
        size_t new_capacity = (l->capacity == 0) ? 4 : l->capacity * 2;
        int *new_items      = realloc(l->items, new_capacity);
        if (new_items == NULL) return 1;
        l->items    = new_items;
        l->capacity = new_capacity;
    }
    l->items[l->size] = val;
    l->size++;
    return 0;
}
int list_f_add(list_f *l, float val) {
    if (l->size >= l->capacity) {
        size_t new_capacity = (l->capacity == 0) ? 4 : l->capacity * 2;
        float *new_items    = realloc(l->items, new_capacity);
        if (new_items == NULL) return 1;
        l->items    = new_items;
        l->capacity = new_capacity;
    }
    l->items[l->size] = val;
    l->size++;
    return 0;
}
#pragma endregion

#pragma region clear
void list_s_clear(list_s *l) {
    if (l) {
        free(l->items);
        l->items = NULL;
        l->size = 0;
        l->capacity = 0;
    }
}
void list_c_clear(list_c *l) {
    if (l) {
        free(l->items);
        l->items = NULL;
        l->size = 0;
        l->capacity = 0;
    }
}
void list_i_clear(list_i *l) {
    if (l) {
        free(l->items);
        l->items = NULL;
        l->size = 0;
        l->capacity = 0;
    }
}
void list_f_clear(list_f *l) {
    if (l) {
        free(l->items);
        l->items = NULL;
        l->size = 0;
        l->capacity = 0;
    }
}
#pragma endregion

#pragma region contains
bool list_s_contains(list_s *l, char* val) {
    for (size_t i = 0; i < l->size; i++)
    {
        char* arrStr = tolower_s(l->items[i]);
        char* valStr = tolower_s(val);
        if (strcmp(arrStr, valStr) == 0) {
            return true;
        }
    }
    return false;
}
bool list_c_contains(list_c *l, char val) {
    for (size_t i = 0; i < l->size; i++)
    {
        if (l->items[i] == val) {
            return true;
        }
    }
    return false;
}
bool list_i_contains(list_i *l, int val) {
    for (size_t i = 0; i < l->size; i++)
    {
        if (l->items[i] == val) {
            return true;
        }
    }
    return false;
}
bool list_f_contains(list_f *l, float val) {
    for (size_t i = 0; i < l->size; i++)
    {
        if (l->items[i] == val) {
            return true;
        }
    }
    return false;
}
#pragma endregion

#pragma region count
int list_c_count(list_c *l, char val) {
    int count = 0;
    for (size_t i = 0; i < l->size; i++)
    {
        if (l->items[i] == val) {
            ++count;
        }
    }
    return count;
}
int list_i_count(list_i *l, int val) {
    int count = 0;
    for (size_t i = 0; i < l->size; i++)
    {
        if (l->items[i] == val) {
            ++count;
        }
    }
    return count;
}
int list_f_count(list_f *l, float val) {
    int count = 0;
    for (size_t i = 0; i < l->size; i++)
    {
        if (l->items[i] == val) {
            ++count;
        }
    }
    return count;
}
#pragma endregion

#pragma region index of
int list_c_index_of(list_c *l, char val) {
    for (size_t i = 0; i < l->size; i++)
    {
        if (l->items[i] == val) {
            return i;
        }
    }
    return -1;
}
int list_i_index_of(list_i *l, int val) {
    for (size_t i = 0; i < l->size; i++)
    {
        if (l->items[i] == val) {
            return i;
        }
    }
    return -1;
}
int list_f_index_of(list_f *l, float val) {
    for (size_t i = 0; i < l->size; i++)
    {
        if (l->items[i] == val) {
            return i;
        }
    }
    return -1;
}
#pragma endregion

#pragma region sort
void list_c_sort(list_c *l) {
    for (size_t i = 0; i < l->size - 1; i++)
    {
        if (l->items[i] > l->items[i + 1]) {
            char temp = l->items[i];
            l->items[i] = l->items[i + 1];
            l->items[i + 1] = temp;
        }
    }
}
#pragma endregion

#pragma region 
// I think that it is not right to just decrement size of list and still having popped item.
// But who cares?
char* list_s_pop(list_s* l) {
    printf("--- list_s_pop NOT TESTED ---");
    if (l->size == 0) {
        return NULL;
    }
    char* lastItem = l->items[l->size - 1];
    l->size--;
    return lastItem;
}
char list_c_pop(list_c* l) {
    if (l->size == 0) {
        return '\n';
    }
    char lastItem = l->items[l->size - 1];
    l->size--;
    return lastItem;
}
int list_i_pop(list_i* l) {
    if (l->size == 0) {
        return '\n';
    }
    int lastItem = l->items[l->size - 1];
    l->size--;
    return lastItem;
}
float list_f_pop(list_f* l) {
    if (l->size == 0) {
        return '\n';
    }
    float lastItem = l->items[l->size - 1];
    l->size--;
    return lastItem;
}

#pragma endregion

#pragma region shift
char list_c_shift(list_c* l) {
    char val = l->items[0];
    if (l->size > 1) {
        l->items = &l->items[1];
    }
    l->size--;
    return val;
}
float list_f_shift(list_f* l) {
    float val = l->items[0];
    if (l->size > 1) {
        l->items = &l->items[1];
    }
    l->size--;
    return val;
}
#pragma endregion

#pragma region take at
float list_f_take_at(list_f* l, int idx) {
    if (idx > l->size) {
        printf("Cannot take element that is out of array (array size: %d; idx: %d)\n", l->size, idx);
        abort();
    }
    float r = l->items[idx];
    l->size--;
    for (size_t j = idx; j < l->size; j++)
    {
        l->items[j] = l->items[j + 1];
    }
    return r;
}
char list_c_take_at(list_c* l, int idx) {
    if (idx >= l->size) {
        printf("Cannot take element that is out of array\n");
        abort();
    }
    char r = l->items[idx];
    l->size--;
    for (size_t j = idx; j < l->size; j++)
    {
        l->items[j] = l->items[j + 1];
    }
    return r;
}
#pragma endregion

#pragma region insert at
void list_f_insert_at(list_f* l, int idx, float val) {
    if (l->size >= l->capacity) {
        size_t new_capacity = (l->capacity == 0) ? 4 : l->capacity * 2;
        float *new_items    = realloc(l->items, new_capacity);
        if (new_items == NULL) return;
        l->items    = new_items;
        l->capacity = new_capacity;
    }
    l->size++;
    for (size_t i = idx + 1; i < l->size; i++)
    {
        l->items[i] = l->items[i - 1];
    }
    l->items[idx] = val;
}
#pragma endregion

#pragma region help
char* tolower_s(char* str) {
    char* res = malloc(strlen(str) * sizeof(char));
    for (size_t i = 0; i < strlen(str); i++)
    {
        res[i] = tolower(str[i]);
    }
    return res;
}
#pragma endregion