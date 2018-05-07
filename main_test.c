#include <stdio.h>
#include "../src/malloc.h"
#define AMOUNT 10000
#define S 4090
#define M getpagesize() * 32 - sizeof(t_block)
#define L getpagesize * 32
#include <limits.h>

int main() {
    int i;
    int j;
    char *test[AMOUNT];

    for (i = 0; i < AMOUNT; i++) {
        if(i == 95)
            printf("");
        test[i] = malloc(100);
        if (!test[i]) {
            printf("Error!\n");
            i--;
            break;
        }
    }
	show_alloc_mem();
    show_all_mem_test();
    printf("\n");
    printf("///////////////malloc finished///////////////\n");
    printf("\n");

    for (j = i; j > 0; j--) {
        free(test[j- 1]);
    }
    show_all_mem_test();
}
