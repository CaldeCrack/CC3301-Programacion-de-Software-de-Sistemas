#include <stdlib.h>
#include <string.h>

#include "comprimir.h"

typedef unsigned int uint;

int maxK(int n, uint l) {
  int k = 0, n1 = n;
  while (n <= l) {
    n+=n1;
    k++;
  }
  return k;
}

uint comprimir(uint a[], int nbits) {
  uint one = 1, t = 0, l = sizeof(uint) << 3, mask = (one<<(nbits-1)<<1)-1;
  int k = maxK(nbits, l);
  for (int i = 0; i < k; i++) {
    t = t << (nbits-1) << 1;
    t += a[i] & mask;
  }
  return t;
}