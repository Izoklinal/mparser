#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdbool.h>

// dynamic array for strings
typedef struct {
    char **items;
    size_t size;
    size_t capacity;
} list_s;
// dynamic array for chars
typedef struct {
    char *items;
    size_t size;
    size_t capacity;
} list_c;
// dynamic array for integers
typedef struct {
    int *items;
    size_t size;
    size_t capacity;
} list_i;
// dynamic array for floats
typedef struct {
    float *items;
    size_t size;
    size_t capacity;
} list_f;

int list_s_add(list_s *l, const char *val); // adding a new item in dynamic array of strings
int list_c_add(list_c *l, char val); // adding a new item in dynamic array of chars
int list_i_add(list_i *l, int val); // adding a new item in dynamic array of integers
int list_f_add(list_f *l, float val); // adding a new item in dynamic array of floats

void list_s_clear(list_s *l); // clears a dynamic array of strings
void list_c_clear(list_c *l); // clears a dynamic array of chars
void list_i_clear(list_i *l); // clears a dynamic array of integers
void list_f_clear(list_f *l); // clears a dynamic array of floats

bool list_s_contains(list_s *l, char* val); // checks if dynamic array of string contains a value
bool list_c_contains(list_c *l, char val); // checks if dynamic array of chars contains a value
bool list_i_contains(list_i *l, int val); // checks if dynamic array of integers contains a value
bool list_f_contains(list_f *l, float val); // checks if dynamic array of floats contains a value

int list_c_count(list_c *l, char val); // counts how many times given value has appeard in dynamic array of chars
int list_i_count(list_i *l, int val); // counts how many times given value has appeard in dynamic array of integers
int list_f_count(list_f *l, float val); // counts how many times given value has appeard in dynamic array of floats

int list_c_index_of(list_c *l, char val); // returns index of given element. if there is no element in array, returns -1
int list_i_index_of(list_i *l, int val); // returns index of given element. if there is no element in array, returns -1
int list_f_index_of(list_f *l, float val); // returns index of given element. if there is no element in array, returns -1

void list_c_sort(list_c *l); // sorts list of chars

char* list_s_pop(list_s* l); // returns and removes last added element in list of strings
char list_c_pop(list_c* l); // returns and removes last added element in list of chars 
int list_i_pop(list_i* l); // returns and removes last added element in list of integers
float list_f_pop(list_f* l); // returns and removes last added element in list of floats

char list_c_shift(list_c* l); // returns and removes first added element in list of chars 
float list_f_shift(list_f* l); // returns and removes first added element in list of floats

float list_f_take_at(list_f* l, int idx); // takes element at i position
char list_c_take_at(list_c* l, int idx); // takes element at i position

void list_f_insert_at(list_f* l, int idx, float val); // inserts a val at idx position and shifts all elements by one

char* tolower_s(char* str); // lowers the string. Help function from mystr.h

#endif