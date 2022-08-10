#ifndef _TLIST_TAD_
#define _TLIST_TAD_

#include <iostream>
#include "../funciones/lists.hpp"

using namespace std;

template<typename T>
struct List
{
   Node<T>* n;
   int curr;
};

template<typename T>
List<T> list()
{
   List<T> l = {NULL,0};
   return l;
}

template<typename T>
T* listAdd(List<T>& lst,T v)
{
   Node<T>* t = add(lst.n,v);
   return &(t->info);
}

template<typename T,typename K>
T listRemove(List<T>& lst,K k, int cmpTK(T,K))
{
   T t = remove<T>(lst.n,k,cmpTK);
   return t;
}

template <typename T>
T listRemoveFirst(List<T>& lst)
{
   return removeFirst<T>(lst.n);
}

template<typename T,typename K>
T* listFind(List<T> lst,K k, int cmpTK(T,K))
{
   Node<T>* t = find(lst.n,k,cmpTK);
   return &(t->info);
}

template<typename T>
T* listOrderedInsert(List<T>& lst,T t,int cmpTT(T,T))
{
   Node<T>* l = orderedInsert(lst.n,t,cmpTT);
   return &(l->info);
}

template<typename T>
void listSort(List<T>& lst,int cmpTT(T,T))
{
   sort(lst.n,cmpTT);
}

template<typename T>
bool listIsEmpty(List<T> lst)
{
   return isEmpty(lst.n);
}

template<typename T>
int listSize(List<T> lst)
{
   Node<T>* aux = lst.n;
   int i=0;

   for (; aux!=NULL; i++)
   {
      aux=aux->sig;
   }

   return i;
}

template<typename T>
void listFree(List<T>& lst)
{
   free(lst.n);
}

template<typename T>
void listReset(List<T>& lst)
{
   lst.curr=0;
}

template<typename T>
bool listHasNext(List<T>& lst)
{
   return lst.curr!=listSize(lst);
}

template<typename T>
T* listNext(List<T>& lst)
{
   Node<T>* aux = lst.n;

   for (int i=0; i<lst.curr; i++)
   {
     aux = aux->sig;
   }

   T* t = &(aux->info);
   lst.curr++;

   return t;
}

#endif
