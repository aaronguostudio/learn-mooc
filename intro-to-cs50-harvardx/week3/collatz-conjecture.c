#include <stdio.h>

int collatz (int n, int steps);
int main () {
  int steps = 0;
  collatz(27, steps);
  return 0;
}

int collatz (int n, int steps) {
  if (n == 1) return printf("Done with %d steps\n", steps);
  steps++;
  return n % 2 == 0 ? collatz(n / 2, steps) : collatz(n * 3 + 1, steps);
}