#ifndef REG_H_
#define	REG_H_

#include <iostream>
#include "DiccLex.h"


namespace aed2
{
class Registro
{
  public:
  	//DiccLex();
  	//~DiccLex();
  	//DiccLex(const Registro&);
  	void Definir(Campo, S&);
  	bool Definido(Campo);
  	void Borrar(Campo);
  	S& Significado(Campo);
  	const Conj<Campo>& DiccClaves();
  	Campo Maximo();
  	Campo Minimo();

  private:
  	DiccLex<Dato> base;


};


void Registro::Definir(Campo s, S& d){
	this->base.Definir(s,d);
};


template<typename S>
bool Registro::Definido(Campo s){
	this->base.Definido(s);
};


template<typename S>
void Registro::Borrar(Campo s){
	this->base.Borrar(s);
};


template<typename S>
S& Registro::Significado(Campo s){
	return this->base.Significado(s);

};


template<typename S>
const Conj<Campo>& Registro::DiccClaves(){
	return this->base.DiccClaves;
};


template<typename S>
Campo Registro::Maximo(){
	return this->base.Maximo();
};


template<typename S>
Campo Registro::Minimo(){
	return this->base.Minimo();
};






};


#endif // DICCLEX_H_