# How compiling works
- preprocessing
- compiling
- assembling
- linking

# Assembly
```
pushq
movq
subq
xorl
movl
movabsq
movb
callq
movabsq
movq
movq
movb
callq
```

# Sorting
- bubble sort
- selection sort


# Arrays in C
```c
int foo[5] = { 1,2,3,4,5 };
int bar[5];

// invalid in C
foo = bar

// have to do in this
for (int j = 0; j < 5; j++)
{
  bar[j] = foo[j]
}
```

```c
// array passed in function as reference
```


# Dynamic Memory Allocation
```c
// statically obtain an integer
// created on the stack
int x;

// dynamically obtain an integer
// created on the heap
int *px = malloc(sizeof(int));

// array of floats on the stack
float stack_array[x];

// array of floats on the heap
float* heap_array = malloc(sizeof(float) * x);

// free
char* word = malloc(sizeof(char) * 50);
// do some stuff
free(word);

```