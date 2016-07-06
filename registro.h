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
  	const Conj<Campo>& Campos();
  	Campo Maximo();
  	Campo Minimo();
  	bool BorrarPreg(const Registro&);
  	bool CoincideAlguno(Conj<Campo>, const Registro&);
  	bool CoincidenTodos(Conj<Campo>, const Registro&);
  	Registro UnirRegistros(Campo, const Registro&);
  	Registro CombinarTodos(Campo, Conj<Registro>);

  private:
  	DiccLex<Dato> base;


};

bool EnTodos(Campo, Conj<Registro>);

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
const Conj<Campo>& Registro::Campos(){
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

bool Registro::BorrarPreg(const Registro& otro){
	return this->CoincidenTodos(this->Campos, otro);
};
bool Registro::CoincideAlguno(Conj<Campo> cc, const Registro& r2){
	Conj<Campo>::Iterador it =cc.CrearIt();
	bool res=false;
	while(!res && it.HaySiguiente()) res=(this->Significado(it.Siguiente())==r2.Significado(i.Siguiente())), it.Avanzar();
	return res;
};
bool Registro::CoincidenTodos(Conj<Campo> cc, const Registro& r2){
	Conj<Campo>::Iterador it =cc.CrearIt();
	bool res=true;
	while(res && it.HaySiguiente()) res=(this->Significado(it.Siguiente())==r2.Significado(i.Siguiente())), it.Avanzar();
	return res;
};
bool EnTodos(Campo c, Conj<Registro> cr){
	Conj<Campo>::Iterador it =cc.CrearIt();
	bool res=true;
	while(res && it.HaySiguiente()) res= c.Definido(it.Siguiente()),it.Avanzar();
	return res;
};
Registro Registro::UnirRegistros(Campo c, const Registro& r2){
	Conj<Campo>::Iterador itAux =r2.Campos().CrearIt();
	Registro res;
	while(itAux.HaySiguiente()) res.Definir(itAux.Siguiente(), r2.Significado(itAux.Siguiente())), itAux.Avanzar();
	Conj<Campo>::Iterador it =this->Campos().CrearIt();
	while(it.HaySiguiente()) res.Definir(it.Siguiente(), this->Significado(it.Siguiente())), it.Avanzar();
	return res;
};
Registro Registro::CombinarTodos(Campo c, Conj<Registro> cr){
	Conj<Campo>::Iterador it =cr.CrearIt();
	bool f=true;
	Registro* res;
	while(f && it.HaySiguiente()){
		if (this->Significado(c)==(it.Siguiente()).Significado(c))
			res= &(this->UnirRegistros(c, it.Siguiente()));
			f=false
		}
		it.Avanzar;
	}
	return *res;
};




};


#endif // DICCLEX_H_