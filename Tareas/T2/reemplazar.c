#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "reemplazar.h"

// int main(){
//   char res[25] = "%&/(hola que tal\0    )=?";
//   char *r= &res[4];
//   reemplazar(r, 'a', "opa");
//   reemplazar(r, 'o', "");
//   return 0;
// }

char* reemplazo(char *s, char c, char *pal) {
  int len = strlen(s), lenP = strlen(pal), matches = 0;
  if(*s==c) matches++;
  while(*s++) if(*s==c) matches++;
  s-=len+1;
  int newStrLen = len+matches*(lenP-1);
  char* newStr = malloc(newStrLen+1);
  while(len--){
    if(*s==c){
      strcpy(newStr, pal);
      newStr+=lenP-1;
    } else *newStr = *s;
    s++; newStr++;
  }
  *newStr = '\0';
  newStr-=newStrLen;
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
  char *str = s+len+matches*(lenP-1);
  // char *strAux = s;
  str--;
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
  str += len+matches*(lenP-1)+1;
  *str = '\0';
  }
}