
#ifndef _TADBITREADER_
#define _TADBITREADER_

#include "../funciones/strings.hpp"
#include "../funciones/files.hpp"
#include <iostream>

using namespace std;

struct BitReader
{
   unsigned char byte;
   int cantI;
   int cantD;
   FILE* f;
};

BitReader bitReader(FILE* f)
{
   BitReader br ={0,0,7,f};
   return br;
}

int bitReaderRead(BitReader& br)
{
   int izq=br.cantI;
   int der=br.cantD;

   if (izq==0)
   {
     br.byte = read<unsigned char>(br.f);
     //cout << (int)br.byte<<endl;
   }
   unsigned char byte = br.byte;

   byte = byte<<izq;
   byte = byte>>der;
   br.cantI++;

   if( br.cantI==8 )
   {
      br.cantI=0;
   }

   return (int)byte;
}


#endif
