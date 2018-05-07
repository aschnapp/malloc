# 42 Malloc

## Basic Testing
```
git checkout test
```
```
python test/test.py
```

## Additional Tests
```test/main.c``` and ```show_all_mem_test``` are an additional test files. Makefile should have an additional flag ```-DDEBUG_MODE``` when using these test files.
Use the function ```show_all_mem_test``` to see all memory blocks.

To compile the additional test:\
```make && gcc -o malloc_test main_test.c```\
To run the additional test:\
```./malloc_test```

