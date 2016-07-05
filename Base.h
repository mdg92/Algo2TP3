#ifndef BASE_H_
#define BASE_H_

#include "Dato.h"
#include "Tipos.h"
#include "Tabla.h"
#include "aed2/Dicc.h"
#include "aed2/Conj.h"
#include "aed2/TiposBasicos.h"

namespace aed2
{

class Base
{
	public:

	typedef aed2::Dicc<NombreCampo, Dato> Registro;



	Base();

	Conj<NombreTabla>::Iterador DameTablas();

	Tabla DameTabla(const NombreTabla);

	bool HayJoin(const NombreTabla, const NombreTabla);

	NombreCampo CampoJoin(const NombreTabla, const NombreTabla);

	void AgregarTabla(const Tabla);

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
			Tmax(): NomTabla("Ninguna"), Modif(0){};
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
		Dicc/*Nat*/<Nat, Conj<Registro>::Iterador> JoinN;
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
	//Hacer...
};

Conj<NombreTabla>::Iterador Base::DameTablas()
{
	//return Base::Tablas.Claves();
};

Tabla Base::DameTabla(const NombreTabla t)
{
	return this->Tablas.Significado(t).TActual;
};

bool Base::HayJoin(const NombreTabla t1, const NombreTabla t2)
{
	return this->Tablas.Significado(t1).Joins.Definido(t2) && this->Tablas.Significado(t2).Joins.Definido(t1);
};

NombreCampo Base::CampoJoin(const NombreTabla t1, const NombreTabla t2)
{
	return this->Tablas.Significado(t1).Joins.Significado(t2).CampoJ;
};

void Base::AgregarTabla(const Tabla t)
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

			InfoJoin InfoJ = InfoT->Joins.Significado(NomTab.Siguiente());
			DatoCambio DatoC = DatoCambio(r, t, true);
			InfoJ.Rcambios.AgregarAtras(DatoC);
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
				InfoJ->Rcambios.AgregarAtras(DatoC);
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

void Base::GenerarVistaJoin(const NombreTabla, const NombreTabla, const NombreCampo)
{
	//Hacer...
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

Conj<Base::Registro> Base::VistaJoin(const NombreTabla, const NombreTabla)
{
	//Hacer...
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
