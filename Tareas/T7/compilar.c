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

// Cola global
Queue *q;

// Devuelve 0 si el archivo no debe compilarse
// Devuelve 1 sino
// c := nombre del archivo .c
// o := nombre del archivo a comparar con c
// sc := fecha del archivo .c
// so := fecha del archivo a comparar con c
int compilable(char *c, char *o, int sc, int so) {
  int lenC = strlen(c), lenO = strlen(o);
  // Archivos no coinciden en largo o potencial archivo ".o" tiene fecha posterior al archivo ".c"
  if (lenC != lenO || sc <= so) {
    return 1;
  }
  // Tienen el mismo nombre hasta el "." que indica la extension
  if (!strncmp(c, o, lenC-1)) {
    o += lenO-1;
    // El archivo tiene extensión ".o" y dado que llego aquí sabemos que no debe compilarse
    if(*o == 'o') {
      return 0;
    }
  }
  // El archivo tenía mismo largo y tenía fecha previa al archivo ".c"
  // pero no tenía el nombre correspondiente
  return 1;
}

// Recorrer el directorio
// nom := nombre del archivo actual
// root := nombre del directorio en el que está nom
void listDir(char *nom, char *root) {
  struct stat st_nom;
  int rc;
  rc= stat(nom, &st_nom);

  if (rc!=0) {
    printf("%s no existe\n", nom);
    exit(0);
  }
  if (S_ISREG(st_nom.st_mode)) {
    // Procesar archivo regular
    int len = strlen(nom);
    char *c = ".c";
    // Archivos que terminan en ".c"
    if (!strcmp(c, nom+len-2)) {
      // Asumimos inicialmente que el archivo debe compilarse
      int compile = 1;
      // Encontrar si existe un archivo ".o" en el mismo directorio que se corresponda con el archivo ".c"
      DIR *dir = opendir(root);
      for (struct dirent *entry = readdir(dir); entry != NULL; entry = readdir(dir)) {
        if (strcmp(entry->d_name, ".")==0 || strcmp(entry->d_name, "..")==0) {
          continue;
        }
        // Nombre del archivo que estamos revisando
        char *nom_arch= malloc(strlen(nom)+strlen(entry->d_name)+2);
        strcpy(nom_arch, nom);
        strcat(nom_arch, "/");
        strcat(nom_arch, entry->d_name);
        // Creamos el stat del archivo a revisar
        struct stat st_o;
        stat(nom_arch, &st_o);
        // Si el archivo no necesita compilarse lo evitamos
        if (!compilable(nom, nom_arch, st_nom.st_mtime, st_o.st_mtime)) {
          free(nom_arch);
          compile = 0;
          break;
        }
        free(nom_arch);
      }
      closedir(dir);
      // Si no se encontró archivo ".o" con las condiciones hay que compilar el archivo
      if (compile) {
        put(q, nom);
        printf("%s\n", nom);
      }
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
      listDir(nom_arch, nom);
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
  // Encontrar archivos .c validos
  listDir(argv[1], argv[1]);
  // Ordenar queue


  // Potencialmente liberar memoria


  return 0;
}