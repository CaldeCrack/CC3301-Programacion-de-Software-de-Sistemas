#include <stdio.h>
#include <stdlib.h>

int bits1(int n);
int posicionBits(int x, int p, int n);
unsigned repBits(unsigned x, int i, int k, unsigned val);

// int main(int argc, char* argv[]) {
//   - P3 -
//   if (argc != 5) 
//     printf("Uso correcto: %s <x> <i> <k> <val>", argv[0]);
//   int x_test = atoi(argv[1]);
//   int i_test = atoi(argv[2]);
//   int k_test = atoi(argv[3]);
//   int val_test = atoi(argv[4]);
//   printf("El resultado de reemplazar los %d bits de 0x%x en el %d-esimo bit de 0x%x es 0x%x\n", k_test, val_test, i_test, x_test, repBits(x_test, i_test, k_test, val_test));

//  - P2 -
//  if (argc != 4) 
//    printf("Uso correcto: %s <x> <p> <n>", argv[0]);
//  int x_test = atoi(argv[1]);
//  int p_test = atoi(argv[2]);
//  int n_test = atoi(argv[3]);
//  printf("El patrón de %d bits de 0x%x esta en el %d bit de 0x%x\n", n_test, p_test, posicionBits(x_test, p_test, n_test), x_test);

//  - P1 -
//  if (argc != 2) 
//    printf("Uso correcto: %s <n>", argv[0]);
//  int test = atoi(argv[1]);
//  printf("0x%x tienen %d bits en 1\n", test, bits1(test));

// }

// - P1 -
int bits1(int n){ 
  int mask = 0x1;
  int cnt = 0;
  for(int i = 0; i < sizeof(n)*8; i++) {
    if((n>>i) & mask) { // (n>>i & mask) == 1
      cnt++;
    }
  }
  return cnt;
}

// - P2 -
int posicionBits(int x, int p, int n) {
  int mask = ~(-1<<n); // 000.....111
  p &= mask; // p = p & mask
  for(int i=0; i<sizeof(x)*8-n+1; i++) {
    if(((x>>i)&mask) == p) {
      return i+1;
    }
  }
  return -1;
}

// - P3 -
unsigned repBits(unsigned x, int i, int k, unsigned val) {
  int mask1 = (~(-1<<k))<<i;
  x = (x&~mask1);
  val <<= i;
  val &= mask1;
  return x | val;
}
