#include <stdio.h>
#include "src/malloc.h"

int main() {
    char *ptr = malloc(1000000);
    (void)ptr;
    // int i;
    // for (i = 0; i < 1000; i ++)
    // {
    //     ptr[i] = '1';
    // }
    // ptr[i] = 0;
    // printf("%s\n", ptr);
    // free(ptr);
}
