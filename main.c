#include <stdio.h>
#include "src/malloc.h"
#define AMOUNT 1000000
#define S 4090
#define M getpagesize() * 32 - sizeof(t_block)
#define L getpagesize * 32
#include <limits.h>

int main() {
    int i;
    int j;
    char *test;
    test = malloc(16);
    free(test + 5);
    // for (i = 0; i < AMOUNT; i++) {
    //     // printf("%d\n", i);
    //     if(i == 95)
    //         printf("");
    //     test[i] = malloc(INT_MAX - 1000000000);
    //     if (!test[i]) {
    //         printf("Error!\n");
    //         i--;
    //         break;
    //     }
    // }
    // show_alloc_mem();
    // show_all_mem_test();
    printf("\n");
    printf("///////////////malloc finished///////////////\n");
    printf("\n");
    // (void)j;
    // // free((char*)test[2] + 100);
    // test[1] = realloc(test[1], 131000);

    // for (j = 0; j < i; j++) {
    //     free(test[j]);
    // }
    // show_all_mem_test();
}
