#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "pss.h"

#define MAXTAM (800+2)

//* bash test-consultar.sh ./prof.ref-$ARCH

int main(int argc, char *argv[]) {
  // initial data
  char buf[MAXTAM];
  char *arch = argv[1];
  char *key = argv[2];
  int lenKey = strlen(key);
  char *bufKey[lenKey];

  // empty dictionary
  FILE *fileDicc = fopen(arch, "r");
  if (!fileDicc){
    fprintf(stderr, "%s: el dicionario esta vacio", arch);
    exit(1);
  }

  // first line length
  int lenLine;
  while(1){
    if(!fgets(buf, MAXTAM, fileDicc)) break;
  lenLine = strlen(buf);
  }
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
  int lines = lenArch/lenLine;
  long n = hash_string(key)%lines, j = lines-1;

  // read file
  while(j--){
    fseek(fileDicc, n*lenLine, SEEK_SET);
    if(fread(&bufKey, lenLine, 1, fileDicc) != 1){
      fprintf(stderr, "%s: linea %ld de tamaño incorrecto", arch, n);
      exit(4);
    }
    int rc = strncmp(key, *bufKey, lenKey);

    // it does not have the :
    if(*bufKey[lenKey] != ':'){
      fprintf(stderr, "%s: linea %ld no posee : para terminar la llave", arch, n);
      exit(5);
    }

    // same keys
    if(!rc){
      break;
    }

    // next line
    n++;
    if(n>lines) n=0;
  }
}