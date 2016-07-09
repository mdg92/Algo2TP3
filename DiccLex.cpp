#include "DiccLex.h"
#include <iostream>

using namespace aed2;

// int main(){
// 	DiccLex<Nat> p;
// 	Nat i=2;
// 	p.Definir("ahora",i);
// 	std::cout<<p.Definido("ahora")<<"\n";
// 	p.Definir("ahora1",i);
// 	p.Definir("ahra",i);
// 	p.Definir("aora",i);
// 	p.Definir("hora",i);
// 	p.Definir("sahora",i);
// 	p.Definir("afhora1",i);
// 	p.Definir("ahrsa",i);
// 	p.Definir("aorag",i);
// 	p.Definir("hogra",i);
// 	p.Definir("ahoraew",i);
// 	p.Definir("ahorewa1",i);
// 	p.Definir("ahqra",i);
// 	p.Definir("aoeqra",i);
// 	p.Definir("horqweqwa",i);
// 	p.Definir("ahwqora",i);
// 	p.Definir("ahoqra1",i);
// 	p.Definir("ahrewqqa",i);
// 	p.Definir("aoweqra",i);
// 	p.Definir("hoewqra",i);
// 	p.Definir("ahoreea",i);
// 	p.Definir("ahqweora1",i);
// 	i++;
// 	p.Definir("ahra",i);
// 	p.Definir("aoeqwra",i);
// 	p.Definir("horasda",i);
// 	p.Definir("ahorsada",i);
// 	p.Definir("ahosara1",i);
// 	p.Definir("ahrasda",i);
// 	p.Definir("aorsdaa",i);
// 	p.Definir("zoradsa",i);
// 	p.Definir("Horadsa",i);
// 	std::cout<<p.Minimo()<<"\n";
// 	std::cout<<p.Maximo()<<"\n";
// 	std::cout<<p.DiccClaves()<<"\n";
// 	p.Borrar("ahra");
// 	std::cout<<p.DiccClaves()<<"\n";
// 	std::cout<<p.Significado(p.Minimo())<<"\n";
// 	return 3;


// };

template<typename S>
DiccLex<S>::DiccLex(){
	this->_raiz=NULL;
	this->_claves=Conj<String>();
};

template<typename S>
void DiccLex<S>::borrec (Nodo* n){
	int i=0;
	while(i<256) {
		if(n->continuaciones[i]!=NULL) borrec(n->continuaciones[i]);
		i++;
	}
	delete n;
};

template<typename S>
DiccLex<S>::~DiccLex(){
	Nodo* root=this->_raiz;
	if (root!=NULL) borrec(root);
};

template<typename S>
void DiccLex<S>::Definir(String s, S d){
	Nodo** aux=&this->_raiz;
	int i = 0;
	int sl = s.length();
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
	if((*aux)->esSig!=true) (*aux)->claveEnConj=(this->_claves).AgregarRapido(s);
	(*aux)->esSig=true;
	(*aux)->dato=&d;
};


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
};

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
	while(i<sl){
		l.AgregarAdelante(aux);
		aux=aux->continuaciones[(unsigned char)(s[i])];
		i++;
	}
	aux->esSig=false;
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

};
template<typename S>
S& DiccLex<S>::Significado(String s) const{
	Nodo* aux=this->_raiz;
	int i =0;
	int sl = s.length();
	while (i<sl){
		aux=aux->continuaciones[(unsigned char)(s[i])];
		i++;
	}
	return *(aux->dato);

};


template<typename S>
Conj<String> DiccLex<S>::DiccClaves(){
	return this->_claves;
};

template<typename S>
Conj<String> DiccLex<S>::DiccClaves() const{
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


