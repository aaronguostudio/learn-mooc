#include <stdio.h>
int fact (int n);

int main (int argc, char **argv) {
  printf("fact: %d\n", fact(4));
  return 0;
}

int fact (int n)
{
  if (n == 1) return 1;
  else return n * fact(n-1);
}