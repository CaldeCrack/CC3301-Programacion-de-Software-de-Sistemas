#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "reemplazar.h"

int main(){
  char* res = reemplazo("banjaar", 'a', "alo");
  printf("res: %s\n", res);
  return 0;
}

char* reemplazo(char *s, char c, char *pal) {
  int len = 0, lenP = 0, aux = 0;
  while(*s++) len++;
  s-=len+1;
  while(*pal++) lenP++;
  pal-=lenP+1;
  char* newStr = malloc(len*lenP+1);
  while(len--){
    if(*s==c){
      strcpy(newStr, pal);
      newStr+=lenP-1;
      aux+=lenP-1;
    } else *newStr = *s;
    aux++; s++; newStr++;
  }
  *newStr = '\0';
  newStr-=aux;
  return newStr;
}

void reemplazar(char *s, char c, char *pal) {
  return;
}