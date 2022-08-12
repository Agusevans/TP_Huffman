#ifndef _FUNCIONES_HPP
#define _FUNCIONES_HPP

#include <iostream>
#include "../librerias/funciones/files.hpp"
#include "../librerias/funciones/strings.hpp"
#include "../librerias/tads/HuffmanTree.hpp"
#include "../librerias/tads/List.hpp"
#include "../librerias/tads/BitReader.hpp"
#include "../librerias/tads/BitWriter.hpp"
#include <cstring>

struct HuffmanTable // Guarda el codigo y cuantas veces esta un caracter en un archivo
{
  unsigned int contadorOcurrecias;
  string codigo;
};

struct Ocurrencias
{
  int cantH;          // cantidad total de hojas
  unsigned int cantT; // cantidad total de caracteres del archivo a comprir
};

#endif