// compilar usando:
//   g++ -o tests tests.cpp Driver.cpp <lista de archivos *.cpp propios>
#include <cassert>

#include "Tabla.h"
#include <string>
#include <iostream>
namespace aed2{

//Tabla(const NombreTabla& nombre, const aed2::Conj<NombreCampo >& claves, const Registro& columnas);

aed2::Tabla::Tabla(const NombreTabla& nombre, const aed2::Conj<NombreCampo >& claves, const Registro& columnas){
	Nombre_=nombre;
	Registro::const_Iterador it=columnas.CrearIt();
	while(it.HaySiguiente()){
		Campos_.Definir(it.SiguienteClave(),it.SiguienteSignificado().tipo());
		it.Avanzar();
	};
	Claves_=claves;
	CampoR=claves.CrearIt().Siguiente();
	cantAccesos=0;
};

aed2::Tabla::~Tabla(){};

void aed2::Tabla::agregarRegistro(const Registro& registro_){
	cantAccesos++;
	Registro reg=Registro(registro_);

	aed2::Conj<Registro >::Iterador nuevo= Registros_.Agregar(reg);
	bool TipoRelacion=Campos_.Significado(CampoR);
	Acceso a;
	if(this->indices().Cardinal()>0){
		//Sabemos que hay algun indice
		if(IndiceS.EnUso and IndiceN.EnUso){
			Tabla::CjDeIteradores::Iterador itcjs;
			aed2::String valorS= reg.Significado(IndiceS.CampoI).valorString();
			if(!IndiceDS.Definido(valorS)){
				Tabla::CjDeIteradores cjs=IndiceDS.Significado(valorS);
				itcjs=cjs.Agregar(nuevo);
			}else{
				// no esta definido
				Tabla::CjDeIteradores cjs;
				itcjs=cjs.Agregar(nuevo);
				IndiceDS.Definir(valorS, cjs);
			}
			a.S=itcjs;
			Tabla::CjDeIteradores::Iterador itcjn;
			aed2::Nat valorN=reg.Significado(IndiceN.CampoI).valorNat();
			if(IndiceDN.Definido(valorN)){
				Tabla::CjDeIteradores cjn=IndiceDN.Significado(valorN);
				itcjn=cjn.Agregar(nuevo);
			}else{
				// no esta definido
				Tabla::CjDeIteradores cjn;
				itcjn=cjn.Agregar(nuevo);
				IndiceDN.Definir(valorN, cjn);
			}
			a.N=itcjn;
			if(TipoRelacion){ //caso nat
				ConsultaN.Definir(reg.Significado(CampoR).valorNat(), a);
			}else{ //caso string
				ConsultaS.Definir(reg.Significado(CampoR).valorString(), a);
			}

		}else{
			if(IndiceS.EnUso){
				Tabla::CjDeIteradores::Iterador itcjs;
				aed2::String valorS= reg.Significado(IndiceS.CampoI).valorString();
				if(!IndiceDS.Definido(valorS)){
					Tabla::CjDeIteradores cjs=IndiceDS.Significado(valorS);
					itcjs=cjs.Agregar(nuevo);
				}else{
					// no esta definido
					Tabla::CjDeIteradores cjs;
					itcjs=cjs.Agregar(nuevo);
					IndiceDS.Definir(valorS, cjs);
				}
				a.S=itcjs;
				if(TipoRelacion){ //caso nat
					ConsultaN.Definir(reg.Significado(CampoR).valorNat(), a);
				}else{ //caso string
					ConsultaS.Definir(reg.Significado(CampoR).valorString(), a);
				}

			}else{
				if(IndiceN.EnUso){
					Tabla::CjDeIteradores::Iterador itcjn;
					aed2::Nat valorN=reg.Significado(IndiceN.CampoI).valorNat();
					if(IndiceDN.Definido(valorN)){
						Tabla::CjDeIteradores cjn=IndiceDN.Significado(valorN);
						itcjn=cjn.Agregar(nuevo);
					}else{
						// no esta definido
						Tabla::CjDeIteradores cjn;
						itcjn=cjn.Agregar(nuevo);
						IndiceDN.Definir(valorN, cjn);
					}
					a.N=itcjn;
					if(TipoRelacion){ //caso nat
						ConsultaN.Definir(reg.Significado(CampoR).valorNat(), a);
					}else{ //caso string
						ConsultaS.Definir(reg.Significado(CampoR).valorString(), a);
					}

				}
			}
		}


	}
};
//
const aed2::Conj<aed2::NombreCampo > Tabla::indices()const{
	aed2::Conj<NombreCampo > NomDeCamposInd;
	if(this->IndiceN.EnUso){
		//NomDeCamposInd.Agregar(t.IndiceN.CampoI);
	}
	if(this->IndiceS.EnUso){
		//NomDeCamposInd.Agregar(t.IndiceS.CampoI);
	}
	return NomDeCamposInd;
};


aed2::Conj<aed2::Tabla::Registro > Tabla::registros() const{
	return this->Registros_;

};

};

int main(){

	aed2::Conj<aed2::NombreCampo > cjcampo;
	cjcampo.Agregar("Nombre");
	cjcampo.Agregar("Dni");
	aed2::Tabla::Registro reg;
	aed2::Dato datonumero(1);
	aed2::Dato datoletra("a");
	reg.Definir("Nombre", datoletra);
	reg.Definir("Dni", datonumero);
	aed2::Tabla t("tabla", cjcampo, reg);
	t.agregarRegistro(reg);
	assert(t.registros().Pertenece(reg));





	return 0;

};
