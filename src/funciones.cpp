#ifndef _FUNCIONES
#define _FUNCIONES

#include "funciones.hpp"

void inicializarTabla(HuffmanTable tabla[]) // inicio el contador de cada caracter en 0
{
  for (int i = 0; i < 256; i++)
  {
    tabla[i] = {0, ""};
  }
}

void contarOcurrencias(string pathArchivo, HuffmanTable tabla[])
{
  cout << "Contando ocurrencias" << endl;

  FILE *archivo = fopen(pathArchivo.c_str(), "r+b");
  inicializarTabla(tabla);

  int caracterLeido = read<unsigned char>(archivo); 
  while (!feof(archivo))
  {
    tabla[caracterLeido].contadorOcurrecias++;
    caracterLeido = read<unsigned char>(archivo);
  }

  fclose(archivo);
}

int cmpInfo(HuffmanTreeInfo a, HuffmanTreeInfo b)
{
  int ret = a.n - b.n; // comparo por ocurrencias de menor a mayor
  if (ret == 0)        // si aparecen las mismas veces
  {
    ret = a.c < b.c ? -1 : 1; // comparo por ascii de menor a mayor
  }

  return ret;
}

void crearLista(List<HuffmanTreeInfo> &lista, HuffmanTable tabla[])
{
  cout << "Creando lista enlazada" << endl;

  for (int i = 0; i < 256; i++)
  {
    unsigned int contador = tabla[i].contadorOcurrecias; // ocurrencias de cada caracter
    if (contador > 0)                                    // si el caracter estaba en el archivo
    {
      unsigned char c = i;
      HuffmanTreeInfo nodo = {c, contador, NULL, NULL}; 
      listOrderedInsert<HuffmanTreeInfo>(lista, nodo, cmpInfo);
    }
  }
}

HuffmanTreeInfo *crearArbol(List<HuffmanTreeInfo> &lista)
{
  cout << "Creando arbol binario" << endl;

  int i = 256;

  HuffmanTreeInfo a = listRemoveFirst<HuffmanTreeInfo>(lista);
  while (listSize<HuffmanTreeInfo>(lista) > 0)
  {
    HuffmanTreeInfo b = listRemoveFirst<HuffmanTreeInfo>(lista);

    HuffmanTreeInfo *ha = huffmanTreeInfo(a.c, a.n, a.left, a.right);
    HuffmanTreeInfo *hb = huffmanTreeInfo(b.c, b.n, b.left, b.right);
    HuffmanTreeInfo *hc = huffmanTreeInfo(i, a.n + b.n, hb, ha);

    listOrderedInsert<HuffmanTreeInfo>(lista, *hc, cmpInfo);

    i++;
    a = listRemoveFirst<HuffmanTreeInfo>(lista);
  }
  HuffmanTreeInfo *raiz = huffmanTreeInfo(a.c, a.n, a.left, a.right);

  return raiz;
}

void cargarCodigosEnTabla(HuffmanTreeInfo *raiz, HuffmanTable tabla[])
{
  cout << "Cargando codigos en tabla" << endl;

  HuffmanTree ht = huffmanTree(raiz);

  string cod;
  while (huffmanTreeHasNext(ht))
  {
    HuffmanTreeInfo *x = huffmanTreeNext(ht, cod);
    tabla[x->c].codigo = cod;
    /*cout << (char)x->c << ", (" << tabla[x->c].n << "), "
         << "[" << tabla[x->c].cod << "]" << endl;*/
  }
}

Ocurrencias cantOcurrencias(HuffmanTable tabla[])
{
  Ocurrencias o = {-1, 0};
  for (int i = 0; i < 256; i++)
  {
    if (tabla[i].contadorOcurrecias > 0)
    {
      o.cantH++;
      o.cantT += tabla[i].contadorOcurrecias;
    }
  }
  return o;
}

string nombreDelArchivo(string path)
{
  int index = lastIndexOf(path, '/');
  string nombre;
  if (index > -1)
    nombre = substring(path, index + 1);
  else
    nombre = path;

  return nombre;
}

FILE *abrirArchivo(string pathArchivo, string extension)
{
  string nombre = nombreDelArchivo(pathArchivo) + extension;

  return fopen(("../salida/" + nombre).c_str(), "w+b");
}

void grabarArchivoComprimido(string pathArchivo, HuffmanTable tabla[])
{
  cout << "Grabando archivo" << endl;

  FILE *archivoComprimido = abrirArchivo(pathArchivo, ".huf");

  Ocurrencias o = cantOcurrencias(tabla);
  // cout<<"Hojas: "<<o.cantH+1<<", Cant bytes: "<<o.cantT<<endl; //prueba

  write<unsigned char>(archivoComprimido, o.cantH); // Escribo cant hojas

  for (int j = 0; j < 256; j++)
  {
    if (tabla[j].contadorOcurrecias > 0) // Escribo registros x cada hoja
    {
      write<unsigned char>(archivoComprimido, (unsigned char)j);

      string cod = tabla[j].codigo;
      unsigned int longCod = length(cod);
      write<unsigned char>(archivoComprimido, longCod);

      for (unsigned int i = 0; i < longCod; i++)
      {
        write<unsigned char>(archivoComprimido, (unsigned char)cod[i]);
      }
    }
  }

  write<unsigned int>(archivoComprimido, o.cantT); // Escribo cant bytes

  // Reabro el archivo original para escribir
  FILE *archivoOriginal = fopen(pathArchivo.c_str(), "r+b");

  BitWriter b = bitWriter(archivoComprimido);
  int c = read<unsigned char>(archivoOriginal);
  while (!feof(archivoOriginal))
  {
    string cod = tabla[c].codigo;
    for (int j = 0; j < length(cod); j++)
    {
      int bit = charToInt((unsigned char)cod[j]);
      bitWriterWrite(b, bit); // Escribo los codigos bit x bit
    }
    c = read<unsigned char>(archivoOriginal);
  }
  bitWriterFlush(b);

  fclose(archivoOriginal);
  fclose(archivoComprimido);

  cout << "Compresion FINALIZADA" << endl;
}

HuffmanTreeInfo *crearRama(string cod, HuffmanTreeInfo *raiz, unsigned char c)
{
  if (raiz == NULL) // crea la raiz
  {
    raiz = new HuffmanTreeInfo();
  }

  HuffmanTreeInfo *aux = raiz; // puntero auxiliar para recorrer y crear la rama
  for (int i = 0; i < length(cod); i++)
  {
    if (cod[i] == '1')
    {
      if (aux->right == NULL)
      {
        aux->right = new HuffmanTreeInfo();
      }
      aux = aux->right;
    }
    else
    {
      if (aux->left == NULL)
      {
        aux->left = new HuffmanTreeInfo();
      }
      aux = aux->left;
    }
  }
  // cout<<"Rama de: ("<<c<<") ["<<cod<<"]"<<endl;
  aux->c = (unsigned int)c; // el puntero aux queda en la hoja, donde grabo el caracter
  return raiz;
}

HuffmanTreeInfo *recomponerArbol(FILE *archivo)
{
  cout << "Recomponiendo arbol" << endl;

  HuffmanTreeInfo *raiz = NULL;
  unsigned int cantHojas = read<unsigned char>(archivo) + 1;

  for (unsigned int i = 0; i < cantHojas; i++) // mientras no lea todos los caracteres
  {
    string cod = "";

    unsigned char c = read<unsigned char>(archivo);      // leo el caracter
    unsigned int longCod = read<unsigned char>(archivo); // leo la longitud del codigo del caracter

    for (unsigned int j = 0; j < longCod; j++)
    {
      cod += read<unsigned char>(archivo); // obtengo el codigo
    }

    raiz = crearRama(cod, raiz, c);
  }

  return raiz;
}

void reescribirArchivo(HuffmanTreeInfo *raiz, string pathArchivo, FILE *archivoComprimido)
{
  cout << "Reescribiendo archivo descomprimido" << endl;

  int longPath = length(pathArchivo);
  string pathArchivoOrig = substring(pathArchivo, 0, longPath - 4); // le saco el .huf al path
  FILE *archivoOriginal = abrirArchivo(pathArchivoOrig, "");        // Genero el archivo descomprimido

  unsigned int longArchivoOriginal = read<unsigned int>(archivoComprimido);

  BitReader br = bitReader(archivoComprimido);
  for (unsigned int i = 0; i < longArchivoOriginal; i++) // leo con bitreader
  {
    HuffmanTreeInfo *aux = raiz;

    while (aux->left != NULL && aux->right != NULL)
    {
      int bit = bitReaderRead(br);
      if (bit == 0)
      {
        aux = aux->left;
      }
      else
      {
        aux = aux->right;
      }
    }
    write<unsigned char>(archivoOriginal, aux->c); // finalmente, aux estara en la hoja entonces escribo el caracter
    // cout<<"Caracter reescrito: "<<aux->c<<endl;
  }

  fclose(archivoOriginal);
}

void descomprimir(string pathArchivo)
{
  cout << "Iniciando descompresion:" << endl;

  FILE *archivoComprimido = fopen(pathArchivo.c_str(), "r+b");

  HuffmanTreeInfo *raiz = recomponerArbol(archivoComprimido);

  reescribirArchivo(raiz, pathArchivo, archivoComprimido);

  fclose(archivoComprimido);

  cout << "Descompresion Finalizada" << endl;
}

void comprimir(string pathArchivo)
{
  cout << "Iniciando compresion:" << endl;

  // tabla de contadores
  HuffmanTable tabla[256];

  // paso 1
  contarOcurrencias(pathArchivo, tabla);

  // paso 2
  List<HuffmanTreeInfo> lista = list<HuffmanTreeInfo>();
  crearLista(lista, tabla);

  // paso 3
  HuffmanTreeInfo *raiz = crearArbol(lista);

  // paso adicional
  cargarCodigosEnTabla(raiz, tabla);

  // grabar
  grabarArchivoComprimido(pathArchivo, tabla);
}

#endif