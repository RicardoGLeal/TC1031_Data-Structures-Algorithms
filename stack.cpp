#include <iostream>
using namespace std;

struct Nodo {
    int dato;
    Nodo *sig;
}*pila, *aux, *tope;

class Pila {
    public:
        int toFind;
        void push(int);
        void pop();
        bool vacia();
        void imprimir();
    
};

void Pila::push(int value) {
  if(vacia()) {
    pila = new Nodo;
    pila->dato = value;
    pila->sig = NULL;
    tope = pila;
  } else {
      aux = new Nodo;
      aux->dato=value;
      aux->sig=NULL;
      tope->sig=aux;
      tope=aux;
  }
}

void Pila::pop() {
  if (!vacia()) {
    aux = pila; 
    if(aux->sig==NULL) {
      pila = NULL;
    }
    else {
      while(aux->sig!=tope) {
        aux = aux->sig;
      }
      aux->sig = NULL;
      delete tope;
      tope = aux;
    }
    cout<<"Elemento eliminado"<<endl;
  }
}

bool Pila::vacia() {
    return (pila == NULL);
}

void Pila::imprimir() {
  if(vacia()) {
    cout<<"La pila esta vacia"<<endl;
  }
  else {
    cout<<"Pila: "<<endl;
    aux = pila;
    do {
      cout<<aux->dato<<" ";
      aux = aux->sig;
    }
    while(aux!=NULL);
    cout<<endl;
  }
}

int main() {
  Pila pila;
//   pila.inicializar();
  pila.push(5);
  pila.push(1);
  pila.push(2);
  pila.push(3);
  pila.imprimir();
  pila.pop();
  pila.pop();
  pila.imprimir();
  pila.push(10);
  pila.push(12);
  pila.imprimir();
//   mi internet xd
}