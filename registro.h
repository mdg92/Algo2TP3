#ifndef REG_H_
#define	REG_H_

#include <iostream>
#include "DiccLex.h"
#include "DiccNat.h"
#include "Dato.h"
#include "Tipos.h"


namespace aed2
{


class Registro
{
  public:
	Registro();
	Registro& operator = (const Registro& otro){
		Conj<String>::const_Iterador claves= otro.Campos().CrearIt();
		while(claves.HaySiguiente()){
			this->Definir(claves.Siguiente(),otro.Significado(claves.Siguiente()));
			claves.Avanzar();
		}
	};
  	//DiccLex();
  	//~DiccLex();
  	//DiccLex(const Registro&);
  	void Definir(NombreCampo, Dato);
  	bool Definido(NombreCampo);
  	bool Definido(NombreCampo) const;
  	void Borrar(NombreCampo);
  	const Conj<NombreCampo>& Campos() const;
  	NombreCampo Maximo();
  	NombreCampo Minimo();
  	Dato& Significado(NombreCampo) const;
  	NombreCampo Maximo() const;
  	NombreCampo Minimo() const;
  	bool BorrarPreg(Registro);
  	bool BorrarPreg(Registro) const;
  	bool EnTodos(NombreCampo, Conj<Registro>);
    bool CoincideAlguno(const Conj<NombreCampo>&, const Registro&)const;
    bool CoincidenTodos(const Conj<NombreCampo>&,  const Registro&) const;
  	Registro UnirRegistros(NombreCampo,  Registro);
  	Registro CombinarTodos(NombreCampo, Conj<Registro>);
  	bool operator==(const Registro)const;
  private:
  	DiccLex<Dato> base;


};
};

#endif // DICCLEX_H_
