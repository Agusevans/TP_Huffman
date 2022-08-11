#ifndef _MAIN
#define _MAIN

#include "funciones.h"

using namespace std;

int main(int argc, char **argv)
{
  if (argc < 2)
    return EXIT_FAILURE;

  string pathArchivo = argv[1];

  if (!endsWith(pathArchivo, ".huf"))
    comprimir(pathArchivo);
  else
    descomprimir(pathArchivo);

  return EXIT_SUCCESS;
}

/*Compilar g++ -o nombredelejecutable.exe nombre.cpp*/

#endif