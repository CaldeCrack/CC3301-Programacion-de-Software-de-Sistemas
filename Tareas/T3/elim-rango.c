#include <stdio.h>
#include <stdlib.h>

#include "elim-rango.h"

// static Nodo *lista(int x, Nodo *cola) {
//   Nodo *nodo= malloc(sizeof(Nodo));
//   if (nodo==NULL) {
//     exit(1);
//   }
//   nodo->x= x;
//   nodo->prox= cola;
//   return nodo;
// }

// static Nodo *listaTest() {
//   return lista(2, lista(4, lista(7, lista(8, lista(9, NULL)))));
// }

// int main(){
//   Nodo *head = listaTest();
//   eliminarRango(&head, 5, 7);
// }

void eliminarRango(Nodo **phead, double y, double z) {
  int lower = 0, greater = 1;
  Nodo *first, *last, *origin = *phead;
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
    if(*phead == NULL){
      greater = 0;
      break;
    }
  }
  if(lower){
    *phead = first;
    (*phead) -> prox = last;
  }
  if(lower && !greater) *phead = origin;
}