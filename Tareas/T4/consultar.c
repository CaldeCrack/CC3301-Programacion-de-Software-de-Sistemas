#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "pss.h"

#define MAXTAM (800+2)

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