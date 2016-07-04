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

	Conj<NombreTabla>::Iterador Tablas();

	Tabla DameTabla(const NombreTabla);

	bool HayJoin(const NombreTabla, const NombreTabla);

	Conj<NombreCampo>::Iterador CampoJoin();

	void AgregarTabla(const Tabla);

	void InsertarEntrada(const Registro, const NombreTabla);

	void Borrar(const Registro, const NombreTabla);

	void GenerarVistaJoin(const NombreTabla, const NombreTabla, const NombreCampo);

	void BorrarJoin(const NombreTabla, const NombreTabla);

	Conj<Registro> Registros(const NombreTabla);

	Conj<Registro> VistaJoin(const NombreTabla, const NombreTabla);

	Nat CantidadDeAccesos(const NombreTabla) const;

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

	Tmax TablaMaxima;
	Dicc/*String*/<NombreTabla, InfoTabla> Tablas;


}; // class Base


Base::Base()
{
	//Hacer...
};

Conj<NombreTabla>::Iterador Tablas();
{
	//Hacer...
};

Tabla DameTabla(const NombreTabla);
{
	//Hacer...
};

bool HayJoin(const NombreTabla, const NombreTabla);
{
	//Hacer...
};

Conj<NombreCampo>::Iterador CampoJoin();
{
	//Hacer...
};

void AgregarTabla(const Tabla);
{
	//Hacer...
};

void InsertarEntrada(const Registro, const NombreTabla);
{
	//Hacer...
};

void Borrar(const Registro, const NombreTabla);
{
	//Hacer...
};

void GenerarVistaJoin(const NombreTabla, const NombreTabla, const NombreCampo);
{
	//Hacer...
};

void BorrarJoin(const NombreTabla, const NombreTabla);
{
	//Hacer...
};

Conj<Registro> Registros(const NombreTabla);
{
	//Hacer...
};

Conj<Registro> VistaJoin(const NombreTabla, const NombreTabla);
{
	//Hacer...
};

Nat CantidadDeAccesos(const NombreTabla) const;
{
	//Hacer...
};

const NombreTabla TablaMaxima();
{
	//Hacer...
};

const NombreTabla EncontrarMaximo(const NombreTabla, const Conj<NombreTabla>);
{
	//Hacer...
};

Conj<Conj<Registro>::Iterador> Buscar(const Registro, const NombreTabla);
{
	//Hacer...
};



}; // namespace aed2






#endif /* TABLA_H_ */
