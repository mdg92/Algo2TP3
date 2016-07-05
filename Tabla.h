#ifndef TABLA_H_
#define TABLA_H_

#include "Dato.h"
#include "Tipos.h"
#include "aed2/Dicc.h"
#include "aed2/Conj.h"
#include "aed2/TiposBasicos.h"
#include "Registro.h"

namespace aed2
{

class Tabla
{
  public:

	const NombreTabla& nombre()const;

    typedef aed2::Conj<aed2::Conj<Registro& >::Iterador > CjDeIteradores;

    const Conj<const NombreCampo&>& claves() const;

    const aed2::Conj<NombreCampo > indices() const;

    const Conj<const NombreCampo&> campos()const;

    const Tipo& tipoCampo(const NombreCampo& c) const;

    Conj<Registro& >& registros();

    const Nat& cantidadDeAccesos() const;

    Tabla(const NombreTabla& nombre, const Conj<const NombreCampo& >& claves, const Registro& columnas);

    Tabla(const Tabla& t);

    ~Tabla();

    void agregarRegistro(const Registro& reg);

    void borrarRegistro(const Registro& registro_);

    void indexar(const NombreCampo& c);

    const bool puedoInsertar(const Registro& r)const;

    const bool compatible(const Registro& r)const;

    const Dato& minimo(const NombreCampo& columna) const;

    const Dato& maximo(const NombreCampo& columna) const;

    const bool puedeIndexar(const NombreCampo& c)const;

    const bool hayCoincidencia(const Registro& reg, const Conj<const NombreCampo& >& cjcampo, const Conj<Registro& >& cjreg)const;

    Conj<Conj<Registro& >::Iterador > coincidencias(const Registro& , Conj<Registro& >)const;

    Conj<Registro& >& combinarRegistros(const NombreCampo& campo, const Conj<Registro& >& cr1, const Conj<Registro& >& cr2);

    Conj<Dato > dameColumna(const NombreCampo& campo, const Conj<Registro& > cr)const;

    const bool mismosTipos(const Registro& reg)const;

    Conj<Conj<Registro& >::Iterador > buscarEnTabla(const Registro& criterio)const;



  private:
	NombreTabla Nombre_;
	Conj<Registro& > Registros_;
	Dicc/*String*/<const NombreCampo&, Tipo > Campos_;//String
	Conj<const NombreCampo& > Claves_;
	struct IndiceNat{
		   NombreCampo CampoI;
		   bool EnUso;
		   Dato Min;
		   Dato Max;
		   IndiceNat(NombreCampo nom="a"):CampoI(nom), EnUso(false), Min(1),Max(1){};
	};
	struct IndiceString{
		   NombreCampo CampoI;
		   bool EnUso;
		   Dato Min;
		   Dato Max;
		   IndiceString(NombreCampo nom="a"):CampoI(nom), EnUso(false), Min("a"),Max("a"){};
	};
	IndiceString IndiceS;
	Dicc/*String*/<String, Tabla::CjDeIteradores > IndiceDS;//DiccString
	IndiceNat IndiceN;
	Dicc/*Nat*/<Nat, Tabla::CjDeIteradores > IndiceDN; //DiccNat
	struct Acceso{
		   aed2::Conj<aed2::Conj<Registro& >::Iterador >::Iterador S;
		   aed2::Conj<aed2::Conj<Registro& >::Iterador >::Iterador N;
		   //<>
	};
	NombreCampo CampoR;
	Dicc/*Nat*/<Nat, Acceso> ConsultaN; //Nat
	Dicc/*String*/<String, Acceso> ConsultaS;//String
	Nat cantAccesos;
}; // class Tabla

}; // namespace aed2






#endif /* TABLA_H_ */
