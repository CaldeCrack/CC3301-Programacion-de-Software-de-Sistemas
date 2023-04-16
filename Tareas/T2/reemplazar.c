#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "reemplazar.h"

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
  *newStr = '\0'; newStr-=newStrLen;
  return newStr;
}

void reemplazar(char *s, char c, char *pal) {
  int len = strlen(s), lenP = strlen(pal), matches = 0;
  if(*s==c) matches++;
  while(*s++) if(*s==c) matches++;
  s-=len+1; pal+=lenP-1;
  if(lenP<2){
    char *str = s;
    while(len--){
      if(*str==c){
        if(lenP) *s=*pal;
        else s--;
      } else *s=*str;
      s++; str++;
    }
    *s = '\0';
  } else {
    char *final = s+len;
    char *str = s+len+matches*(lenP-1);
    *str = '\0'; str--;
    while(final--!=s){
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