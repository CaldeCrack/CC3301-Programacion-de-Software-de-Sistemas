#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "reemplazar.h"

// int main(){
//   char r[15] = "banjaar";
//   reemplazar(r, 'a', "ou");
//   printf("r: %s\n", r);
//   return 0;
// }

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
  int len = 0, lenP = 0, matches = 0;
  while(*s++){
    len++;
    if(*s==c) matches++;
  }
  s-=len+1;
  while(*pal++) lenP++;
  pal-=2;
  char *final = s+len;
  char *str = s+len+matches*(lenP-1)-1;
  if(lenP<2){
    while(*s++){
      if(*s==c) *str = *pal;
    }
  } else {
    while(*final--!=*s){
      if(*final==c){
        for(int i=0; i<lenP; i++){
          *str = *pal;
          pal--; str--;
        }
        pal+=lenP; str++;
      } else *str = *final;
      str--;
    }
  }
}