#include "Tabla.h"

//using namespace std;
using namespace aed2;


Tabla::Tabla(const NombreTabla& nombre, const aed2::Conj<NombreCampo>& claves, const Registro& columnas){
	Nombre_=nombre;
	Conj<NombreCampo> conj = columnas.Campos();
	Conj<NombreCampo>::Iterador it=conj.CrearIt();



	while(it.HaySiguiente()){



		Campos_.Definir(it.Siguiente(),columnas.Significado(it.Siguiente()).tipo());

		it.Avanzar();
	};


	Claves_=claves;

	CampoR=claves.CrearIt().Siguiente();

	cantAccesos=0;

}
//
//Tabla::Tabla(const NombreTabla& nombre, const Conj<NombreCampo>& claves, const Conj<Columna>& columnas){
//	Nombre_=nombre;
//	Registros_ = Conj<Registro>();
//	Conj<Columna>::const_Iterador it=columnas.CrearIt();
//	while(it.HaySiguiente()){
//		Tipo t = it.Siguiente().tipo==NAT;
//		Campos_.Definir(it.Siguiente().nombre, t);
//		it.Avanzar();
//	};
//	Claves_=claves;
//
//	IndiceS = IndiceString();
//	IndiceDS = DiccLex<Tabla::Conj<Conj<Registro>::Iterador>>();
//	IndiceN = IndiceNat();
//	IndiceDN = DiccNat<Tabla::Conj<Conj<Registro>::Iterador>>();
//
//	CampoR=claves.CrearIt().Siguiente();
//	ConsultaN = DiccNat<Acceso>();
//	ConsultaS = DiccLex<Acceso>();
//	cantAccesos=0;
//}


/*
Tabla::Tabla(const Tabla& t){
	this->Nombre_=t.Nombre_;
	this->Claves_=t.Claves_;
	this->cantAccesos=t.cantAccesos;
	this->CampoR=t.CampoR;
	this->IndiceN.CampoI=t.IndiceN.CampoI;
	this->IndiceN.EnUso=t.IndiceN.EnUso;
	Dato maxNN(t.IndiceN.Max);
	this->IndiceN.Max=maxNN;
	Dato minNN(t.IndiceN.Min);
	this->IndiceN.Min=minNN;
	this->IndiceS.CampoI=t.IndiceS.CampoI;
	this->IndiceS.EnUso=t.IndiceS.EnUso;
	Dato maxSS(t.IndiceS.Max);
	this->IndiceS.Max=maxSS;
	Dato minSS(t.IndiceS.Min);
	this->IndiceS.Min=minSS;
	Conj<NombreCampo >::const_Iterador itclaves = t.Claves_.CrearIt();
	while(itclaves.HaySiguiente()){
		this->Claves_.Agregar(itclaves.Siguiente());
		itclaves.Avanzar();
	}
	Dicc<NombreCampo, Tipo >::Iterador itcampos =t.Campos_.DiccClaves().CrearIt();
	while(itcampos.HaySiguiente()){
//		const NombreCampo a();
//		const Tipo b();
		this->Campos_.Definir(itcampos.SiguienteClave(), itcampos.SiguienteSignificado());
		itcampos.Avanzar();
	}
	Conj<Registro >::const_Iterador itregistros = t.Registros_.CrearIt();
	while(itregistros.HaySiguiente()){
		Registro r;
		Registro::const_Iterador itreg=itregistros.Siguiente().CrearIt();
		while(itreg.HaySiguiente()){
//			const NombreCampo nom=;
//			const Dato d=;
			r.Definir(itreg.SiguienteClave(),itreg.SiguienteSignificado());
			itreg.Avanzar();
		}
		this->agregarRegistro(r);
		itregistros.Avanzar();
	}
}
*/

Tabla::~Tabla(){};

void Tabla::agregarRegistro(const Registro& registro){
	this->cantAccesos++;


	Conj<Registro>::Iterador nuevo = this->Registros_.AgregarRapido(registro);

	bool TipoRelacion=Campos_.Significado(CampoR);
	Acceso a;
	if(this->indices().Cardinal()>0){
		//Sabemos que hay algun indice
		if(IndiceS.EnUso and IndiceN.EnUso){
			Conj<Conj<Registro>::Iterador>::Iterador itcjs;
			aed2::String valorS= registro.Significado(IndiceS.CampoI).valorString();
			if(!IndiceDS.Definido(valorS)){
				Conj<Conj<Registro>::Iterador>& cjs=IndiceDS.Significado(valorS);
				itcjs=cjs.Agregar(nuevo);
			}else{
				// no esta definido
				Conj<Conj<Registro>::Iterador> cjs;
				itcjs=cjs.Agregar(nuevo);
				IndiceDS.Definir(valorS, cjs);
			}
			a.S=itcjs;
			Conj<Conj<Registro>::Iterador>::Iterador itcjn;
			aed2::Nat valorN=registro.Significado(IndiceN.CampoI).valorNat();
			if(IndiceDN.Definido(valorN)){
				Conj<Conj<Registro>::Iterador>& cjn=IndiceDN.Significado(valorN);
				itcjn=cjn.Agregar(nuevo);
			}else{
				// no esta definido
				Conj<Conj<Registro>::Iterador> cjn;
				itcjn=cjn.Agregar(nuevo);
				IndiceDN.Definir(valorN, cjn);
			}
			a.N=itcjn;
			if(TipoRelacion){ //caso
				ConsultaN.Definir(registro.Significado(CampoR).valorNat(), a);
			}else{ //caso string
				ConsultaS.Definir(registro.Significado(CampoR).valorString(), a);
			}
			Dato valorSS=registro.Significado(IndiceS.CampoI);
			Dato valorNN=registro.Significado(IndiceN.CampoI);
			if(IndiceN.Max.valorNat()<=valorNN.valorNat()){
				IndiceN.Max=valorNN;
			}
			if(valorNN.valorNat()<=IndiceN.Min.valorNat()){
				IndiceN.Min=valorNN;
			}
			if(IndiceS.Max.valorString()<=valorSS.valorString()){
				IndiceS.Max=valorSS;
			}
			if(valorSS.valorString()<=IndiceS.Min.valorString()){
				IndiceS.Min=valorSS;
			}
		}else{
			if(IndiceS.EnUso){
				Conj<Conj<Registro>::Iterador>::Iterador itcjs;
				aed2::String valorS= registro.Significado(IndiceS.CampoI).valorString();
				if(!IndiceDS.Definido(valorS)){
					Conj<Conj<Registro>::Iterador>& cjs=IndiceDS.Significado(valorS);
					itcjs=cjs.Agregar(nuevo);
				}else{
					// no esta definido
					Conj<Conj<Registro>::Iterador> cjs;
					itcjs=cjs.Agregar(nuevo);
					IndiceDS.Definir(valorS, cjs);
				}
				a.S=itcjs;
				if(TipoRelacion){ //caso
					ConsultaN.Definir(registro.Significado(CampoR).valorNat(), a);
				}else{ //caso string
					ConsultaS.Definir(registro.Significado(CampoR).valorString(), a);
				}
				Dato valorSS=registro.Significado(IndiceS.CampoI);
				if(IndiceS.Max.valorString()<=valorSS.valorString()){
					IndiceS.Max=valorSS;
				}
				if(valorSS.valorString()<=IndiceS.Min.valorString()){
					IndiceS.Min=valorSS;
				}
			}else{
				if(IndiceN.EnUso){
					Conj<Conj<Registro>::Iterador>::Iterador itcjn;
					Dato valorNN=registro.Significado(IndiceN.CampoI);
					aed2::Nat valorN=registro.Significado(IndiceN.CampoI).valorNat();
					if(IndiceDN.Definido(valorN)){
						Conj<Conj<Registro>::Iterador>& cjn=IndiceDN.Significado(valorN);
						itcjn=cjn.Agregar(nuevo);
					}else{
						// no esta definido
						Conj<Conj<Registro>::Iterador> cjn;
						itcjn=cjn.Agregar(nuevo);
						IndiceDN.Definir(valorN, cjn);
					}
					a.N=itcjn;
					if(TipoRelacion){ //caso nat
						ConsultaN.Definir(registro.Significado(CampoR).valorNat(), a);
					}else{ //caso string
						ConsultaS.Definir(registro.Significado(CampoR).valorString(), a);
					}
					if(IndiceN.Max.valorNat()<=valorNN.valorNat()){
						IndiceN.Max=valorNN;
					}
					if(valorNN.valorNat()<=IndiceN.Min.valorNat()){
						IndiceN.Min=valorNN;
					}
				}
			}
		}
	}
};


const Conj<NombreCampo> Tabla::indices()const{
	Conj<NombreCampo> NomDeCamposInd;
	if(this->IndiceN.EnUso){
		NomDeCamposInd.Agregar(this->IndiceN.CampoI);
	}
	if(this->IndiceS.EnUso){
		NomDeCamposInd.Agregar(this->IndiceS.CampoI);
	}
	return NomDeCamposInd;
}


const Conj<Registro>& Tabla::registros() const{
	return this->Registros_;
}

void Tabla::borrarRegistro(const Registro valor){

	// registro_ tiene un solo campo que es clave.
	Conj<Registro>::Iterador itguia;
	Registro guia;
	NombreCampo campovalor=valor.Campos().CrearIt().Siguiente();
	Dato datovalor=valor.Significado(campovalor);
	bool tipocampovalor = Campos_.Significado(campovalor);

	if((IndiceN.EnUso and IndiceN.CampoI==campovalor) or (IndiceS.EnUso and IndiceS.CampoI==campovalor)){

		if(tipocampovalor){
			//El campo del registro valor es Nat
				Conj<Conj<Registro>::Iterador>& cjItn = IndiceDN.Significado(datovalor.valorNat());
				itguia=cjItn.CrearIt().Siguiente();
				//guia=cjItn.CrearIt().Siguiente().Siguiente();
				while(itguia.HaySiguiente()){

					if(Campos_.Significado(CampoR)){
						ConsultaN.Borrar(itguia.Siguiente().Significado(CampoR).valorNat());
					}else{
						ConsultaS.Borrar(itguia.Siguiente().Significado(CampoR).valorString());
					}

					itguia.EliminarSiguiente();

					if(itguia.HaySiguiente()){
						itguia.Avanzar();
					}
				}
				//if(!itguia.HaySiguiente() && !itguia.HayAnterior()){// si para el conj no hay mas elementos lo elimino del indice.
					IndiceDN.Borrar(datovalor.valorNat());
				//}
		}else{
			//El campo del registro valor es String
				Conj<Conj<Registro>::Iterador>& cjIts = IndiceDS.Significado(datovalor.valorString());
				itguia=cjIts.CrearIt().Siguiente();

				while(itguia.HaySiguiente()){


					if(Campos_.Significado(CampoR)){
						ConsultaN.Borrar(itguia.Siguiente().Significado(CampoR).valorNat());
					}else{
						ConsultaS.Borrar(itguia.Siguiente().Significado(CampoR).valorString());
					}

					itguia.EliminarSiguiente();
					if(itguia.HaySiguiente()){
						itguia.Avanzar();
					}
				}
				itguia.EliminarSiguiente();
				//if(!itguia.HaySiguiente() && !itguia.HayAnterior()){
					IndiceDS.Borrar(datovalor.valorString());
				//}

		}

		// eliminar el it al reg en el otro indice
		/*if(Campos_.Significado(CampoR)){

			Acceso& acceso_= this->ConsultaN.Significado(guia.Significado(CampoR).valorNat());

			if(IndiceS.EnUso){
				acceso_.S.EliminarSiguiente();
				if(!acceso_.S.HaySiguiente()){
					IndiceDS.Borrar(datovalor.valorString());
				}
			}

			if(IndiceN.EnUso){
				std::cout << "acceso_.N.HaySiguiente(): "<< acceso_.N.HaySiguiente() << std::endl;
				//acceso_.N.EliminarSiguiente();
				if(!acceso_.N.HaySiguiente()){
					IndiceDN.Borrar(datovalor.valorNat());
				}
			}

			ConsultaN.Borrar(guia.Significado(CampoR).valorNat());


		}else{

			Acceso& acceso_= this->ConsultaS.Significado(guia.Significado(CampoR).valorString());
			if(IndiceN.EnUso){
				acceso_.N.EliminarSiguiente();
				if(!acceso_.N.HaySiguiente()){
					IndiceDN.Borrar(datovalor.valorNat());
				}
			}

			if(IndiceS.EnUso){
				acceso_.S.EliminarSiguiente();
				if(!acceso_.S.HaySiguiente()){
					IndiceDS.Borrar(datovalor.valorString());
				}
			}

			ConsultaS.Borrar(guia.Significado(CampoR).valorString());
		}*/


		if(IndiceN.EnUso){
			IndiceN.Max=IndiceDN.Maximo();
			IndiceN.Min=IndiceDN.Minimo();
		}
		if(IndiceS.EnUso){
			IndiceS.Max=IndiceDS.Maximo();
			IndiceS.Min=IndiceDS.Minimo();
		}
//		itguia.EliminarSiguiente();

	}else{
		//no hay indice
		Conj<Registro>::Iterador itreg=Registros_.CrearIt();
		while(itreg.HaySiguiente()){
			if(itreg.Siguiente().Significado(campovalor)==datovalor){

				cantAccesos++;

				/*if(IndiceS.EnUso or IndiceN.EnUso){
					Dato datoR=itreg.Siguiente().Significado(CampoR);
					Acceso acceso_;
					if(Campos_.Significado(CampoR)){
						acceso_=ConsultaN.Significado(datoR.valorNat());
					}else{
						acceso_=ConsultaS.Significado(datoR.valorString());
					}
					if(IndiceS.EnUso){
						acceso_.S.EliminarSiguiente();
						if(!acceso_.S.HaySiguiente()){
							IndiceDS.Borrar(datovalor.valorString());
						}
					}
					if(IndiceN.EnUso){
						acceso_.N.EliminarSiguiente();
						if(!acceso_.N.HaySiguiente()){
							IndiceDN.Borrar(datovalor.valorNat());
						}
					}
					if(Campos_.Significado(CampoR)){
						ConsultaN.Borrar(guia.Significado(CampoR).valorNat());
					}else{
						ConsultaS.Borrar(guia.Significado(CampoR).valorString());
					}
				}*/

				itreg.EliminarSiguiente();
			}

			if(itreg.HaySiguiente()){
				itreg.Avanzar();
			}

		}
	}
};

void Tabla::indexar(const NombreCampo campo)
{
	assert((this->tipoCampo(campo) && !IndiceN.EnUso) or (!this->tipoCampo(campo) and !IndiceS.EnUso));

	Conj<Conj<Registro >::Iterador >::Iterador SS;
	Conj<Conj<Registro >::Iterador>::Iterador NN;

	Conj<Registro >::Iterador itreg=this->Registros_.CrearIt();
	while(itreg.HaySiguiente()){
		Registro R=itreg.Siguiente();
		if(this->tipoCampo(campo)){
			Nat valor=R.Significado(campo).valorNat();
			if(!IndiceDN.Definido(valor)){
				Conj<Conj<Registro>::Iterador> cjIt;
				IndiceDN.Definir(valor, cjIt);
			}
			NN=IndiceDN.Significado(valor).Agregar(itreg);
		}else{
			String valor=R.Significado(campo).valorString();
			if(!IndiceDS.Definido(valor)){
				Conj<Conj<Registro>::Iterador> cjIt;
				IndiceDS.Definir(valor, cjIt);
			}
			SS=IndiceDS.Significado(valor).Agregar(itreg);
		}
		if(this->tipoCampo(CampoR)){
			if(!this->ConsultaN.Definido(R.Significado(CampoR).valorNat())){
				Acceso acceso_;
				acceso_.N=NN;
				acceso_.S=SS;
				this->ConsultaN.Definir(R.Significado(CampoR).valorNat(), acceso_);
			}else{
				if(!IndiceN.EnUso){
					this->ConsultaN.Significado(R.Significado(CampoR).valorNat()).N=NN;
				}
				if(!IndiceS.EnUso){
					this->ConsultaS.Significado(R.Significado(CampoR).valorString()).S=SS;
				}
			}
		}else{
			if(!this->ConsultaS.Definido(R.Significado(CampoR).valorString())){
				Acceso acceso_;
				acceso_.N=NN;
				acceso_.S=SS;
				this->ConsultaS.Definir(R.Significado(CampoR).valorString(), acceso_);
			}else{
				if(!IndiceN.EnUso){
					this->ConsultaN.Significado(R.Significado(CampoR).valorNat()).N=NN;
				}
				if(!IndiceS.EnUso){
					this->ConsultaS.Significado(R.Significado(CampoR).valorString()).S=SS;
				}
			}
		}
		itreg.Avanzar();
	}
	if(this->tipoCampo(campo)){
		this->IndiceN.EnUso = true;
		this->IndiceN.CampoI = campo;
		this->IndiceN.Max = Dato(IndiceDN.Maximo());
		this->IndiceN.Min = Dato(IndiceDN.Minimo());
	}else{
		this->IndiceS.EnUso = true;
		this->IndiceS.CampoI=campo;
		this->IndiceS.Max = Dato(IndiceDS.Maximo());
		this->IndiceS.Min = Dato(IndiceDS.Minimo());
	}

};

const Tipo Tabla::tipoCampo(const NombreCampo c) const{
	return Campos_.Significado(c);
};

const Conj<NombreCampo> Tabla::campos()const{
	Conj<NombreCampo>::const_Iterador itcampos = this->Campos_.DiccClaves().CrearIt();
	Conj<NombreCampo> cjcampos;
	while(itcampos.HaySiguiente()){
		cjcampos.Agregar(itcampos.Siguiente());
		itcampos.Avanzar();
	}
	return cjcampos;
};

NombreTabla Tabla::nombre()const{
	return this->Nombre_;
};

const Conj<NombreCampo> Tabla::claves()const{
	return this->Claves_;
};

Nat Tabla::cantidadDeAccesos() const{
	return this->cantAccesos;
};

bool Tabla::puedoInsertar(const Registro r)const{
 	return (this->compatible(r) and !(this->hayCoincidencia(r, this->claves(),this->registros())));
};


bool Tabla::compatible(const Registro reg)const{
 	bool valor=true;
 	if(reg.Campos().Cardinal()==Campos_.DiccClaves().Cardinal()){
 		Conj<NombreCampo>::const_Iterador itcampos=Campos_.DiccClaves().CrearIt();
 		while(valor and itcampos.HaySiguiente()){
 			NombreCampo c=itcampos.Siguiente();
 			valor=reg.Definido(c);
 		}
 	}else{
 		valor=false;
 	}
 	return (valor and this->mismosTipos(reg));
 }

const Dato& Tabla::minimo(const NombreCampo campo)const{
		if(IndiceN.EnUso and IndiceN.CampoI==campo){
			return IndiceN.Min;
		}else{
			return IndiceS.Min;
		}
}

const Dato& Tabla::maximo(const NombreCampo campo)const{
		if(IndiceN.EnUso and IndiceN.CampoI==campo){
			return IndiceN.Max;
		}else{
			return IndiceS.Max;
		}
}

bool Tabla::puedeIndexar(const NombreCampo c)const{
	if(this->tipoCampo(c)){
		return !IndiceN.EnUso;
	}else{
		return !IndiceS.EnUso;
	}
}

bool Tabla::hayCoincidencia(const Registro reg, const Conj<NombreCampo > cjcampo, const Conj<Registro > cjreg)const{
	Conj<Registro >::const_Iterador itcr=cjreg.CrearIt();
	bool res=false;

	while(itcr.HaySiguiente()){
	 	res=itcr.Siguiente().CoincideAlguno(cjcampo,reg);
	 	itcr.Avanzar();
	 }
	 return res;
};

Conj<Conj<Registro>::const_Iterador> Tabla::coincidencias(const Registro crit, const Conj<Registro>& cjreg) const{
	Conj<Conj<Registro>::const_Iterador > salida;
	Conj<Registro>::const_Iterador itcr=cjreg.CrearIt();

	while(itcr.HaySiguiente()){

		if(crit.CoincidenTodos(crit.Campos(), itcr.Siguiente())){
			salida.AgregarRapido(itcr);
		}
		itcr.Avanzar();
	}

	return salida;
};

Conj<Registro> combinarRegistros(const NombreCampo campo, const Conj<Registro > cr1, const Conj<Registro > cr2){
	Conj<Registro> res;
	Conj<Registro >::const_Iterador itcr2=cr2.CrearIt();
	if(cr1.Cardinal()>0){
		Tipo rac=itcr2.Siguiente().Significado(campo).tipo();
		if(rac==NAT){
			// caso Nat
			DiccNat<Registro > d;
			Conj<Registro>::const_Iterador itaux=cr1.CrearIt();
			while(itaux.HaySiguiente()){
				d.Definir(itaux.Siguiente().Significado(campo).valorNat(), itaux.Siguiente());
			}
			while(itcr2.HaySiguiente()){
				if(d.Definido(itcr2.Siguiente().Significado(campo).valorNat())){
					Registro regaux;
					Conj<NombreCampo>::const_Iterador icnj= itcr2.Siguiente().Campos().CrearIt();

					while(icnj.HaySiguiente()){
						regaux.Definir(icnj.Siguiente(),itcr2.Siguiente().Significado(icnj.Siguiente()));
						icnj.Avanzar();
					}
					res.AgregarRapido(regaux.UnirRegistros(campo,d.Significado(regaux.Significado(campo).valorNat())));
				}
				itcr2.Avanzar();
			}
		}else{
			// caso String
			DiccLex<Registro > d;
			Conj<Registro>::const_Iterador itaux=cr1.CrearIt();
			while(itaux.HaySiguiente()){
				d.Definir(itaux.Siguiente().Significado(campo).valorString(), itaux.Siguiente());
			}
			while(itcr2.HaySiguiente()){
				if(d.Definido(itcr2.Siguiente().Significado(campo).valorString())){
					Registro regaux;
					Conj<NombreCampo>::const_Iterador icnj= itcr2.Siguiente().Campos().CrearIt();
					while(icnj.HaySiguiente()){
						regaux.Definir(icnj.Siguiente(),itcr2.Siguiente().Significado(icnj.Siguiente()));
						icnj.Avanzar();
					}
					res.AgregarRapido(regaux.UnirRegistros(campo,d.Significado(regaux.Significado(campo).valorString())));
				}
				itcr2.Avanzar();
		}
	}
	}
	return res;
};

bool Tabla::mismosTipos(const Registro reg)const{
	bool valor=true;
	Conj<NombreCampo>::const_Iterador itClaves=reg.Campos().CrearIt();
	Conj<NombreCampo>::const_Iterador itCampos=this->Campos_.DiccClaves().CrearIt();
	while(valor && itClaves.HaySiguiente()){
		bool val1=reg.Significado(itClaves.Siguiente()).EsNat();
		bool val2=(this->tipoCampo(itCampos.Siguiente()))==NAT;
		valor=(val1==val2);
		itClaves.Avanzar();
	}
	return valor;
};

Conj<Conj<Registro>::const_Iterador> Tabla::buscarEnTabla(const Registro criterio) const{
	Conj<NombreCampo> campos=this->Campos_.DiccClaves();

	Conj<Conj<Registro>::const_Iterador> res;

	if(this->IndiceN.EnUso or this->IndiceS.EnUso){

		if(this->IndiceN.EnUso && campos.Pertenece(this->IndiceN.CampoI)){

			Conj<Conj<Registro>::Iterador> conj = this->IndiceDN.Significado(criterio.Significado(this->IndiceN.CampoI).valorNat());
			Conj<Conj<Registro>::Iterador>::Iterador itconj = conj.CrearIt();

			while(itconj.HaySiguiente()){

				if(criterio.CoincidenTodos(campos, itconj.Siguiente().Siguiente())){
					res.AgregarRapido(itconj.Siguiente());
				}

				itconj.Avanzar();
			}
		}

		if(this->IndiceN.EnUso && campos.Pertenece(this->IndiceN.CampoI)){

			Conj<Conj<Registro>::Iterador> conj = this->IndiceDS.Significado(criterio.Significado(this->IndiceS.CampoI).valorString());
			Conj<Conj<Registro>::Iterador>::Iterador itconj = conj.CrearIt();

			while(itconj.HaySiguiente()){

				if(criterio.CoincidenTodos(campos, itconj.Siguiente().Siguiente())){
					res.AgregarRapido(itconj.Siguiente());
				}

				itconj.Avanzar();
			}
		}

	}else{

		res = this->coincidencias(criterio, this->Registros_);

	}

	return res;
}


const Conj<Dato> Tabla::dameColumna(const NombreCampo campo, const Conj<Registro> cr) const{
	assert(!cr.EsVacio());
	Conj<Dato> res = Conj<Dato>();
	Conj<Registro >::const_Iterador it=cr.CrearIt();
	Tipo Tvalor=it.Siguiente().Significado(campo).tipo();
	if(Tvalor){
		DiccNat< Dato > bolsaN;
		while(it.HaySiguiente()){
			bolsaN.Definir(it.Siguiente().Significado(campo).valorNat(),it.Siguiente().Significado(campo));
			it.Avanzar();
		}
		Lista<Nat>::Iterador itN=bolsaN.DiccClaves().CrearIt();
		while(itN.HaySiguiente()){
			res.AgregarRapido(bolsaN.Significado(itN.Siguiente()));
			itN.Avanzar();
		}
	}else{
		DiccLex<Dato > bolsaS;
		while(it.HaySiguiente()){
			bolsaS.Definir(it.Siguiente().Significado(campo).valorString(),it.Siguiente().Significado(campo));
			it.Avanzar();
		}
		aed2::Conj<String >::const_Iterador itS=bolsaS.DiccClaves().CrearIt();
		while(itS.HaySiguiente()){
			res.AgregarRapido(bolsaS.Significado(itS.Siguiente()));
			itS.Avanzar();
		}
	}
	return res;
}
