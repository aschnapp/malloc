# 42 Malloc

## Features
Basic defragmentation if the block to right is also free.
*Will not defrag if freeing from right to left

## Known Problems
Chrome and Firefox segfaults when a pointer they pass in a pointer to be realloced that was not malloced by this malloc. 
This realloc will return a NULL if the pointer does not belong to it, and Chrome and FF does not have the right protection.
To see this in action: 
1: Add a printf statement between line 102 and 103 and between 103 and 104 in realloc.c
2: Add a printf before return (1) in check_ptr_ownership in free.c
3: ./run.sh (/Application/{chrome app})

It will segfault after it returns from realloc with a NULL pointer
