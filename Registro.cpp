#include "registro.h"
#include <iostream>

using namespace aed2;

bool Registro::operator==(const Registro otro)const{
	bool respuesta=this->Campos()==otro.Campos();
	if(respuesta){
		Conj<NombreCampo>::const_Iterador it=this->Campos().CrearIt();
		while(respuesta and it.HaySiguiente()){
			respuesta=this->Significado(it.Siguiente())==otro.Significado(it.Siguiente());
			it.Avanzar();
		}
	}
	return respuesta;
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


Dato& Registro::Significado(NombreCampo s) const{
	return this->base.Significado(s);

};

const Conj<NombreCampo>& Registro::Campos() const{
	return this->base.DiccClaves();
};


NombreCampo Registro::Maximo(){
	return this->base.Maximo();
};


NombreCampo Registro::Minimo(){
	return this->base.Minimo();
};

NombreCampo Registro::Maximo() const{
	return this->base.Maximo();
};


NombreCampo Registro::Minimo() const{
	return this->base.Minimo();
};

bool Registro::BorrarPreg( Registro r2){
	Conj<NombreCampo>::const_Iterador it =(this->Campos()).CrearIt();
	bool res=true;
	while(res && it.HaySiguiente()) res=(this->Significado(it.Siguiente())==r2.Significado(it.Siguiente())), it.Avanzar();
	return res;
};

bool Registro::CoincideAlguno(const Conj<NombreCampo>& cc, const Registro& r2) const{
	Conj<NombreCampo>::const_Iterador it =cc.CrearIt();
	bool res=false;
	while(!res && it.HaySiguiente()) res=(this->Significado(it.Siguiente())==r2.Significado(it.Siguiente())), it.Avanzar();
	return res;
};

bool Registro::CoincidenTodos(const Conj<NombreCampo>& cc,  const Registro& r2) const{
    Conj<NombreCampo>::const_Iterador it =cc.CrearIt();
	bool res=true;
	while(res && it.HaySiguiente()){
		res=this->Significado(it.Siguiente())==r2.Significado(it.Siguiente());
		it.Avanzar();
	}
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
	Conj<NombreCampo>::const_Iterador itAux =r2.Campos().CrearIt();
	Registro res;
	while(itAux.HaySiguiente()) res.Definir(itAux.Siguiente(), r2.Significado(itAux.Siguiente())), itAux.Avanzar();
	Conj<NombreCampo>::const_Iterador it =this->Campos().CrearIt();
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

