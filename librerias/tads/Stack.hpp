#ifndef _TSTACK_TAD_
#define _TSTACK_TAD_

#include <iostream>
#include "../funciones/lists.hpp"

using namespace std;

template<typename T>
struct Stack
{
   Node<T>* s;
};

template<typename T>
Stack<T> stack()
{
   Stack<T> st = {NULL};
   return st;
}

template<typename T>
T* stackPush(Stack<T>& st,T v)
{
   Node<T>* n = push(st.s,v);
   return &(n->info);
}

template<typename T>
T stackPop(Stack<T>& st)
{
   return pop(st.s);
}

template<typename T>
bool stackIsEmpty(Stack<T> st)
{
   return st.s==NULL;
}

template<typename T>
int stackSize(Stack<T> s)
{
   int i = 0;
   Node<T>* aux = s.s;
   for (; aux!=NULL ; i++)
   {
      aux=aux->sig;
   }

   return i;
}

#endif
