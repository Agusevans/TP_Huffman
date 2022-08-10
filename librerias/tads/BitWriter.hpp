
#ifndef _TADBITWRITER_
#define _TADBITWRITER_

#include "../funciones/strings.hpp"
#include "../funciones/files.hpp"
#include <iostream>

using namespace std;

struct BitWriter
{
   unsigned char byte;
   int cantB;
   bool escrito;
   FILE* f;
};

BitWriter bitWriter(FILE* f)
{
   BitWriter a = {0,0,false,f};
   return a;
}

void bitWriterWrite(BitWriter& bw, int bit)
{
   if (bw.cantB<8)
   {
      bw.escrito=false;
   }

   bw.byte=bw.byte<<1;
   if( bit==1 )
   {
      int i = 1;
      unsigned char m = i;
      bw.byte = (bw.byte|m);
   }

   bw.cantB++;

   if( bw.cantB==8 )
   {
      write<unsigned char>(bw.f,bw.byte);
      bw.cantB = 0;
      bw.byte=0;
      bw.escrito=true;
   }
}

void bitWriterFlush(BitWriter bw)
{
   while( !bw.escrito )
   {
      bitWriterWrite(bw,0);
   }
}

#endif
