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