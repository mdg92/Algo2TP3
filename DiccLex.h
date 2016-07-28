#ifndef DICCLEX_H_
#define	DICCLEX_H_

#include <iostream>
#include "Tipos.h"
#include "aed2/Lista.h"
#include "aed2/Conj.h"


namespace aed2
{

template<typename S>
class DiccLex
{
  public:
    DiccLex();
    DiccLex(const DiccLex &);
  	~DiccLex();
  	//DiccLex(const DiccLex<S>&);
  	void Definir(String, const S&);
  //	bool Definido(String);
  	bool Definido(String) const;
  	void Borrar(String);
  	//S& Significado(String);
  	S& Significado(String) const;
  	//Conj<String> DiccClaves();
  	const Conj<String>& DiccClaves() const;
  	String Maximo();
  	String Maximo()const;
  	String Minimo();
  	String Minimo()const;

/*
  	class Iterador{
  	}
*/
  private:

  	struct Nodo{
        Nodo() : dato(NULL), esSig(false) { for(int i=0; i<256;++i) continuaciones[i]=NULL;}
  		S* dato;
  		bool esSig;
  		Conj<String>::Iterador claveEnConj;
  		Nodo* continuaciones[256];
  	};
  	Nodo* _raiz;
  	Conj<String> _claves;
    void borrec (Nodo*);


};
	
template<typename S>
DiccLex<S>::DiccLex(){
	this->_raiz=NULL;
	this->_claves=Conj<String>();
};

template<typename S>
DiccLex<S>::DiccLex(const DiccLex &otro){
    this->_raiz=NULL;
    Conj<String>::const_Iterador itcl=otro._claves.CrearIt();
    while(itcl.HaySiguiente()){
        this->Definir(itcl.Siguiente(), otro.Significado(itcl.Siguiente()));
        itcl.Avanzar();
    }
};


template<typename S>
void DiccLex<S>::borrec (Nodo* n){
	int i=0;
	while(i<256) {
		if(n->continuaciones[i]!=NULL) borrec(n->continuaciones[i]);
		i++;
	}
	if (n->dato!=NULL) delete n->dato;
	delete n;
};
template<typename S>
DiccLex<S>::~DiccLex(){
    //Nodo* root=this->_raiz;
    //if (root!=NULL) borrec(root);

};


template<typename S>
void DiccLex<S>::Definir(const String s, const S& d){

	Nodo** aux=&this->_raiz;
	int i = 0;
    int sl = s.length() ;
	while(i<(sl)){
		if(*aux==NULL){
			(*aux)= new Nodo;
			(*aux)->esSig=false;
			int j = 0;
			while(j<256){
				((*aux)->continuaciones[j])=NULL;
				j++;
			}
		}
		(aux)=&((*aux)->continuaciones[(unsigned char)(s[i])]);
		i++;
	}
	if((*aux)==NULL){
		(*aux)= new Nodo;
		(*aux)->esSig=false;
		int j = 0;
		while(j<256){
			(*aux)->continuaciones[j]=NULL;
			j++;
		}
	}
    if((*aux)->esSig!=true){
        (*aux)->claveEnConj=(this->_claves).AgregarRapido(s);

    }else{
        delete (*aux)->dato;
    }
    (*aux)->esSig=true;
	(*aux)->dato= new S(d);
	//std::cout << s << " Definido" << std::endl;

};

/*
template<typename S>
bool DiccLex<S>::Definido(String s){
	Nodo* aux=this->_raiz;
	bool res=false;
	int i = 0;
	int sl = s.length();
	while(i<sl && aux!=NULL){
		aux=(aux->continuaciones[(unsigned char)(s[i])]);
		i++;
	}
	if(aux!=NULL) res=aux->esSig;
	return res;
};*/
template<typename S>
bool DiccLex<S>::Definido(String s) const{
	Nodo* aux=this->_raiz;
	bool res=false;
	int i = 0;
	int sl = s.length();
	while(i<sl && aux!=NULL){
		aux=(aux->continuaciones[(unsigned char)(s[i])]);
		i++;
	}
	if(aux!=NULL) res=aux->esSig;
	return res;
};


template<typename S>
void DiccLex<S>::Borrar(String s){
	Nodo* aux = this->_raiz;
	int i =0;
	Lista<Nodo*> l;
	int sl = s.length();
    while(i<(sl +1)){
		l.AgregarAdelante(aux);
		aux=aux->continuaciones[(unsigned char)(s[i])];
		i++;
	}
	aux->esSig=false;
	delete aux->dato;
	aux->dato=NULL;
	i--;
	int j=0;
	while(aux->continuaciones[j]==NULL&&j<256) j++;
	typename Lista<Nodo*>::Iterador itL=l.CrearIt();
	if(j<256) while(! l.EsVacia()) itL.EliminarSiguiente();
	while(itL.HaySiguiente()){
		j=0;
		itL.Siguiente()->continuaciones[(unsigned char) (s[i])]=NULL;
		while(itL.Siguiente()->continuaciones[j]==NULL&&j<256) j++;
		if(j<256) {
			Lista<Nodo*> l1, l=l1;
			//itL=(l.CrearIt());
		}else {
			itL.EliminarSiguiente();
			i--;
		}
	}
};

/*
template<typename S>
S& DiccLex<S>::Significado(String s){
	Nodo* aux=this->_raiz;
	int i =0;
	int sl = s.length();
	while (i<sl){
		aux=aux->continuaciones[(unsigned char)(s[i])];
		i++;
	}
	return *(aux->dato);
};*/
template<typename S>
S& DiccLex<S>::Significado(String s) const{
	Nodo* aux=this->_raiz;
	int i =0;
	int sl = s.length();
    while (i<(sl)){
		aux=aux->continuaciones[(unsigned char)(s[i])];
		i++;
    }
	return *(aux->dato);

};


/*template<typename S>
Conj<String> DiccLex<S>::DiccClaves(){
	return this->_claves;
};*/

template<typename S>
const Conj<String>& DiccLex<S>::DiccClaves() const{
	return this->_claves;
};


template<typename S>
String DiccLex<S>::Maximo(){
	Nodo* aux=this->_raiz;
	String res;
	res.clear();
	int i=255;
	while(i>-1){
		if (aux->continuaciones[i]==NULL){
			i--;
		}
		else {
			res.push_back((char) i);
			aux=aux->continuaciones[i];
			i=255;
		}

	}
	return res;
};


template<typename S>
String DiccLex<S>::Minimo(){
	Nodo* aux=this->_raiz;
	String res;
	res.clear();
	int i=0;
	while(i<256){
		if (aux->continuaciones[i]==NULL){
			i++;
		}
		else {
			res.push_back((char) i);
			aux=aux->continuaciones[i];
			i=0;
		}

	}
	return res;
};

template<typename S>
String DiccLex<S>::Maximo() const{
	Nodo* aux=this->_raiz;
	String res;
	res.clear();
	int i=255;
	while(i>-1){
		if (aux->continuaciones[i]==NULL){
			i--;
		}
		else {
			res.push_back((char) i);
			aux=aux->continuaciones[i];
			i=255;
		}

	}
	return res;
};


template<typename S>
String DiccLex<S>::Minimo() const{
	Nodo* aux=this->_raiz;
	String res;
	res.clear();
	int i=0;
	while(i<256){
		if (aux->continuaciones[i]==NULL){
			i++;
		}
		else {
			res.push_back((char) i);
			aux=aux->continuaciones[i];
			i=0;
		}

	}
	return res;
};





};


#endif // DICCLEX_H_
