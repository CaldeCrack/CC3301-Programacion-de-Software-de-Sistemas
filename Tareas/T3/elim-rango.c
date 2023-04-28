#include <stdio.h>
#include <stdlib.h>

#include "elim-rango.h"

void eliminarRango(Nodo **phead, double y, double z) {
  int lower = 0;
  Nodo *first, *last = NULL, *origin = *phead;
  while((*phead) -> x < y){
    lower = 1;
    first = *phead;
    Nodo *head = *phead;
    *phead = head -> prox;
  }
  while((*phead) -> x <= z){
    Nodo *head = *phead;
    *phead = head -> prox;
    free(head);
    last = *phead;
    if(*phead == NULL) break;
  }
  if(lower){
    first -> prox = last;
    *phead = origin;
  }
}