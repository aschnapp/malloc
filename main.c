#include <stdio.h>
#include "libmalloc/src/malloc.h"

int main() {
    char *str = malloc(2);
    str[0] = 'a';
    str[1] = 0;
    printf("%s\n", str);
}