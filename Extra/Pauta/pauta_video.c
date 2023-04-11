#include <stdio.h>

int bits1(int n);
int posicionBits(int x, int p, int n);
unsigned repBits(unsigned x, int i, int k, unsigned val);

int main() {
	printf("bits1 de 9 es %d!\n", bits1(152));
	int res = posicionBits(202, 9, 4);
	printf("posicionBits(0x562, 0xB, 4) == %d\n", res);
	//printf("posicionBits(0x01010101, 0, 8) == %d\n", posicionBits(0x01010101, 0, 8));
	printf("repBits(0x5555FFFF, 8, 12, 0x123) == 0x%X\n", repBits(0x5555FFFF, 8, 12, 0x123));
	return 0;
}

// P1.
int bits1(int n) {
	// 000000000000000000000000000000000 -> 0  // 0
	// 000000000000000000000000000000001 -> 1  // 1
	// 000000000000000000000000000000010 -> 1| // 2
	// 000000000000000000000001010101010 -> 5  //682
	int total = 0;
	// 10101010100100110 >>
	// 01010101010010011
	// 00101010101001001
	// 00000000000000001
	// sizeof(int): BYTES que definen a un integer
	for (unsigned long i = 0; i < sizeof(n)*8; i++){
		if (((n>>i) & 1) == 1){
			total++;
		}
	} 
	return total;
}

// decimal: 202
// haxadecimal: CA
// binario: 11001010

// P2.
int posicionBits(int x, int p, int n) {
	// x: 11001010 &
	// p: 0001
	// n: 4
	// ex: 10000000000000000000000000000000000000000000
	// 000000000000000000000000000000000000000000000001
	// m: 00000110 : 6
	// res:0000010 
	unsigned m = -1;
	int mask = ~(m << n);
	for(unsigned long i = 0; i < sizeof(x)*8 - n + 1;i++){
		if (((x >> i) & mask) == p){
			return i; 
		}
	}
	return -1;
	// x: 00000000000000000000011001010 &
	// x: 00000000000000000000000100100 &
	// 00000000000000000000000000001111
	// 00000000000000000000000000001001
}

// P3.
unsigned repBits(unsigned x, int i, int k, unsigned val) {
	// 10011
	// i: 3
	// 0000000000000000000000011111
	// 0000000000000000000011111000
	
	// 1010101010101010001001011000
	// 1010101010101010001000000000
	unsigned m = -1;	
	unsigned mask1 = ~(m<<k); // 000...011...1 con k unos
	unsigned mask2 = mask1 << i; // 0...0 1^{k} 0^{i}
	x &= ~mask2; // 1111111111111111111100000111 &
	val <<= i;   // 0000000000000000000010011000
	x |= val;    // 1010101010101010001000000000
	             // 1010101010101010001010011000
	return x;

	// 11010101010101010001000100
	// 11010101010101010001010001
}