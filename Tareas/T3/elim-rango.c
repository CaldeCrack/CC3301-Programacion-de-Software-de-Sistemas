#include <stdio.h>
#include <stdlib.h>

#include "elim-rango.h"

void eliminarRango(Nodo **phead, double y, double z) {
  int lower = 0, greater = 1;
  Nodo *first, *last;
  printf("x: %f\ny: %f\n", y, z);
  while((*phead) -> x < y){
    lower = 1;
    first = *phead;
    Nodo *head = *phead;
    *phead = head -> prox;
  }
  while((*phead) -> x <= z){
    printf("phead: %i\n", (*phead) -> x);
    Nodo *head = *phead;
    *phead = head -> prox;
    free(head);
    last = *phead;
    if(*phead == NULL){
      greater = 0;
      break;
    }
  }
  if(lower && greater){
    *phead = first;
    (*phead) -> prox = last;
  }
}