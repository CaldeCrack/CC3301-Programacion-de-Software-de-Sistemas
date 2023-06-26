#define _POSIX_C_SOURCE 200809L
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#include "pss.h"

void listDir(char *nom) {
  struct stat st_nom;
  int rc;
  rc= stat(nom, &st_nom);

  if (rc!=0) {
    printf("%s no existe\n", nom);
    exit(0);
  }
  printf("%s\n", nom); //* aqui se imprimen los archivos
  if (S_ISREG(st_nom.st_mode)) {
    // Procesar archivo
    int len = strlen(nom);
    char *c = ".c";
    nom += len-2;
    // Archivos que terminan en ".c"
    if (!strcmp(c, nom)) {
      
    }
  }
  else if (S_ISDIR(st_nom.st_mode)) {
    // Es un directorio
    DIR *dir = opendir(nom);
    if (dir == NULL) {
      perror(nom);
      exit(1);
    }
    for (struct dirent *entry = readdir(dir); entry != NULL; entry = readdir(dir)) {
      if (strcmp(entry->d_name, ".")==0 || strcmp(entry->d_name, "..")==0) {
        continue;
      }
      char *nom_arch= malloc(strlen(nom)+strlen(entry->d_name)+2);
      strcpy(nom_arch, nom);
      strcat(nom_arch, "/");
      strcat(nom_arch, entry->d_name);
      listDir(nom_arch);
      free(nom_arch);
    }
    closedir(dir);
  }
  else {
    // Podria ser un dispositivo, un link simbolico, etc.
    fprintf(stderr, "Archivo %s es de tipo desconocido\n", nom);
    exit(1);
  }
}

int main(int argc, char *argv[]) {
  if (argc!=2) {
    fprintf(stderr, "uso: %s <arch|dir>\n", argv[0]);
    exit(1);
  }
  listDir(argv[1]);
  return 0;
}