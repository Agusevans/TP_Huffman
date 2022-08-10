#ifndef _TSTRINGS_T_
#define _TSTRINGS_T_

#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;


int length(string s)
{

   int i;

   for(i=0;s[i]!='\0';i++)

    {
    }

   return i;
}

// Retorna la cantidad de veces que la cadena s contiene a c
int charCount(string s,char c)
{

   int cont=0;

   for(int i=0;s[i]!='\0';i++)
   {
      if(s[i]==c)
      {
         cont++;
      }
   }
   return cont;
}

// Retorna la subcadena de s comprendida entre d (inclusive) y h (no inclusive)
string substring(string s,int d,int h)
{
  string sb;

  for(;d<h;d++)
  {
     sb=sb+s[d];
  }

   return sb;
}

// Retorna la subcadena de s que va desde d (inclusive) hasta el final
string substring(string s,int d) // ok
{
  string sb;
  int l=length (s);

  for(;d<l;d++)
  {
     sb=sb+s[d];
  }

   return sb;
}

// Retorna la posicion de la primer ocurrencia
// de c dentro s, o -1 si s no contiene a c
int indexOf(string s,char c) // ok
{

   int p=0;

   for(; s[p]!=c and p<=length(s) ;p++)
   {
   }

   if(p>length(s))
   {
      p=-1;
   }


   return p;
}

// Retorna la posicion de la primer ocurrencia de c dentro de s
// considerando la subcadena de s que va desde offset hasta el final.
// Ejemplo: indexOf("ALGORITMOS",'O',7) retorna: 1
int indexOf(string s,char c,int offSet) // ok
{
  string sub = substring (s,offSet);

  int p=0;

     for(; sub[p]!=c and p<=length(sub) ;p++)
     {
     }

     if(p>length(sub))
     {
        p=-1;
     }

     return p;
}

// Retorna la posicion de la ultima ocurrencia de c dentro de s
// o -1 si s no contiene a c
int lastIndexOf(string s,char c)
{
   int p=0;
   int pos=-1;

   for(;p<=length(s);p++)
   {
      if(s[p]==c)
      {
         pos=p;
      }
   }


   return pos;
}

// Retorna la posicion de la n-esima ocurrencia de c dentro de s.
// Por ejemplo: indexOfN("pedro|pablo|juan|rolo",'|',2) retorna 11.
int indexOfN(string s,char c,int n)
{
   int p=0;
   int pos=-1;

   for(;p<=length(s);p++)
   {
      if(s[p]==c and n>0)
      {
         pos=p;
         n--;
      }
   }

   return pos;
}

// Retorna el valor numerico de ch.
// Ejemplo: charToInt('4') retorna: 4.
int charToInt(char ch)
{
   return ch-48;
}

// Retorna el valor char de i.
// Ejemplo: intToChar(4) retorna: '4'.
char intToChar(int i)
{
   char c=i+48;
   return c;
}

// retorna el i-esimo digito de n contando desde la derecha
int getDigit(int n,int i) // ok
{
   if (n<0)
   {
      n=-n;
   }
  for(int parar=0; parar<i; n=n/10, parar++)
   {
   }
    n=n%10;

 return n;
}

int digitCount(int i) // ok
{
   int cont=0;
   if (i<0)
   {
      i=-i;
   }
   for(int n=0; n<i ; i=i/10,cont++)
   {
   }
   return cont;
}

string intToString(int num) // ok
{
   string s;
   int cantD;

   if(num!=0)
    {
    cantD= digitCount(num)-1;
     if (num<0)
     {
      s="-";
     }
    }
   else
   {
   cantD= digitCount(num);
   }

   int cantD2=cantD;

   for(int cont=0; cont<=cantD; cont++)
   {
   int dig= getDigit(num,cantD2);
   cantD2--;
   char c= intToChar(dig);
   s=s+c;
   }

   return s;

}

int stringToInt(string s) // ok
{
  int l=length(s)-1;
  bool negativo = (s[0]=='-');

  if (s[0]=='-')
  {
     s = substring(s,1);
     l = length(s)-1;
  }

  int i=0;
  int mult=1;
  int l2=l;

  for(int cont=0; cont<=l ; cont++, mult=mult*10,l2--)
  {
     char c=s[l2];
     int v= charToInt (c);
     i=i+v*mult;
  }

  if(negativo==true)
  {
     i=-i;
  }

   return i;
}

int stringToInt(string s,int b) // ok
{



   // PROGRAMAR AQUI...
   return 0;
}

string charToString(char c)
{
   string s="";
   s=s+c;

  return s;
}

char stringToChar(string s)
{
   int a = stringToInt(s);
   char x = intToChar(a);

   return x;
}

string stringToString(string s)
{
   return s;
}

string doubleToString(double d)
{

   string s = intToString(d);
   if(d<0)
   {
      d=-d;
   }
   double n = d-(int)d;

     if(n!=0)
   {
      s=s+'.';
      n=n*10;
      int num=n;

    while(num!=0)
    {
       s=s+intToChar(num);
       n=(n-num)*10;
       num=n;
    }

   }


   return s;
}

double stringToDouble(string s)
{
   bool neg= (s[0]=='-');
   if (neg)
    {
     s= substring(s,1);
    }

   double n;
   int x = indexOf(s,'.');

   if(x!=-1)
   {

     string a = substring(s,0,x);
     string b = substring (s,x+1);
     int lb= length (b);
     double y = stringToInt (a);
     double z =stringToInt(b);

      for(int cont=0; cont<lb ; cont++)
      {
         z=z/10;
      }

     n=y+z;

   }
   else
   {
      n= stringToInt(s);
   }

   if(neg)
   {
      n=-n;
   }

   return n;
}

bool isEmpty(string s)
{
  bool a = (length(s)==0);

   return a;
}

bool contains(string s, char c)
{
   bool a;
   if (indexOf(s,c)==-1)
   {
      a=false;
   }
   else
   {
      a=true;
   }

   return a;
}

string replace(string s, char oldChar, char newChar)
{
   string s2="";

   for(int cont=0; cont<length(s); cont++)
   {
     if(s[cont]==oldChar)
     {
      s2=s2+newChar;
     }
     else
     {
      s2=s2+s[cont];
     }
   }

   return s2;
}

string insertAt(string s,int pos,char c)
{
   string s2= substring(s,0,pos);
   string s3= substring(s,pos);

   s= s2+c+s3;

   return s;
}

string removeAt(string s,int pos)
{
   string s1= substring(s,0,pos);
   string s2= substring(s,pos+1);
   s=s1+s2;

   return s;
}

string ltrim(string s)
{
   int cont=0;
   for(; s[cont]==' ' ; cont++)
   {
   }
   s=substring(s,cont);
   return s;
}

string rtrim(string s)
{

   int l = length(s)-1;
   for(; s[l]==' ';l--)
   {
   }
   s=substring(s,0,l+1);

   return s;
}

string trim(string s)
{
  s= ltrim(s);
  s= rtrim(s);

   return s;
}

string replicate(int n,char c)
{
   string s="";
   for(int cont=0; cont<n; cont++)
   {
      s=s+c;
   }

   return s;
}

string spaces(int n)
{
 string s="";
 for(int cont=0; cont<n; cont++)
 {
    s=s+' ';
 }

   return s;
}

string lpad(string s,int n,char c)
{

   int l = length(s);
   int dif= n-l;
   string s2="";

   if(l<n)
   {
     for(int cont=0; cont<l ; cont++)
     {
        while(dif>0)
        {
           s2=s2+c;
           dif--;
        }
        s2=s2+s[cont];
     }
     s=s2;
   }

   return s;
}

string rpad(string s,int n,char c)
{

   if(length(s)<n)
   {
      for(int cont=0; length(s)!=10; cont++)
      {
         s= s+c;
      }
   }

   return s;
}

string cpad(string s,int n,char c)
{
   int a,b;
   string s2="";
   n=n-length(s);

   if(n%2==0)
   {
     a=n/2;
     b=a;
   }
   else
   {
      a=n/2;
      b=a+1;
   }

   for(;a>0;a--)
   {
      s=s+c;
   }
   for(;b>0;b--)
   {
      s2=s2+c;
   }
   s=s2+s;

   return s;
}

bool isDigit(char c)
{
   bool a = (charToInt(c)>=0 and charToInt(c)<=9);

   return a;
}

bool isLetter(char c)
{
  bool a= ((c>64 and c<91)or(c>96 and c<123));

   return a;
}

bool isUpperCase(char c)
{
   bool a = (c>64 and c<91);

   return a;
}

bool isLowerCase(char c)
{
  bool a = (c>96 and c<123);

  return a;
}

char toUpperCase(char c)
{

   if(isLetter(c) and isLowerCase(c))
   {
      c=c-32;
   }


   return c;
}

char toLowerCase(char c)
{

   if(isLetter(c) && isUpperCase(c))
   {
      c=c+32;
   }

   return c;
}

// Retorna la subcadena de s comprendida entre d (inclusive) hasta el final
//string substring(string s,int d)

bool endsWith(string cadena, string terminacion)
{
   int index = length(cadena) - length(terminacion);
   string subcadena = substring(cadena, index);

   return subcadena == terminacion;
}

#endif
