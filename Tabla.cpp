#include "Tabla.h"

using namespace std;
using namespace aed2;

/*
Tabla::Tabla(const NombreTabla nombre, const aed2::Conj<NombreCampo> claves, const Registro columnas){
	Nombre_=nombre;
	Conj<Campo>::const_Iterador it=columnas.CrearIt();
	while(it.HaySiguiente()){
		Campos_.Definir(it.SiguienteClave(),it.SiguienteSignificado().tipo());
		it.Avanzar();
	};
	Claves_=claves;
	CampoR=claves.CrearIt().Siguiente();
	cantAccesos=0;
}*/

Tabla::Tabla(const NombreTabla& nombre, const Conj<NombreCampo>& claves, const Conj<Columna>& columnas){
	Nombre_=nombre;
	Conj<Columna>::const_Iterador it=columnas.CrearIt();
	while(it.HaySiguiente()){
		Campos_.Definir(it.Siguiente().nombre,it.Siguiente().tipo);
		it.Avanzar();
	};
	Claves_=claves;
	CampoR=claves.CrearIt().Siguiente();
	cantAccesos=0;
}


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

void Tabla::agregarRegistro(const Registro registro){
	this->cantAccesos++;
	//Registro reg = Registro(registro_);
	Conj<Registro>::Iterador nuevo = this->Registros_.Agregar(registro);
	bool TipoRelacion=Campos_.Significado(CampoR);
	Acceso a;
	if(this->indices().Cardinal()>0){
		//Sabemos que hay algun indice
		if(IndiceS.EnUso and IndiceN.EnUso){
			Tabla::CjDeIteradores::Iterador itcjs;
			aed2::String valorS= registro.Significado(IndiceS.CampoI).valorString();
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
			aed2::Nat valorN=registro.Significado(IndiceN.CampoI).valorNat();
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
			if(TipoRelacion){ //caso
				ConsultaN.Definir(registro.Significado(CampoR).valorNat(), a);
			}else{ //caso string
				ConsultaS.Definir(registro.Significado(CampoR).valorString(), a);
			}
			Dato valorSS=registro.Significado(IndiceS.CampoI);
			Dato valorNN=registro.Significado(IndiceN.CampoI);
			if(IndiceN.Max<=valorNN){
				IndiceN.Max=valorNN;
			}
			if(valorNN<=IndiceN.Min){
				IndiceN.Min=valorNN;
			}
			if(IndiceS.Max<=valorSS){
				IndiceS.Max=valorSS;
			}
			if(valorSS<=IndiceS.Min){
				IndiceS.Min=valorSS;
			}
		}else{
			if(IndiceS.EnUso){
				Tabla::CjDeIteradores::Iterador itcjs;
				aed2::String valorS= registro.Significado(IndiceS.CampoI).valorString();
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
				if(TipoRelacion){ //caso
					ConsultaN.Definir(registro.Significado(CampoR).valorNat(), a);
				}else{ //caso string
					ConsultaS.Definir(registro.Significado(CampoR).valorString(), a);
				}
				Dato valorSS=registro.Significado(IndiceS.CampoI);
				if(IndiceS.Max<=valorSS){
					IndiceS.Max=valorSS;
				}
				if(valorSS<=IndiceS.Min){
					IndiceS.Min=valorSS;
				}
			}else{
				if(IndiceN.EnUso){
					Tabla::CjDeIteradores::Iterador itcjn;
					Dato valorNN=registro.Significado(IndiceN.CampoI);
					aed2::Nat valorN=registro.Significado(IndiceN.CampoI).valorNat();
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
						ConsultaN.Definir(registro.Significado(CampoR).valorNat(), a);
					}else{ //caso string
						ConsultaS.Definir(registro.Significado(CampoR).valorString(), a);
					}
					if(IndiceN.Max<=valorNN){
						IndiceN.Max=valorNN;
					}
					if(valorNN<=IndiceN.Min){
						IndiceN.Min=valorNN;
					}
				}
			}
		}
	}
};


const aed2::Conj<aed2::NombreCampo > Tabla::indices()const{
	aed2::Conj<NombreCampo > NomDeCamposInd;
	if(this->IndiceN.EnUso){
		//NomDeCamposInd.Agregar(t.IndiceN.CampoI);
	}
	if(this->IndiceS.EnUso){
		//NomDeCamposInd.Agregar(t.IndiceS.CampoI);
	}
	return NomDeCamposInd;
}


const Conj<Registro>& Tabla::registros() const{
	return this->Registros_;
}

void Tabla::borrarRegistro(const Registro valor){
	cantAccesos++;
	// registro_ tiene un solo campo que es clave.
	Conj<Registro >::Iterador itguia;
	Registro guia;
	NombreCampo campovalor=valor.Campos().CrearIt().Siguiente();
	Dato datovalor=valor.Significado(campovalor);
	bool tipocampovalor = Campos_.Significado(campovalor);
	if((IndiceN.EnUso and IndiceN.CampoI==campovalor) or (IndiceS.EnUso and IndiceS.CampoI==campovalor)){
		Acceso acceso_;
		if(tipocampovalor){
			//El campo del registro valor es Nat
				CjDeIteradores cjItn = IndiceDN.Significado(datovalor.valorNat());
				itguia=cjItn.CrearIt().Siguiente();
				guia=cjItn.CrearIt().Siguiente().Siguiente();
				itguia.EliminarSiguiente();
				if(!itguia.HaySiguiente()){// si para el conj no hay mas elementos lo elimino del indice.
					IndiceDN.Borrar(datovalor.valorNat());
				}
		}else{
			//El campo del registro valor es String
				CjDeIteradores cjIts = IndiceDS.Significado(datovalor.valorString());
				itguia=cjIts.CrearIt().Siguiente();
				guia=cjIts.CrearIt().Siguiente().Siguiente();
				itguia.EliminarSiguiente();
				if(!itguia.HaySiguiente()){
					IndiceDS.Borrar(datovalor.valorString());
				}
		}
		// eliminar el it al reg en el otro indice
		if(Campos_.Significado(CampoR)){
			acceso_=ConsultaN.Significado(guia.Significado(CampoR).valorNat());
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
			ConsultaN.Borrar(guia.Significado(CampoR).valorNat());
		}else{
			acceso_=ConsultaS.Significado(guia.Significado(CampoR).valorString());
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
		}
//		if(IndiceN.EnUso){
//			IndiceN.Max=IndiceN.DiccClaves.min();
//			IndiceN.Min=IndiceN.DiccClaves.min();
//		}
//		if(IndiceS.EnUso){
//			IndiceS.Max=IndiceS.DiccClaves.min();
//			IndiceS.Min=IndiceS.DiccClaves.min();
//		}
		itguia.EliminarSiguiente();

	}else{
		//no hay indice
		Conj<Registro >::Iterador itreg=Registros_.CrearIt();
		while(itreg.HaySiguiente()){
			if(itreg.Siguiente().Significado(campovalor)==datovalor){

				if(IndiceS.EnUso or IndiceN.EnUso){
					Dato datoR=itreg.Siguiente().Significado(CampoR);
					Acceso acceso_;
					if(Campos_.Significado(CampoR)){
						acceso_=ConsultaN.Significado(datoR.valorNat());
					}else{
						acceso_=ConsultaS.Significado(datoR.valorString());
					}
					if(IndiceS.EnUso){
						acceso_.S.EliminarSiguiente();
						if(!acceso_.S.HaySiguiente()){							IndiceDS.Borrar(datovalor.valorString());
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
				}
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
	assert(this->tipoCampo(campo) and !IndiceN.EnUso);
	assert(!this->tipoCampo(campo) and !IndiceS.EnUso);
	Conj<Conj<Registro >::Iterador >::Iterador SS;
	Conj<Conj<Registro >::Iterador>::Iterador NN;
	if(this->tipoCampo(campo)){
		IndiceN.EnUso=true;
		IndiceN.CampoI=campo;
	}else{
		IndiceS.EnUso=true;
		IndiceS.CampoI=campo;
	}
	Conj<Registro >::Iterador itreg=this->Registros_.CrearIt();
	while(itreg.HaySiguiente()){
		Registro R=itreg.Siguiente();
		if(this->tipoCampo(campo)){
			Nat valor=R.Significado(campo).valorNat();
			if(!IndiceDN.Definido(valor)){
				CjDeIteradores cjIt;
				IndiceDN.Definir(valor, cjIt);
			}
			NN=IndiceDN.Significado(valor).Agregar(itreg);
		}else{
			String valor=R.Significado(campo).valorString();
			if(!IndiceDS.Definido(valor)){
				CjDeIteradores cjIt;
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
		IndiceN.EnUso=true;
		IndiceN.CampoI=campo;
	}else{
		IndiceS.EnUso=true;
		IndiceS.CampoI=campo;
	}

};

const Tipo Tabla::tipoCampo(const NombreCampo c) const{
	return Campos_.Significado(c);
};

const Conj<NombreCampo> Tabla::campos()const{
	Conj<NombreCampo>::Iterador itcampos = this->Campos_.DiccClaves().CrearIt();
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

Nat Tabla::cantidadDeAccesos() const{
	return this->cantAccesos;
};

//const bool Tabla::puedoInsertar(const Registro r)const{
//
//};


//const bool Tabla::compatible(const Registro reg){
//	bool valor=true;
//	if(reg.campos().){
//
//	}
//}

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
	return true;
};

Conj<Conj<Registro >::Iterador > Tabla::coincidencias(const Registro crit, Conj<Registro > cjreg) const{
	Conj<Conj<Registro >::Iterador > salida;
	Conj<Registro >::Iterador itcr=cjreg.CrearIt();
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
					Conj<NombreCampo>::Iterador icnj= itcr2.Siguiente().Campos().CrearIt();

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
					Conj<NombreCampo>::Iterador icnj= itcr2.Siguiente().Campos().CrearIt();
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
	Conj<NombreCampo>::Iterador itClaves=reg.Campos().CrearIt();
	Conj<NombreCampo>::Iterador itCampos=this->Campos_.DiccClaves().CrearIt();
	while(valor && itClaves.HaySiguiente()){
		bool val1=reg.Significado(itClaves.Siguiente()).EsNat();
		bool val2=(this->tipoCampo(itCampos.Siguiente()))==NAT;
		valor=(val1==val2);
		itClaves.Avanzar();
	}
	return valor;
};

Conj<Conj<Registro>::Iterador> Tabla::buscarEnTabla(const Registro criterio) const{
	Conj<NombreCampo>::Iterador itcampos=this->Campos_.DiccClaves().CrearIt();
	bool Encontrado=false;
	NombreCampo EncontradoCampoInd;
	Conj<NombreCampo > cj;
	Conj<Conj<Registro>::Iterador> res;
	while(itcampos.HaySiguiente()){
		NombreCampo c=itcampos.Siguiente();
		bool Def=criterio.Definido(c);
		if(Def){
			bool valorD=(criterio.Significado(c)==Campos_.Significado(c));
			if(valorD){
				cj.AgregarRapido(c);
				bool EncS=(IndiceS.EnUso and IndiceS.CampoI==c);
				bool EncN=(IndiceN.EnUso and IndiceN.CampoI==c);
				bool Encontrado=(EncS or EncN);
				if(Encontrado){
					EncontradoCampoInd=c;
				}
			}
		}
		itcampos.Avanzar();
	}
	if(Encontrado){
		if(IndiceN.EnUso and IndiceN.CampoI==EncontradoCampoInd){
			Nat valor=criterio.Significado(EncontradoCampoInd).valorNat();
			res = this->IndiceDN.Significado(valor);
		}
		if(IndiceS.EnUso and IndiceS.CampoI==EncontradoCampoInd){
			String valor=criterio.Significado(EncontradoCampoInd).valorString();
			res = this->IndiceDS.Significado(valor);
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
		aed2::Conj<String >::Iterador itS=bolsaS.DiccClaves().CrearIt();
		while(itS.HaySiguiente()){
			res.AgregarRapido(bolsaS.Significado(itS.Siguiente()));
			itS.Avanzar();
		}
	}
	return res;
}
