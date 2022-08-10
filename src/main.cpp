#ifndef _MAIN
#define _MAIN

#include "main.h"

using namespace std;

struct HuffmanTable
{
  unsigned int n;
  string cod;
};

struct Ocurrencias
{
  int cantH; //cantidad total de hojas
  unsigned int cantT; //cantidad total de caracteres del archivo a comprir
};

void inicializarTabla(HuffmanTable tabla[])
{
  for( int i = 0; i<256; i++ )
  {
     tabla[i]= {0,""};
  }
}

void contarOcurrencias(string fName, HuffmanTable tabla[])
{
  cout<<"Contando ocurrencias"<<endl;

  FILE* f = fopen(fName.c_str(),"r+b");
  inicializarTabla(tabla);  //inicio el contador de cada caracter en 0

  int c = read<unsigned char>(f);
  while( !feof(f) )
  {
     tabla[c].n++;
     c = read<unsigned char>(f);
  }

  fclose(f);
}

int cmpInfo(HuffmanTreeInfo a, HuffmanTreeInfo b)
{
  int ret = a.n-b.n;  //comparo por ocurrencias de menor a mayor
  if( ret==0 )   //si aparecen las mismas veces
  {
     ret = a.c<b.c?-1:1;  //comparo por ascii de menor a mayor
  }

  return ret;
}

void crearLista(List<HuffmanTreeInfo>& lista, HuffmanTable tabla[])
{
  cout<<"Creando lista enlazada"<<endl;

  for( int i = 0; i<256; i++ )
  {
     unsigned int cont = tabla[i].n;  //ocurrencias de cada caracter
     if( cont>0 )  //si el caracter estaba en el archivo
     {
        unsigned char c = i;
        HuffmanTreeInfo n = { c, cont, NULL, NULL };
        listOrderedInsert<HuffmanTreeInfo>(lista,n,cmpInfo);
     }
  }
}

HuffmanTreeInfo* crearArbol(List<HuffmanTreeInfo>& lista)
{
  cout<<"Creando arbol binario"<<endl;

  int i = 256;

  HuffmanTreeInfo a = listRemoveFirst<HuffmanTreeInfo>(lista);
  while( listSize<HuffmanTreeInfo>(lista)>0 )  //mientras tenga elementos en la lista
  {
     HuffmanTreeInfo b = listRemoveFirst<HuffmanTreeInfo>(lista);

     HuffmanTreeInfo* ha = huffmanTreeInfo(a.c,a.n,a.left,a.right);
     HuffmanTreeInfo* hb = huffmanTreeInfo(b.c,b.n,b.left,b.right);
     HuffmanTreeInfo* hc = huffmanTreeInfo(i,a.n+b.n,hb,ha);

     listOrderedInsert<HuffmanTreeInfo>(lista,*hc,cmpInfo);

     i++;
     a = listRemoveFirst<HuffmanTreeInfo>(lista);
  }
  HuffmanTreeInfo* ret = huffmanTreeInfo(a.c,a.n,a.left,a.right);

  return ret;
}

void cargarCodigosEnTabla(HuffmanTreeInfo* raiz, HuffmanTable tabla[])
{
  cout<<"Cargando codigos en tabla"<<endl;

  HuffmanTree ht = huffmanTree(raiz);

  string cod;
  while( huffmanTreeHasNext(ht) )
  {
     HuffmanTreeInfo* x = huffmanTreeNext(ht,cod);
     tabla[x->c].cod = cod;
     cout << (char)x->c << ", ("<<tabla[x->c].n <<"), " << "[" << tabla[x->c].cod <<"]" << endl; //Prueba
  }
}

Ocurrencias cantOcurrencias(HuffmanTable tabla[])
{
  Ocurrencias o = {-1,0};
  for( int i = 0; i<256; i++ )
  {
     if( tabla[i].n>0 )
     {
        o.cantH++;
        o.cantT += tabla[i].n;
     }
  }
  return o;
}

void grabarArchivoComprimido(string fName, HuffmanTable tabla[])
{
  cout<<"Grabando archivo"<<endl;

  FILE* f = fopen((fName+".huf").c_str(),"w+b");

  Ocurrencias o = cantOcurrencias(tabla);
  //cout<<"Hojas: "<<o.cantH+1<<", Cant bytes: "<<o.cantT<<endl; //prueba

  write<unsigned char>(f,o.cantH);       //Escribo cant hojas, CHEQUEAR!!

  for( int j = 0; j<256; j++ )
  {
     if( tabla[j].n>0 )                //Escribo registros x cada hoja
     {
        write<unsigned char>(f,(unsigned char)j);

        string cod = tabla[j].cod;
        unsigned int longCod = length(cod);
        write<unsigned char>(f,longCod);

        for( unsigned int i = 0; i<longCod; i++ )
        {
           write<unsigned char>(f,(unsigned char)cod[i]);
        }
     }
  }

  write<unsigned int>(f,o.cantT);  //Escribo cant bytes

  //Reabro el archivo original para escribir
  FILE* g = fopen(fName.c_str(),"r+b");

  BitWriter b = bitWriter(f);
  int c = read<unsigned char>(g);
  while( !feof(g) )
  {
     string cod = tabla[c].cod;
     for( int j = 0; j<length(cod); j++ )
     {
        int bit = charToInt((unsigned char)cod[j]);
        bitWriterWrite(b,bit);  //Escribo los codigos bit x bit
     }
     c = read<unsigned char>(g);
  }
  bitWriterFlush(b);

  fclose(g);
  fclose(f);

  cout<<"Compresion FINALIZADA"<<endl;
}

void comprimir(string fName)
{
  cout<<"Iniciando compresion:"<<endl;

  // tabla de contadores
  HuffmanTable tabla[256];

  // paso 1
  contarOcurrencias(fName,tabla);

  // paso 2
  List<HuffmanTreeInfo> lista = list<HuffmanTreeInfo>();
  crearLista(lista,tabla);

  // paso 3
  HuffmanTreeInfo* raiz = crearArbol(lista);

  // paso adicional
  cargarCodigosEnTabla(raiz,tabla);

  // grabar
  grabarArchivoComprimido(fName,tabla);
}

HuffmanTreeInfo* crearRama(string cod, HuffmanTreeInfo *raiz, unsigned char c)
{
  if( raiz==NULL )   //crea la raiz
  {
     raiz = new HuffmanTreeInfo();
  }

  HuffmanTreeInfo *aux = raiz;  //puntero auxiliar para recorrer y crear la rama
  for( int i = 0; i<length(cod); i++ )
  {
     if( cod[i]=='1' )
     {
        if( aux->right==NULL )
        {
           aux->right = new HuffmanTreeInfo();
        }
        aux = aux->right;
     }
     else
     {
        if( aux->left==NULL )
        {
           aux->left = new HuffmanTreeInfo();
        }
        aux = aux->left;
     }
  }
  //cout<<"Rama de: ("<<c<<") ["<<cod<<"]"<<endl;
  aux->c = (unsigned int)c;  //el puntero aux queda en la hoja, donde grabo el caracter
  return raiz;
}

HuffmanTreeInfo* recomponerArbol(FILE* g)
{
  cout<<"Recomponiendo arbol"<<endl;

  HuffmanTreeInfo* raiz = NULL;   //raiz del arbol
  unsigned int cantHojas = read<unsigned char>(g)+1;

  for( unsigned int i = 0; i<cantHojas; i++ )    //mientras no lea todos los caracteres
  {
     string cod = "";

     unsigned char c = read<unsigned char>(g);  //leo el caracter
     unsigned int longCod = read<unsigned char>(g); //leo la longitud del codigo del caracter

     for( unsigned int j = 0; j<longCod; j++ )
     {
        cod += read<unsigned char>(g);        //obtengo el codigo
     }

     raiz = crearRama(cod,raiz,c);
  }

  return raiz;
}

void reescribirArchivo(HuffmanTreeInfo* raiz, string fName, FILE* g)
{
  cout<<"Reescribiendo archivo descomprimido"<<endl;

  int longFName = length(fName);
  string archOrig = substring(fName,0,longFName-4);  //nombre del archivo descomprimido
  FILE* f = fopen(archOrig.c_str(),"w+b");           //Genero el archivo descomprimido

  unsigned int longArchivoOriginal = read<unsigned int>(g);

  BitReader br = bitReader(g);
  for( unsigned int i = 0; i<longArchivoOriginal; i++ )  //leo con bitreader
  {
     HuffmanTreeInfo* aux = raiz;

     while( aux->left!=NULL && aux->right!=NULL )
     {
        int bit = bitReaderRead(br);
        if( bit==0 )
        {
           aux = aux->left;
        }
        else
        {
           aux = aux->right;
        }
     }
     write<unsigned char>(f,aux->c);  //finalmente, aux estara en la hoja entonces escribo el caracter
    // cout<<"Caracter reescrito: "<<aux->c<<endl;
  }
  fclose(f);
}

void descomprimir(string fName)
{
  cout<<"Iniciando descompresion:"<<endl;

  FILE* g = fopen(fName.c_str(),"r+b"); //Abro el archivo comprimido

  HuffmanTreeInfo* raiz = recomponerArbol(g);

  reescribirArchivo(raiz,fName,g);

  fclose(g);

  cout<<"Descompresion Finalizada"<<endl;
}

// PROGRAMA PRINCIPAL
int main(int argc, char** argv)
{
  // argumento recibido en linea de comando
  string fName = argv[1];

  if( !endsWith(fName,".huf") )
  {
     comprimir(fName);
  }
  else
  {
     descomprimir(fName);
  }

  return 0;
}

/*Compilar g++ -o nombredelejecutable.exe nombre.cpp*/

#endif