#ifndef TABLA_H_
#define TABLA_H_

#include "Dato.h"
#include "Tipos.h"
#include "DiccNat.h"
#include "DiccLex.h"
#include "aed2/Dicc.h"
#include "aed2/Conj.h"
#include "aed2/TiposBasicos.h"
#include "registro.h"

namespace aed2 {

class Tabla
{
  public:

    typedef Conj<Conj<Registro >::Iterador> CjDeIteradores;
	
		NombreTabla nombre() const;

    const Conj<NombreCampo> claves() const;

    const Conj<NombreCampo> indices() const;

    const Conj<NombreCampo> campos()const;

    const Tipo tipoCampo(NombreCampo) const;

    const Conj<Registro>& registros() const;

    Nat cantidadDeAccesos() const;

    bool compatible(const Registro reg)const;

    Tabla(const NombreTabla& nombre, const aed2::Conj<NombreCampo >& claves, const Registro& columnas);
    //Tabla(const NombreTabla& nombre, const aed2::Conj<NombreCampo >& claves, const Conj<Columna>& columnas);

    ~Tabla();

   void agregarRegistro(const Registro&);

    void borrarRegistro(const Registro);

    void indexar(const NombreCampo);

    bool puedoInsertar(const Registro) const;

    const Dato& minimo(const NombreCampo) const;

    const Dato& maximo(const NombreCampo) const;

    bool puedeIndexar(const NombreCampo)const;

    bool hayCoincidencia(const Registro, const Conj<NombreCampo>, const Conj<Registro > )const;

    Conj<Conj<Registro >::const_Iterador > coincidencias(const Registro, const Conj<Registro>&) const;

    Conj<Registro> combinarRegistros(const NombreCampo, const Conj<Registro>, const Conj<Registro>);

    const Conj<Dato> dameColumna(const NombreCampo, const Conj<Registro>)const;

    bool mismosTipos(const Registro) const;

    Conj<Conj<Registro>::const_Iterador> buscarEnTabla(const Registro)const;

  private:
    //Tabla(const Tabla& t);
    NombreTabla Nombre_;
	Conj<Registro> Registros_;
	DiccLex<Tipo> Campos_;//String
	Conj<NombreCampo > Claves_;
	struct IndiceNat{
		   NombreCampo CampoI;
		   bool EnUso;
		   Dato Min;
		   Dato Max;
		   IndiceNat():CampoI(""), EnUso(false), Min(0),Max(0){};
	};
	struct IndiceString{
		   NombreCampo CampoI;
		   bool EnUso;
		   Dato Min;
		   Dato Max;
		   IndiceString():CampoI(""), EnUso(false), Min(""),Max(""){};
	};
	IndiceString IndiceS;
	DiccLex<CjDeIteradores> IndiceDS;//DiccString
	IndiceNat IndiceN;
	DiccNat<CjDeIteradores> IndiceDN; //DiccNat
	struct Acceso{
		   Conj<Conj<Registro >::Iterador >::Iterador S;
		   Conj<Conj<Registro >::Iterador >::Iterador N;
		   //<>
	};
	NombreCampo CampoR;
	DiccNat<Acceso> ConsultaN; //Nat
	DiccLex<Acceso> ConsultaS;//String
	int cantAccesos;

}; // class Tabla

};

#endif /* TABLA_H_ */
