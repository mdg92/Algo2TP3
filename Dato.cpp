#include "Dato.h"
#include <cassert>


using namespace aed2;

Dato::Dato(const Dato& a){
	this->tipo_=a.tipo();
	if(a.tipo()){
		this->valorNat_=a.valorNat();
	}else{
		this->valorString_=a.valorString();
	}
};


Dato::Dato(const String y):tipo_(false),valorString_(y)
{};

Dato::Dato(const Nat x):tipo_(true), valorNat_(x)
{};

Dato::~Dato(){};

const Tipo Dato::tipo()const{
	return this->tipo_;
};


Nat Dato::valorNat()const{
	return this->valorNat_;
};

String Dato::valorString()const{
	return this->valorString_;
};

bool Dato::mismoTipo(const Dato& b)const{
	if(this->tipo()==b.tipo()){
		if(this->tipo()){
			return (this->valorNat()==b.valorNat());
		}else{
			return (this->valorString()==b.valorString());
		}
	}else{
		return false;
	}
};

bool Dato::EsString()const{
	return (this->tipo()==false);
};


bool Dato::EsNat()const{
	return (this->tipo()==true);
};

bool Dato::operator<=(const Dato& b)const{
	assert(this->tipo_==b.tipo_);
	if(this->tipo_){
		return this->valorNat_ <=b.valorNat_;
	}else{
		return this->valorString_ <=b.valorString_;
	}
};

//const Dato Dato::min(Conj<Dato& >& cjd)const{
//	assert(cjd.Cardinal()!=0);
//	Conj<Dato& >::Iterador it=cjd.CrearIt();
//	Dato menor=it.Siguiente();
//	while(it.HaySiguiente()){
//		if(it.Siguiente()<= menor){
//			menor=it.Siguiente();
//		}
//		it.Avanzar();
//	}
//	return menor;
//};
//
//const Dato Dato::max(Conj<Dato& >& cjd)const{
//	assert(cjd.Cardinal()!=0);
//	Conj<Dato& >::Iterador it=cjd.CrearIt();
//	Dato mayor=it.Siguiente();
//	while(it.HaySiguiente()){
//		if(mayor<=it.Siguiente()){
//			mayor=it.Siguiente();
//		}
//		it.Avanzar();
//	}
//	return mayor;
//};

bool Dato::operator ==(const Dato& b)const{
	if(this->mismoTipo(b)){
		if(this->tipo()){
			return this->valorNat()==b.valorNat();
		}else{
			return this->valorString()==b.valorString();
		}
	}else{
		return false;
	}
};




//int main(){
//	aed2::Dato s1("a");
//	assert(s1.EsString());
//	aed2::Dato s2("b");
//	assert(s1.mismoTipo(s2));
//	aed2::Dato s3("c");
//	aed2::Dato s4("d");
//	aed2::Dato s5("e");
//	aed2::Dato s6("a");
//
////
////	aed2::Dato n1(1);
////	assert(s1.EsNat());
//
////	aed2::Dato n2= Dato(2);
////	aed2::Dato n3= Dato(3);
////	aed2::Dato n4= Dato(4);
////	aed2::Dato n5= Dato(5);
////	aed2::Dato n6= Dato(1);
////
////	aed2::Conj<aed2::Dato& > conjuntoS;
////
////	conjuntoS.AgregarRapido(s1);
////	conjuntoS.AgregarRapido(s2);
////	conjuntoS.AgregarRapido(s3);
////	conjuntoS.AgregarRapido(s4);
////	conjuntoS.AgregarRapido(s5);
////	conjuntoS.AgregarRapido(s6);
//
//	return 0;
//};





