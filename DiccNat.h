#ifndef DICCNAT_H_
#define	DICCNAT_H_

#include <iostream>
#include "Tipos.h"
#include "aed2/Lista.h"


namespace aed2
{

template<typename S>
class DiccNat
{
  public:


	DiccNat();
	//DiccNat(const DiccNat& otro);
	//DiccNat& operator=(const DiccNat& otro);
    void Definir(const Nat& clave, const S& significado);
    //void DefinirRapido(const Nat& clave, const S& significado);
    bool Definido(const Nat& clave) const;
    S Significado(const Nat& clave);
    void Borrar(const Nat& clave);
    Lista<Nat>& Claves();
    std::ostream& mostrarDicc(std::ostream&) const;


  private:

    struct Nodo
      {

        Nat clave;
        S significado;
        Nodo* izquierda;
        Nodo* derecha;
        Lista<Nat>::Iterador puntero;
        Nodo(const Nat& c,const S& s,const Lista<Nat>::Iterador p) :
        	clave(c), significado(s), izquierda(NULL), derecha(NULL), puntero(p) {};

     };



    Nodo* primero;
    Lista<Nat> claves;


};


template<typename S>
std::ostream& operator << (std::ostream &os, const DiccNat<S>& d)
{
	return d.mostrarDicc(os);
};


template<typename S>
DiccNat<S>::DiccNat()
{
	this->primero=NULL;
	this->claves=Lista<Nat>::Lista();
}



/*
template<typename S>
bool operator ==(const aed2::DiccNat<S>& d1, const aed2::DiccNat<S>& d2);

template<typename S>
DiccNat<S>::DiccNat(const DiccNat<S>& otro)
{
	if(otro.primero==NULL){

			this->primero=NULL;

	}
};


template<typename S>
DiccNat<S>& DiccNat<S>::operator = (const DiccNat<S>& otro)
{
  primero = otro.primero;

  return *this;
}
*/

template<typename S>
void DiccNat<S>::Definir(const Nat& clave, const S& significado)
{
		Lista<Nat>::Iterador puntero;
		puntero= claves.Lista<Nat>::AgregarAtras(clave);
		Nodo* n = new Nodo(clave, significado, puntero);

		if(this->primero==NULL){
			this->primero=n;
		}else{
			bool fin = true;
			Nodo* actual = this->primero;

			while(fin){

				if(actual->clave>clave){

					if(actual->izquierda == NULL){
						actual->izquierda=n;
						fin=false;
					}
					actual=actual->izquierda;
				} else {

					if(actual->derecha == NULL){
						actual->derecha=n;
						fin=false;
					}
					actual=actual->derecha;
				}

			}
		}
}


template<typename S>
bool DiccNat<S>::Definido(const Nat& clave) const
{
	bool fin = true;
	bool res = false;
	Nodo* actual = this->primero;

	while(fin){

		if(actual==NULL){

			fin=false;

		} else {

			if(actual->clave==clave) {
				res = true;
				fin = false;
			}

			if(actual->clave>clave) {
				actual=actual->izquierda;
			}else{
				actual=actual->derecha;
			}

		}

	}

	return res;
}


template<typename S>
S DiccNat<S>::Significado(const Nat& clave)
{
	bool fin = true;
	S res;
	Nodo* actual = primero;

	while(fin){

			if(actual->clave==clave) {
				res = actual->significado;
				fin = false;
			}

			if(actual->clave>clave) {
				actual=actual->izquierda;
			}else{
				actual=actual->derecha;
			}

		}

	return res;
};

template<typename S>
void DiccNat<S>::Borrar(const Nat& clave)
{

	Nodo* padre = NULL; /* (1) */
	Nodo* actual;
	Nodo* nodo;
	Nat auxC;
	S auxS;
	Lista<Nat>::Iterador auxP;

   actual = this->primero;

   while(actual!=NULL) { /* Búsqueda (2) else implícito */
	  if(clave == actual->clave) { /* (3) */
		 if(actual->izquierda==NULL && actual->derecha==NULL) { /* (3-a) */
			   if(padre){
				   if(padre->derecha == actual) padre->derecha = NULL;  /* (3-a-ii) */
				   else if(padre->izquierda == actual) padre->izquierda = NULL; /* (3-a-iii) */
			   }
			   if(padre==NULL && actual->clave==this->primero->clave){
				   this->primero=NULL;
			   }
		   Lista<Nat>::Iterador it=actual->puntero;
		   it.Lista<Nat>::Iterador::EliminarSiguiente();
		   delete actual; /* (3-a-iv) */
		   actual = NULL;

		   return;
	 }
		 else { /* (3-b) */
			/* Buscar nodo */
			padre = actual; /* (3-b-i) */
			if(actual->derecha) {
			   nodo = actual->derecha;
			   while(nodo->izquierda) {
				  padre = nodo;
				  nodo = nodo->izquierda;
			   }
			}
			else {
			   nodo = actual->izquierda;
			   while(nodo->derecha) {
				  padre = nodo;
				  nodo = nodo->derecha;
			   }
			}
			/* Intercambio */
			auxC = actual->clave; /* (3-b-ii) */
			actual->clave = nodo->clave;
			nodo->clave = auxC;

			auxS = actual->significado; /* (3-b-ii) */
			actual->significado = nodo->significado;
			nodo->significado = auxS;

			auxP = actual->puntero; /* (3-b-ii) */
			actual->puntero = nodo->puntero;
			nodo->puntero = auxP;

			actual = nodo;
		 }
	  }
	  else {
		 padre = actual;
		 if(clave > actual->clave) actual = actual->derecha; /* (4) */
		 else if(clave < actual->clave) actual = actual->izquierda; /* (5) */
	  }
   }


};

template<typename S>
Lista<Nat>& DiccNat<S>::Claves()
{
	return this->claves;
};


template<typename S>
std::ostream& DiccNat<S>::mostrarDicc(std::ostream& d) const
{

	if(this->primero==NULL){

			d << "[]" ;

		}else{

			struct Nodo* actual=this->primero;
			d << "[" ;

			d << actual->clave;
			d << ", ";

			if(actual->izquierda != NULL){
				d << "Izq: ";
				d << actual->izquierda->clave;
				d << ", ";
			}


			if(actual->derecha != NULL){
				d << "Der: ";
				d << actual->derecha->clave;
			}


			d << "]" << std::endl;


			if(this->primero->izquierda != NULL){
				actual=this->primero->izquierda;
				d << "[" ;

				d << actual->clave;
				d << ", ";

				if(actual->izquierda != NULL){
					d << "Izq: ";
					d << actual->izquierda->clave;
					d << ", ";
				}


				if(actual->derecha != NULL){
					d << "Der: ";
					d << actual->derecha->clave;
				}


			d << "]" << std::endl;
			}

			if(this->primero->derecha != NULL){
				actual=this->primero->derecha;
				d << "[" ;

				d << actual->clave;
				d << ", ";

				if(actual->izquierda != NULL){
					d << "Izq: ";
					d << actual->izquierda->clave;
					d << ", ";
				}


				if(actual->derecha != NULL){
					d << "Der: ";
					d << actual->derecha->clave;
				}


				d << "]" << std::endl;
			}
		}

		return d;
};





};


#endif // DICCNAT_H_
