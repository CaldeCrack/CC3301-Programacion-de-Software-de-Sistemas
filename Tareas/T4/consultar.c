#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "pss.h"

#define MAXTAM (800+2)

//* bash test-consultar.sh ./prof.ref-$ARCH

int main(int argc, char *argv[]) {
  // initial data
  char buff[MAXTAM];
  char *arch = argv[1], *key = argv[2];
  int lenKey = strlen(key);
  //char *buffKey[lenKey];

  // empty dictionary
  FILE *fileDicc = fopen(arch, "r");
  if (!fileDicc){
    fprintf(stderr, "%s: el dicionario esta vacio", arch);
    exit(1);
  }

  // first line length
  fseek(fileDicc, 0, SEEK_CUR);
  int lenLine = ftell(fileDicc);
  // lines greater than the limit
  if(lenLine>MAXTAM){
    fprintf(stderr, "%s: el tamaño de las lineas excede el maximo permitido", arch);
    exit(2);
  }

  // file length
  fseek(fileDicc, 0, SEEK_END);
  int lenArch = ftell(fileDicc);
  // archive not a multiple of the first line length
  if(!lenArch%lenLine){
    fprintf(stderr, "%s: el tamaño del archivo no es multiplo del tamaño de la linea", arch);
    exit(3);
  }
  char sol[lenLine+1];
  int lines = lenArch/lenLine;
  int n = hash_string(key)%lines, j = lines-1;

  // read file
  while(j--){
    fseek(fileDicc, n*lenLine, SEEK_SET);
    if(fread(buff, lenLine, 1, fileDicc) != 1){
      fprintf(stderr, "%s: linea %i de tamaño incorrecto", arch, n);
      exit(4);
    }

    // it does not have the :
    if(buff[lenKey] != ':'){
      fprintf(stderr, "%s: linea %i no posee : para terminar la llave", arch, n);
      exit(5);
    }

    int rc = strncmp(key, buff, lenKey);

    // same keys
    if(!rc){
      fseek(fileDicc, 1, SEEK_CUR);
      fgets(sol, lenLine-lenKey, fileDicc);
      fprintf(stdout, sol);
    }

    // next line
    if(++n>lines) n=0;
  }
}