#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "pss.h"

#define MAXTAM (800+2)

/*
Test de la llaves existentes de dicc.txt
Ejecutando: ./prof.ref-x86_64 dicc.txt embarcacion
|todo tipo de artilugio capaz de navegar en el agua                  
Ejecutando: ./prof.ref-x86_64 dicc.txt casa
edificacion construida para ser habitada                                   
Ejecutando: ./prof.ref-x86_64 dicc.txt lluvia
precipitacion de particulas liquidas de agua                             
Ejecutando: ./prof.ref-x86_64 dicc.txt alimento
sustancia ingerida por un ser vivo                                     
Ejecutando: ./prof.ref-x86_64 dicc.txt celular
aparato portatil de un sistema de telefonia celular                     
Ejecutando: ./prof.ref-x86_64 dicc.txt canario
ave paseriforme de la familia de los fringilidos                        
Ejecutando: ./prof.ref-x86_64 dicc.txt palacio
edificio utilizado como residencia de un magnate                        
Ejecutando: ./prof.ref-x86_64 dicc.txt bolsillo
bolsa pequena                                                          
Ejecutando: ./prof.ref-x86_64 dicc.txt correr
andar tan rapidamente que los pies quedan en el aire                     
Ejecutando: ./prof.ref-x86_64 dicc.txt nadar
trasladarse en el agua, con los brazos y sin tocar el suelo               
Ejecutando: ./prof.ref-x86_64 dicc.txt posada
establecimiento economico de hospedaje para viajeros                     
Ejecutando: ./prof.ref-x86_64 dicc.txt taladro
herramienta aguda o cortante con que se agujerea la madera              
Ejecutando: ./prof.ref-x86_64 dicc.txt perro
mamifero domestico con olfato muy fino, inteligente y leal                
Ejecutando: ./prof.ref-x86_64 dicc.txt techo
parte superior de un edificio que lo cubre y cierra                       
-----------------------------------------------------------
Test de una llave inexistente
Ejecutando: ./prof.ref-x86_64 dicc.txt gato
dicc.txt: el diccionario no contiene la llave gato
Bien.  Se diagnostico correctamente el error.
-----------------------------------------------------------
Test con un diccionario inexistente
Ejecutando: ./prof.ref-x86_64 nodicc.txt bolsillo
nodicc.txt: No such file or directory
Bien.  Se diagnostico correctamente el error.
-----------------------------------------------------------
Test con diccionario sin permiso de lectura
Ejecutando: ./prof.ref-x86_64 /tmp/dicc.txt posada
/tmp/dicc.txt: Permission denied
Bien.  Se diagnostico correctamente el error.
-----------------------------------------------------------
Test de uso incorrecto de parametros
Ejecutando: ./prof.ref-x86_64 dicc.txt bolsillo bolsa
Uso: ./consultar.bin <diccionario> <llave>
Bien.  Se diagnostico correctamente el error.
Ejecutando: ./prof.ref-x86_64 bolsillo
Uso: ./consultar.bin <diccionario> <llave>
Bien.  Se diagnostico correctamente el error.
-----------------------------------------------------------
Test de un diccionario vacio
Ejecutando: ./prof.ref-x86_64 vacio.txt perro
vacio.txt: el dicionario esta vacio
Bien.  Se diagnostico correctamente el error.
-----------------------------------------------------------
Test de un diccionario con lineas de tamaño variable
Ejecutando: ./prof.ref-x86_64 dicc-bad.txt perro
dicc-bad.txt: linea 30 de tamaño incorrecto
Bien.  Se diagnostico correctamente el error.
Ejecutando: ./prof.ref-x86_64 dicc-bad2.txt taladro
dicc-bad2.txt: el tamaño del archivo no es multiplo del tamaño de la linea
Bien.  Se diagnostico correctamente el error.
-----------------------------------------------------------
Test de un diccionario con una linea sin :
Ejecutando: ./prof.ref-x86_64 dicc-bad3.txt celular
dicc-bad3.txt: linea 28 no posee : para terminar la llave
Bien.  Se diagnostico correctamente el error.
-----------------------------------------------------------
Test de un diccionario de tamano distinto
Ejecutando: ./prof.ref-x86_64 dicc2.txt celular
aparato portatil de un sistema de telefonia celular           
Ejecutando: ./prof.ref-x86_64 dicc2.txt taladro
herramienta aguda o cortante con que se agujerea la madera    
Ejecutando: ./prof.ref-x86_64 dicc2.txt pedro
dicc2.txt: el diccionario no contiene la llave pedro
Bien.  Se diagnostico correctamente el error.
-----------------------------------------------------------
Test de busqueda en un diccionario completamente lleno
Ejecutando: ./prof.ref-x86_64 dicc3.txt celular
aparato portatil de un sistema de telefonia celular           
Ejecutando: ./prof.ref-x86_64 dicc3.txt posada
establecimiento economico de hospedaje para viajeros           
Ejecutando: ./prof.ref-x86_64 dicc3.txt gato
dicc3.txt: el diccionario no contiene la llave gato
Bien.  Se diagnostico correctamente el error.

Felicitaciones: aprobo todos los tests
*/

int main(int argc, char *argv[]) {
  // wrong use of the comand
  if(argc!=3){
    fprintf(stderr, "Uso: ./consultar.bin <diccionario> <llave>\n");
    exit(1);
  }

  // initial data
  char buff[MAXTAM];
  char *arch = argv[1], *key = argv[2];
  int lenKey = strlen(key);
  FILE *fileDicc = fopen(arch, "r");

  // file does not exist
  if(!fileDicc){
    perror(arch);
    exit(1);
  }

  // first line length
  int lenLine = 0;
  if(fgets(buff, MAXTAM, fileDicc) != NULL) lenLine = strlen(buff);

  // empty file
  if(!lenLine){
    fprintf(stderr, "%s: el dicionario esta vacio\n", arch);
    exit(1);
  }

  // lines greater than the limit
  if(lenLine>MAXTAM){
    fprintf(stderr, "%s: el tamaño de las lineas excede el maximo permitido", arch);
    exit(1);
  }

  // file length
  fseek(fileDicc, 0, SEEK_END);
  int lenArch = ftell(fileDicc);
  int lines = lenArch/lenLine;
  int n = hash_string(key)%lines, j = lines;

  // archive not a multiple of the first line length
  if(lenArch%lenLine){
    fprintf(stderr, "%s: el tamaño del archivo no es multiplo del tamaño de la linea\n", arch);
    exit(3);
  }

  // read file
  while(j--){
    // line of different size
    int l = 0;
    if (fgets(buff, MAXTAM, fileDicc)) {
        while (buff[l] != '\n' && buff[l] != '\0') l++;
    }
    if(++l != lenLine && l != 1){
      fprintf(stderr, "%s: linea %i de tamaño incorrecto\n", arch, n-1);
      exit(1);
    }

    // read line
    fseek(fileDicc, n*lenLine, SEEK_SET);
    fread(buff, lenLine, 1, fileDicc);

    // compare keys
    int rc = strncmp(key, buff, lenKey);

    // same keys
    if(!rc){
      // does not have the : character after the key
      if(buff[lenKey] != ':'){
        fprintf(stderr, "%s: linea %i no posee : para terminar la llave\n", arch, n);
        exit(1);
      }

      // without errors the key is in the file
      fseek(fileDicc, n*lenLine+lenKey+1, SEEK_SET);
      fgets(buff, lenLine, fileDicc);
      fprintf(stdout, buff);
      return 0;
    }

    // next line
    if(++n>lines) n=0;
  }
  // the requested key is not in the file
  fprintf(stderr, "%s: el diccionario no contiene la llave %s\n", arch, key);
  fclose(fileDicc);
  exit(1);
}