#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "lib/aList/aList.h"
#include "lib/aString/aString.h"
#include "lib/mparser/mparser.h"

int main() {
    list_f nums = {0};
    list_c ops = {0};
    string source = string_init("(2+2)*2");

    int count_op = string_count_val(&source, '(');
    int count_cp = string_count_val(&source, ')');

    if (count_op != count_cp) {
        printf("Your string lacks of parenthesis\n");
        return -1;
    }

    int shift = 0;
    float r = mparser_parse(source, &shift);
    printf("%f", r);

    return 0;
}