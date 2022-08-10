#ifndef _TLIST_T_
#define _TLIST_T_

#include <iostream>
#include <stdio.h>

template <typename T>
struct Node
{
   T info;
   Node<T>* sig;
};

template <typename T>
Node<T>* add(Node<T>*& p, T x)
{

   Node<T>* nuevo = new Node<T>();
   nuevo->info = x;
   nuevo->sig = NULL;

   if( p!=NULL )
   {
      Node<T>* aux = p;
      while( aux->sig!=NULL )
      {
         aux = aux->sig;
      }

      aux->sig = nuevo;
   }
   else
   {
      p = nuevo;
   }

   return nuevo;
}

template <typename T>
Node<T>* addFirst(Node<T>*& p,T e)
{
   Node<T>* nuevo = new Node<T>();
   nuevo->info = e;

   if (p==NULL)
   {
      nuevo=add(p,e);
   }
   else
   {
      nuevo->sig=p;
      p=nuevo;
   }

   return nuevo;
}

template <typename T>
T removeFirst(Node<T>*& p)
{
   Node<T>* aux = p;
   T t = aux->info;
   aux = aux->sig;
   delete p;
   p=aux;
   return t;
}

template <typename T, typename K>
T remove(Node<T>*& p, K v, int cmpTK(T,K))
{
   Node<T>* aux = p;
   Node<T>* ant = NULL;
   T t;
   while( aux!=NULL && cmpTK(aux->info,v)!=0 )
   {
      ant = aux;
      aux = aux->sig;
   }
   if( ant==NULL )
   {
      t = removeFirst(p);
   }
   else
   {
      ant->sig = aux->sig;
      t=aux->info;
   }
   delete aux;

   return t;
}

template <typename T, typename K>
Node<T>* find(Node<T>* p, K v, int cmpTK(T,K))
{
   Node<T>* aux = p;
   Node<T>* pos = NULL;

   while( aux!=NULL && pos==NULL )
   {
      if (cmpTK(aux->info,v)==0)
      {
         pos=aux;
      }

      aux = aux->sig;
   }

   return pos;
}

template <typename T>
Node<T>* orderedInsert(Node<T>*& p, T v, int cmpTT(T, T)) //NO se si anda bien siempre
{
   Node<T>* nuevo = new Node<T>();
   nuevo->info = v;
   Node<T>* ant = NULL;
   Node<T>* aux = p;

   while( aux!=NULL && cmpTT(aux->info,v)<1 )
   {
      ant = aux;
      aux = aux->sig;
   }
   if( ant==NULL )
   {
      nuevo->sig = p;
      p = nuevo;
   }
   else
   {
      ant->sig = nuevo;
      if( aux==NULL )
      {
         nuevo->sig = NULL;
      }
      else
      {
         nuevo->sig = aux;
      }
   }

   return nuevo;
}

template <typename T>
Node<T>* searchAndInsert(Node<T>*& p, T e, bool& enc, int cmpTT(T, T))
{
   Node<T>* t = find<T>(p,e,cmpTT);
   t==NULL?enc=false:enc=true;

   if (t==NULL)
   {
      t=orderedInsert<T> (p,e,cmpTT);
   }

   return t;
}

template <typename T>
void sort(Node<T>*& p, int cmpTT(T, T))  //REVISAR
{
   Node<T>* ant = p;
   Node<T>* desp = ant->sig;
   bool interruptor = false;
   bool interruptor2 = false;
   int modificacion = 0;

   for( int i = 0; ant->sig!=NULL&&!interruptor; i++ )
   {
      for( int j = 0; ant->sig!=NULL&&!interruptor2; j++ )
      {
         T x = ant->info;
         T y = desp->info;
         if( cmpTT(x,y)>0 )
         {
            ant->info = y;
            desp->info = x;
            modificacion++;
         }

         if( desp->sig!=NULL )
         {
            ant = ant->sig;
            desp = ant->sig;
         }
         else
         {
            interruptor2 = true;
         }
      }
      ant = p;
      desp = ant->sig;
      interruptor2 = false;
      modificacion==0?interruptor = true:modificacion = 0;
   }
}

template <typename T>
bool isEmpty(Node<T>* p)
{
   return p==NULL;
}

template <typename T>
void free(Node<T>*& p)
{
   Node<T>* aux = p;
   while( !isEmpty<T>(p) )
   {
      p = p->sig;
      delete aux;
      aux=p;
   }
}

template <typename T>
Node<T>* push(Node<T>*& p, T v)
{
   return addFirst<T> (p,v);
}

template <typename T>
T pop(Node<T>*& p)
{
   T t = removeFirst<T> (p);
   return t;
}

template <typename T>
void enqueue(Node<T>*& p, Node<T>*& q, T v)
{
   Node<T>* nuevo = new Node<T>();
   nuevo->info = v;
   nuevo->sig = NULL;

   if( q!=NULL )
   {
      q->sig = nuevo;
   }
   else
   {
      p = nuevo;
   }
   q = nuevo;
}

template <typename T>
Node<T>* enqueue(Node<T>*& q,T e)
{
   Node<T>* nuevo = new Node<T>();
   nuevo->info = e;

   if( q!=NULL )
   {
      nuevo->sig = q->sig;
      q->sig = nuevo;
   }
   else
   {
      nuevo->sig = nuevo;
   }
   q = nuevo;

   return q;
}

template <typename T>
T dequeue(Node<T>*& p, Node<T>*& q)
{
   T t = removeFirst(p);
   if( p==NULL )
   {
      q = NULL;
   }

   return t;
}

template <typename T>
T dequeue(Node<T>*& q)
{
   Node<T>* aux = q->sig;
   q->sig = aux->sig;
   T ret = aux->info;
   if( aux==q )
   {
      q = NULL;
   }
   delete aux;

   return ret;
}

#endif
