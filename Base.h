#ifndef BASE_H_
#define BASE_H_

#include "Dato.h"
#include "Tipos.h"
#include "Tabla.h"
#include "DiccNat.h"
#include "DiccLex.h"
#include "registro.h"
#include "aed2/Lista.h"
#include "aed2/Dicc.h"
#include "aed2/Conj.h"
#include "aed2/TiposBasicos.h"

namespace aed2 {

class Base
{
	public:

	//typedef aed2::Dicc/*String*/<NombreCampo, Dato> Registro;

	Base();

	~Base();

	Conj<NombreTabla>::Iterador DameTablas() const;

	Tabla& DameTabla(const NombreTabla) const;

	bool HayJoin(const NombreTabla, const NombreTabla) const;

	NombreCampo CampoJoin(const NombreTabla, const NombreTabla) const;

	void AgregarTabla(const Tabla&);

	void InsertarEntrada(const Registro&, const NombreTabla&);

	void Borrar(const Registro, const NombreTabla);

	void GenerarVistaJoin(const NombreTabla, const NombreTabla, const NombreCampo);

	void BorrarJoin(const NombreTabla, const NombreTabla);

	const Conj<Registro>& Registros(const NombreTabla) const;

	Conj<Registro>& VistaJoin(const NombreTabla, const NombreTabla);

	int CantidadDeAccesos(const NombreTabla) const;

	const NombreTabla TablaMaxima() const;

	Conj<Conj<Registro>::Iterador> Buscar(const Registro, const NombreTabla) const;



	private:

	struct Tmax{
			NombreTabla NomTabla;
			Nat Modif;
			Tmax(): NomTabla(""), Modif(0){};
		};

	struct DatoCambio{
		Registro Reg;
		NombreTabla NomOrigen;
		bool Accion;
		DatoCambio(Registro r, NombreTabla n, bool b): Reg(r), NomOrigen(n), Accion(b) {};
	};

	struct InfoJoin{
		Lista<struct DatoCambio> Rcambios;
		NombreCampo CampoJ;
		Tipo CampoT;
		DiccLex<Conj<Registro>::Iterador> JoinS;
		DiccNat<Conj<Registro>::Iterador> JoinN;
		Conj<Registro> JoinC;
		InfoJoin(NombreCampo nc,
				Tipo tc,
				DiccLex<Conj<Registro>::Iterador> ds,
				DiccNat<Conj<Registro>::Iterador> dn,
				Conj<Registro> cr): Rcambios(Lista<struct DatoCambio>()), CampoJ(nc), CampoT(tc), JoinS(ds), JoinN(dn), JoinC(cr) {};
	};
	
	struct InfoTabla{
		Tabla TActual;
		DiccLex<struct InfoJoin> Joins;
		InfoTabla(Tabla t): TActual(t), Joins(DiccLex<InfoJoin>()){};
	};



	Tmax TabMaxima;
	DiccLex<InfoTabla> Tablas;


}; // class Base

};


#endif /* TABLA_H_ */
