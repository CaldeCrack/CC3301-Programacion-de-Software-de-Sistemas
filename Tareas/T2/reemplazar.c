#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "reemplazar.h"

int main(){
  char* res = reemplazo("bonjour", 'a', "alo");
  printf("res: %s\n", res);
  return 0;
}

char* reemplazo(char *s, char c, char *pal) {
  int len = 0, lenP = 0;
  while(*s++) len++;
  s-=len+1;
  while(*pal++) lenP++;
  pal-=lenP+1;
  char* newStr = malloc(len*lenP+1);
  while(len--){
    if(*s==c){
      while(*pal++){
        strcpy(newStr, pal);
        // *newStr = *pal;
        newStr++;
        pal++;
      }
      pal-=lenP+1;
    }else{
      // strcpy(newStr, *s);
      *newStr = *s;
    }
    s++;
    newStr++;
  }
  *newStr = '\0';
  newStr-=len+1;
  // printf("newStr: %s\n", newStr);
  // *newStr = "a";
  // free(newStr);
  return newStr;
}





void reemplazar(char *s, char c, char *pal) {
  return;
}