// Plantilla para maleta.c

#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>

#include "maleta.h"

// Use la funcion leer para obtener los resultados del pipe
int leer(int fd, void *vbuf, int n) {
  char *buf= vbuf;
  do {
    int rc= read(fd, buf, n);
    if (rc<=0)
      return 1; /* fracaso: error o fin del archivo/pipe/socket */
    n-= rc; /* descontamos los bytes leídos */
    buf+= rc; /* avanzamos el buffer para no reescribir lo leido previamente */
  } while (n>0); /* mientras no leamos todo lo que esperamos */
  return 0; /* exito */
}

double llenarMaleta(double w[], double v[], int z[], int n,
                    double maxW, int k) {
  // ... Modifique esta funcion ...
  // Use fork() para crear 8 nuevos procesos.  El padre solo obtiene los
  // resultados de los procesos hijos a traves de pipes, entierra a los
  // los hijos y calcula el resultado final.
  // Base su solucion en el ejemplo que determina un factor de
  // un entero, visto en clase auxiliar.
  // Despues invocar fork() agregue: srandom(getUSecsOfDay()*getpid());
  // Esto es para que cada proceso genere secuencias de numeros aleatorios
  // diferentes.
  // Puede invocar la version secuencial llenarMaletaSec definida en
  // test-maleta.c.
  // ...
  return 0.; // Modifique
}
