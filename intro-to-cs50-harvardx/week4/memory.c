#include <stdio.h>
#include <stdlib.h>

void f (void);

int main (void)
{
    f();
}

void f (void)
{
    int *x = malloc(10 * sizeof(int));
    x[10] = 10;
    printf("You inputted %i.\n", x[10]);
}
