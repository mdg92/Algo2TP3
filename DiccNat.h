#ifndef DICCNAT_H_
#define	DICCNAT_H_

#include <ostream>
#include "Lista.h"
using namespace std;

namespace aed2
{

template<class K,class S>
class Dicc
{
  public:


    Dicc();
    Dicc(const Dicc<K,S>& otro);
    Dicc<K,S>& operator=(const Dicc<K,S>& otro);
    void Definir(const K& clave, const S& significado);
    void DefinirRapido(const K& clave, const S& significado);
    bool Definido(const K& clave) const;
    S& Significado(const K& clave);
    void Borrar(const K& clave);
    ostream& mostrarDicc(ostream&) const;


  private:

    struct Nodo
      {
        Nodo(const K& c, S& s) : clave(c), significado(s), izquierda(NULL), derecha(NULL) {};

        K clave;
        S significado;
        Nodo* izquierda;
        Nodo* derecha;

     };

    Nodo* primero;

};

template<class K, class S>
std::ostream& operator << (std::ostream &os, const Dicc<K,S>& d)
{
	return d.mostrarDicc(os);
}

template<class K, class S>
bool operator == (const Dicc<K,S>& d1, const Dicc<K,S>& d2);


template<class K, class S>
Dicc<K,S>::Dicc()
{
	this->primero=NULL;
}

template<class K, class S>
Dicc<K,S>::Dicc(const Dicc<K,S>& otro)
{
	if(otro.primero==NULL){

			this->primero=NULL;

	}
}


template<class K, class S>
Dicc<K,S>& Dicc<K,S>::operator = (const Dicc<K,S>& otro)
{
  primero = otro.primero;

  return *this;
}


template<class K, class S>
void Dicc<K,S>::Definir(const K& clave, const S& significado)
{

	if(this->Definido(clave)){
		this->DefinirRapido(clave, significado);
	}

}


template<class K, class S>
void Dicc<K,S>::DefinirRapido(const K& clave, const S& significado)
{
	struct Nodo* n = new Nodo(clave, significado);
		if(this->primero==NULL){
			this->primero=n;
		}
		bool fin = true;
		Nodo* actual = primero;

		while(fin){

			if(this->primero.clave>clave){

				actual=this->primero.izquierda;

				if(actual == NULL){
					this->primero.izquierda=n;
					fin=false;
				}

			} else {

				actual=this->primero.derecha;

				if(actual == NULL){
					this->primero.derecha=n;
					fin=false;
				}
			}

		}
}


template<class K, class S>
bool Dicc<K,S>::Definido(const K& clave) const
{
	bool fin = true;
	bool res = false;
	Nodo* actual = primero;

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


template<class K, class S>
S& Dicc<K,S>::Significado(const K& clave)
{
	bool fin = true;
	S& res;
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
}

template<class K, class S>
void Dicc<K,S>::Borrar(const K& clave)
{

}


template<class K, class S>
ostream& Dicc<K,S>::mostrarDicc(ostream& d) const
{

	if(this->primero==NULL){

			d << "[]" ;

		}else{

			struct Nodo* actual=this->primero;
			d << "[" ;


			d << this->primero.clave;

			if(this->primero.izquierdo != NULL){
				d << this->primero.izquierdo.clave;
			}

			if(this->primero.derecho != NULL){
				d << this->primero.derecho.clave;
			}


			d << "]" << endl;
		}

		return d;
};




}


#endif // DICCNAT_H_
