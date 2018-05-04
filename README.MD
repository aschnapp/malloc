# 42 Malloc

## Features
Basic defragmentation if the block to right is also free.
*Will not defrag if freeing from right to left

## Basic Testing
```python test/test.py```

```run.sh``` does not work very well for some reason, so modified the ```test.py``` file that was given to not include the ```run.sh``` file during tests.

## Additional Tests
```test/main.c``` and ```show_all_mem_test``` are an additional test files. Makefile should have an additional flag ```-DDEBUG_MODE``` when using these test files.
Use the function ```show_all_mem_test``` to see all memory blocks.

To compile the additional test:\
```make && gcc -o test/bin/malloc_test test/main.c```\
To run the additional test:\
```./test/bin/malloc_test```

