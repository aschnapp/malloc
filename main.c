#include <stdio.h>
#include "src/malloc.h"
#define AMOUNT 5
#define S 4090
#define M getpagesize() * 32 - sizeof(t_block)
#define L getpagesize * 32

int main() {
    int i;
    int j;
    char *test[AMOUNT];
    for (i = 0; i < AMOUNT; i++) {
        // printf("%d\n", i);
        if(i == 95)
            printf("");
        test[i] = malloc(1000);
        if (!test[i]) {
            printf("Error!\n");
            i--;
            break;
        }
    }
    // show_alloc_mem();
    printf("\n");
    printf("///////////////malloc finished///////////////\n");
    printf("\n");
    (void)j;
    free(test[2]);
    test[1] = realloc(test[1], 1500);

    // for (j = 0; j < i; j++) {
    //     free(test[j]);
    // }
    show_alloc_mem();
}
