#ifndef REG_H_
#define	REG_H_

#include <iostream>
#include "DiccLex.h"
#include "Dato.h"
#include "Tipos.h"


namespace aed2
{


class Registro
{
  public:
	Registro();
  	//DiccLex();
  	//~DiccLex();
  	//DiccLex(const Registro&);
  	void Definir(NombreCampo, Dato);
  	bool Definido(NombreCampo);
  	bool Definido(NombreCampo) const;
  	void Borrar(NombreCampo);
  	Dato& Significado(NombreCampo);
  	Conj<NombreCampo> Campos();
  	NombreCampo Maximo();
  	NombreCampo Minimo();
  	Dato& Significado(NombreCampo) const;
  	Conj<NombreCampo> Campos() const;
  	NombreCampo Maximo() const;
  	NombreCampo Minimo() const;
  	bool BorrarPreg(Registro);
  	bool BorrarPreg(Registro) const;
  	bool EnTodos(NombreCampo, Conj<Registro>);
  	bool CoincideAlguno(Conj<NombreCampo>,  Registro);
  	bool CoincidenTodos(Conj<NombreCampo>,  Registro);
  	Registro UnirRegistros(NombreCampo,  Registro);
  	Registro CombinarTodos(NombreCampo, Conj<Registro>);

  private:
  	DiccLex<Dato> base;


};

Registro::Registro(){
	this->base=DiccLex<Dato>();
};


void Registro::Definir(NombreCampo s, Dato d){
	this->base.Definir(s,d);
};


bool Registro::Definido(NombreCampo s){
	return this->base.Definido(s);
};


bool Registro::Definido(NombreCampo s) const{
	return this->base.Definido(s);
};




void Registro::Borrar(NombreCampo s){
	this->base.Borrar(s);
};


Dato& Registro::Significado(NombreCampo s){
	return this->base.Significado(s);

};


Conj<NombreCampo> Registro::Campos(){
	return this->base.DiccClaves();
};


NombreCampo Registro::Maximo(){
	return this->base.Maximo();
};


NombreCampo Registro::Minimo(){
	return this->base.Minimo();
};

bool Registro::BorrarPreg( Registro r2){
	Conj<NombreCampo>::Iterador it =(this->Campos()).CrearIt();
	bool res=true;
	while(res && it.HaySiguiente()) res=(this->Significado(it.Siguiente())==r2.Significado(it.Siguiente())), it.Avanzar();
	return res;
};
bool Registro::CoincideAlguno(Conj<NombreCampo> cc,  Registro r2){
	Conj<NombreCampo>::Iterador it =cc.CrearIt();
	bool res=false;
	while(!res && it.HaySiguiente()) res=(this->Significado(it.Siguiente())==r2.Significado(it.Siguiente())), it.Avanzar();
	return res;
};
bool Registro::CoincidenTodos(Conj<NombreCampo> cc,  Registro r2){
	Conj<NombreCampo>::Iterador it =cc.CrearIt();
	bool res=true;
	while(res && it.HaySiguiente()) res=(this->Significado(it.Siguiente())==r2.Significado(it.Siguiente())), it.Avanzar();
	return res;
};
bool Registro::EnTodos(NombreCampo c, Conj<Registro> cr){
	Conj<Registro>::Iterador it =cr.CrearIt();
	bool res=true;
	while(res && it.HaySiguiente()){
		Registro r=it.Siguiente();
		res = r.Definido(c);
		it.Avanzar();	
	} 
	return res;
};



Registro Registro::UnirRegistros(NombreCampo c, Registro r2){
	Conj<NombreCampo>::Iterador itAux =r2.Campos().CrearIt();
	Registro res;
	while(itAux.HaySiguiente()) res.Definir(itAux.Siguiente(), r2.Significado(itAux.Siguiente())), itAux.Avanzar();
	Conj<NombreCampo>::Iterador it =this->Campos().CrearIt();
	while(it.HaySiguiente()) res.Definir(it.Siguiente(), this->Significado(it.Siguiente())), it.Avanzar();
	return res;
};
Registro Registro::CombinarTodos(NombreCampo c, Conj<Registro> cr){
	Conj<Registro>::Iterador it =cr.CrearIt();
	bool f=true;
	Registro* res;
	while(f && it.HaySiguiente()){
		Registro r=it.Siguiente();
		if (this->Significado(c)==r.Significado(c)){
			Registro rder=this->UnirRegistros(c, it.Siguiente());
			res= &(rder);
			f=false;
		}
		it.Avanzar();
	}
	return *res;
};
};






#endif // DICCLEX_H_
