#ifndef BASE_H_
#define BASE_H_

#include "Dato.h"
#include "Tipos.h"
#include "Tabla.h"
#include "DiccNat.h"
#include "aed2/Lista.h"
#include "aed2/Dicc.h"
#include "aed2/Conj.h"
#include "aed2/TiposBasicos.h"

namespace aed2
{

class Base
{
	public:

	typedef aed2::Dicc/*String*/<NombreCampo, Dato> Registro;



	Base();

	Conj<NombreTabla>::Iterador DameTablas();

	Tabla& DameTabla(const NombreTabla);

	bool HayJoin(const NombreTabla, const NombreTabla);

	NombreCampo CampoJoin(const NombreTabla, const NombreTabla);

	void AgregarTabla(const Tabla&);

	void InsertarEntrada(const Registro, const NombreTabla);

	void Borrar(const Registro, const NombreTabla);

	void GenerarVistaJoin(const NombreTabla, const NombreTabla, const NombreCampo);

	void BorrarJoin(const NombreTabla, const NombreTabla);

	Conj<Registro> Registros(const NombreTabla);

	Conj<Registro> VistaJoin(const NombreTabla, const NombreTabla);

	int CantidadDeAccesos(const NombreTabla) const;

	const NombreTabla TablaMaxima();

	const NombreTabla EncontrarMaximo(const NombreTabla, const Conj<NombreTabla>);

	Conj<Conj<Registro>::Iterador> Buscar(const Registro, const NombreTabla);



	private:

	struct Tmax{
			NombreTabla NomTabla;
			Nat Modif;
			Tmax(): NomTabla(""), Modif(0){};
		};

	struct InfoTabla{
		Tabla TActual;
		Dicc/*String*/<NombreTabla, struct InfoJoin> Joins;
		InfoTabla(Tabla t): TActual(t), Joins(Dicc/*String*/()){};
	};

	struct InfoJoin{
		Lista<struct DatoCambio> Rcambios;
		NombreCampo CampoJ;
		Tipo CampoT;
		Dicc/*String*/<String, Conj<Registro>::Iterador> JoinS;
		DiccNat<Conj<Registro>::Iterador> JoinN;
		Conj<Registro> JoinC;
		InfoJoin(NombreCampo nc,
				Tipo tc,
				Dicc/*String*/<String, Conj<Registro>::Iterador> ds,
				Dicc/*Nat*/<Nat, Conj<Registro>::Iterador> dn,
				Conj<Registro> cr): Rcambios(Lista<struct DatoCambio>::Lista()), CampoJ(nc), CampoT(tc), JoinS(ds), JoinN(dn), JoinC(cr) {};
	};

	struct DatoCambio{
		Registro Reg;
		NombreTabla NomOrigen;
		bool Accion;
		DatoCambio(Registro r, NombreTabla n, bool b): Reg(r), NomOrigen(n), Accion(b) {};
	};

	Tmax TabMaxima;
	Dicc/*String*/<NombreTabla, InfoTabla> Tablas;


}; // class Base


Base::Base()
{
	this->TabMaxima = Tmax();
	this->Tablas = Dicc/*String*/<NombreTabla, InfoTabla>();
};

Conj<NombreTabla>::Iterador Base::DameTablas()
{
	return this->Tablas.claves_;
	//return this->Tablas.Claves();
};

Tabla& Base::DameTabla(const NombreTabla t)
{
	return this->Tablas.Significado(t).TActual;
};

bool Base::HayJoin(const NombreTabla t1, const NombreTabla t2)
{
	return this->Tablas.Significado(t1).Joins.Definido(t2) && this->Tablas.Significado(t2).Joins.Definido(t1);
};

NombreCampo Base::CampoJoin(const NombreTabla t1, const NombreTabla t2)
{
	InfoJoin* InfoJ = this->Tablas.Significado(t1).Joins.Significado(t2);
	return InfoJ->CampoJ;
};

void Base::AgregarTabla(const Tabla& t)
{
	InfoTabla it = InfoTabla(t);
	this->Tablas.Definir(t.Nombre_, it);
};

void Base::InsertarEntrada(const Registro r, const NombreTabla t)
{
	InfoTabla* InfoT = this->Tablas.Significado(t);
	InfoT->TActual.agregarRegistro(r);
	InfoT->TActual.cantAccesos++;


	if(InfoT->Joins.claves_.EsVacia() /*InfoT->Joins.Vacio()*/)
	{
		//Conj<NombreTabla>::Iterador NomTab = InfoT.Joins.Claves().CrearIt();
		Lista<NombreTabla>::Iterador NomTab = InfoT->Joins.claves_.CrearIt();

		while(NomTab.HaySiguiente()){

			InfoJoin* InfoJ = InfoT->Joins.Significado(NomTab.Siguiente());
			DatoCambio DatoC = DatoCambio(r, t, true);
			InfoJ->Rcambios.AgregarAtras(DatoC);
			NomTab.Avanzar();

		}

	}

	if(InfoT->TActual.cantAccesos > this->TabMaxima.Modif)
	{
		this->TabMaxima.Modif = InfoT->TActual.cantAccesos;
		this->TabMaxima.NomTabla = t;
	}



};

void Base::Borrar(const Registro cr, const NombreTabla t)
{
	InfoTabla* InfoT = this->Tablas.Significado(t);

	if(InfoT->Joins.claves_.EsVacia() /*InfoT.Joins.Vacio()*/)
	{
		Lista<NombreTabla>::Iterador itNom = InfoT->Joins.claves_.CrearIt();

		while(itNom.HaySiguiente()){
			InfoJoin* InfoJ = InfoT->Joins.Significado(itNom.Siguiente());

			if(cr.Definido(InfoJ->CampoJ))
			{
				Conj<Conj<Registro>::Iterador> c = InfoT->TActual.buscarEnTabla(cr);
				Registro reg = c.CrearIt().Siguiente().Siguiente();
				DatoCambio DatoC = DatoCambio(reg, itNom.Siguiente(), false);
				InfoJ->Rcambios.Lista<DatoCambio>::AgregarAtras(DatoC);
			}else{

				Conj<Conj<Registro>::Iterador> eje = InfoT->TActual.buscarEnTabla(cr);
				Conj<Conj<Registro>::Iterador>::Iterador itReg = eje.CrearIt();

				while(itReg.HaySiguiente())
				{
					DatoCambio DatoC = DatoCambio(itReg.Siguiente(), t, false);
					InfoJ->Rcambios.AgregarAtras(DatoC);
					itReg.Avanzar();
				}
			}
		}
	}

	InfoT->TActual.borrarRegistro(cr);
	InfoT->TActual.cantAccesos++;

	if(InfoT->TActual.cantAccesos > this->TabMaxima.Modif)
	{
		this->TabMaxima.NomTabla = t;
		this->TabMaxima.Modif = InfoT->TActual.cantAccesos;
	}
};

void Base::GenerarVistaJoin(const NombreTabla t1, const NombreTabla t2, const NombreCampo c)
{
	Lista<DatoCambio> Rcambios = Lista<DatoCambio>();

	Tipo CampoT = this->Tablas.Significado(t1).TActual.tipoCampo(c);

	NombreTabla CampoJ = c;

	Dicc/*String*/<String, Conj<Registro>::Iterador> JoinS = Dicc/*String*/<String, Conj<Registro>::Iterador>();
	DiccNat<Conj<Registro>::Iterador> JoinN = DiccNat<Conj<Registro>::Iterador>();

	Conj<Registro> JoinC = Conj<Registro>();

	Tabla* Ta1 = this->Tablas.Significado(t1).TActual;
	Tabla* Ta2 = this->Tablas.Significado(t2).TActual;

	Nat n = Ta1->Registros_.Cardinal();
	Nat m = Ta2->Registros_.Cardinal();

	Conj<Dato> cjd1 = Ta1->dameColumna(c, Ta1->registros());
	Conj<Dato> cjd2 = Ta2->dameColumna(c, Ta2->registros());

	Conj<Dato>::Iterador itcjd1 = cjd1.CrearIt();

	Dicc/*String*/<String, bool> ds = Dicc/*String*/<String, bool>();
	DiccNat<bool> dn = DiccNat<bool>();

	Conj<Dato> cjD = Conj<Dato>();

	if(!CampoT)
	{
		while(itcjd1.HaySiguiente())
		{
			ds.Definir(itcjd1.Siguiente().valorString(), true);
			itcjd1.Avanzar();
		}

		Conj<Dato>::Iterador itcjd2 = cjd2.CrearIt();

		while(itcjd2.HaySiguiente())
		{
			bool Def = ds.Definido(itcjd2.Siguiente().valorString());

			if(Def)
			{
				cjD.AgregarRapido(itcjd2.Siguiente());
			}
			itcjd2.Avanzar();
		}

	}else
	{
		while(itcjd1.HaySiguiente())
		{
			dn.Definir(itcjd1.Siguiente().valorNat(), true);
			itcjd1.Avanzar();
		}

		Conj<Dato>::Iterador itcjd2 = cjd2.CrearIt();

		while(itcjd2.HaySiguiente())
		{
			bool Def = dn.Definido(itcjd2.Siguiente().valorNat());

			if(Def)
			{
				cjD.AgregarRapido(itcjd2.Siguiente());
			}
			itcjd2.Avanzar();
		}
	}

	if(!cjD.EsVacio())
	{
		Conj<Dato>::Iterador its = cjD.CrearIt();

		while(its.HaySiguiente())
		{
			Registro regModelo = Dicc/*String*/<NombreCampo, Dato>().Definir(c, its.Siguiente());

			Conj<Conj<Registro>::Iterador> cjr1 = Ta1->buscarEnTabla(regModelo);
			Conj<Conj<Registro>::Iterador> cjr2 = Ta2->buscarEnTabla(regModelo);

			Registro r1 = cjr1.CrearIt().Siguiente().Siguiente();
			Registro r2 = cjr2.CrearIt().Siguiente().Siguiente();

			if(!CampoT)
			{
				Conj<Registro>::Iterador itnuevo = JoinC.AgregarRapido(r1.UnirRegistros(r2));
				JoinS.Definir(its.Siguiente().valorString(), itnuevo);

			}else
			{
				Conj<Registro>::Iterador itnuevo = JoinC.AgregarRapido(r1.UnirRegistros(r2));
				JoinN.Definir(its.Siguiente().valorNat(), itnuevo);
			}

			its.Avanzar();

		}
	}
	InfoJoin InfoJ = InfoJoin(Rcambios, CampoJ, CampoT, JoinS, JoinN, JoinC);
	this->Tablas.Significado(t1).Joins.Definir(t2, InfoJ);
	this->Tablas.Significado(t2).Joins.Definir(t1, InfoJ);
};

void Base::BorrarJoin(const NombreTabla t1, const NombreTabla t2)
{
	this->Tablas.Significado(t1).Joins.Borrar(t2);
	this->Tablas.Significado(t2).Joins.Borrar(t1);
};

Conj<Base::Registro> Base::Registros(const NombreTabla t)
{
	return this->Tablas.Significado(t).TActual.Registros_;
};

Conj<Base::Registro> Base::VistaJoin(const NombreTabla t1, const NombreTabla t2)
{
	InfoTabla* InfoT1 = this->Tablas.Significado(t1);
	Tabla* Ta1 = InfoT1->TActual;

	InfoTabla* InfoT2 = this->Tablas.Significado(t2);
	Tabla* Ta2 = InfoT2->TActual;

	InfoJoin* InfoJ = InfoT1->Joins.Significado(t2);

	NombreCampo c = InfoJ->CampoJ;

	if(InfoJ->Rcambios.EsVacia())
	{
		while(!InfoJ->Rcambios.EsVacia())
		{
			DatoCambio data = InfoJ->Rcambios.Primero();
			InfoJ->Rcambios.Fin();
			Registro r = data.Reg;

			Nat keyN;
			String keyS;

			if(InfoJ->CampoT)
			{
				keyN = r.Significado(c);
			}else{
				keyS = r.Significado(c);
			}

			if(data.Accion)
			{
				NombreTabla NomTOrigen = data.NomOrigen;
				Dicc<NombreCampo, Dato> regModelo = Dicc<NombreCampo, Dato>();
				regModelo.Definir(c, r.Significado(c));

				Registro ROtro = Dicc/*String*/<NombreCampo, Dato>();

				if(NomTOrigen==t1)
				{
					ROtro = Ta2->buscarEnTabla(regModelo).CrearIt().Siguiente().Siguiente();
				}else{
					ROtro = Ta1->buscarEnTabla(regModelo).CrearIt().Siguiente().Siguiente();
				}

				if(ROtro.CantClaves()!=0){
					Registro RNuevo = UnirRegistros(r, ROtro);

					if(InfoJ->CampoT)
					{
						Conj<Registro>::Iterador itnew = InfoJ->JoinC.AgregarRapido(RNuevo);
						InfoJ->JoinN.Definir(keyN,itnew);
					}else{
						Conj<Registro>::Iterador itnew = InfoJ->JoinC.AgregarRapido(RNuevo);
						InfoJ->JoinS.Definir(keyS,itnew);
					}
				}
			}else{

				if(InfoJ->CampoT)
				{
					Conj<Registro>::Iterador itcjr = InfoJ->JoinN.Significado(keyN);
					InfoJ->JoinN.Borrar(keyN);
					itcjr.EliminarSiguiente();
				}else{
					Conj<Registro>::Iterador itcjr = InfoJ->JoinS.Significado(keyS);
					InfoJ->JoinS.Borrar(keyS);
					itcjr.EliminarSiguiente();
				}
			}
		}
	}

	return InfoJ->JoinC;
};

int Base::CantidadDeAccesos(const NombreTabla t) const
{

	return this->Tablas.Significado(t).TActual.cantAccesos;
};

const NombreTabla Base::TablaMaxima()
{
	return this->TabMaxima.NomTabla;
};


Conj<Conj<Base::Registro>::Iterador> Base::Buscar(const Registro c, const NombreTabla t)
{
	return this->Tablas.Significado(t).TActual.buscarEnTabla(c);
};





}; // namespace aed2



#endif /* TABLA_H_ */