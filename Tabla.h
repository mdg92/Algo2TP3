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
//	/**
//     * Esta clase representa un dato, que puede tomar valores de String o de Nat.
//     */
//    class Dato
//    {
//      public:
//
//        Dato(const aed2::Nat& x);
//        Dato(const aed2::String& x);
//
//        bool esNat() const{
//        	return this->tipo()==0;
//        };
//        bool esString() const{
//        	return this->tipo()==1;
//        };
//        TipoCampo tipo() const{
//        	return tipo_;
//        };
//
//        const aed2::Nat& dameNat() const{
//        	return this->nat_;
//        };
//        const aed2::String& dameString() const{
//        	return this->str_;
//        };
//
//        bool operator == (const Dato& otro) const;
//        bool operator != (const Dato& otro) const;
//
//      private:
//
//        TipoCampo tipo_;
//
//        aed2::Nat nat_;
//        aed2::String str_;
//    };

	const NombreTabla& nombre()const;
    /**
     * Esta clase representa un registro, es decir, un mapeo de nombres de columna a valores.
     */

    typedef aed2::Conj<aed2::Conj<Registro >::Iterador > CjDeIteradores;

    /**
     * Devuelve el conjunto de columnas clave de la tabla.
     *
     * PRE:.
     */
    aed2::Conj<NombreCampo> claves(const NombreTabla& tabla) const;

    /**
     * Devuelve el conjunto de columnas de la tabla.
     *
     * PRE: .
     */

    const aed2::Conj<NombreCampo > indices() const;


    Conj<const NombreCampo&> campos()const;

    const Tipo& tipoCampo(const NombreCampo& c) const;

    /**
     * Devuelve el conjunto de registros de la tabla.
     *
     * PRE:.
     */
    Conj<Registro> registros()const;

    const Nat& cantidadDeAccesos(const NombreTabla& tabla) const;

    void agregarRegistro(const Registro& reg);

    Tabla(const NombreTabla& nombre, const aed2::Conj<NombreCampo >& claves, const Registro& columnas);

    Tabla(const Tabla& t);

    /**
     * destruye el contenido de la Tabla, liberando la memoria dinámica alocada.
     */
    ~Tabla();


    /**
     * Borra una serie de registros de  tabla.
     *
     * PRE:
     *
     *  - 'columna' es una columna de dicha tabla.
     *  - el tipo de 'valor' coincide con el tipo de dicha columna.
     */
    void borrarRegistro(const Registro& registro_);


    void indexar(const NombreCampo& c);

    aed2::Nat cantidadDeAccesosDeTabla(const NombreTabla& tabla) const;



    /**
     * Devuelve el minimo valor de una columna de la tabla.
     *
     * PRE:
     *  - .
     *  - idem especificación TAD Tabla :: minimo
     */
    const Dato& minimo(const NombreCampo& columna) const;

    /**
     * Devuelve el maximo valor de una columna de la tabla.
     *
     * PRE:
     *  -.
     *  - idem especificación TAD Tabla :: maximo
     */
    const Dato& maximo(const NombreCampo& columna) const;

    const bool puedoInsertar(const Registro& r)const;

    const bool puedoIndexar(const NombreCampo& c)const;

    const bool hayCoincidencia(const Registro& reg, const Conj<NombreCampo > cjcampo, const Conj<Registro& > cjreg)const;

   Conj<Conj<Registro >::Iterador > coincidencias(const Registro& crit, const Conj<Registro >);

    Conj<Registro& > combinarRegistros(const NombreCampo& campo, const Conj<Registro& > cr1, const Conj<Registro& > cr2);


    const bool mismosTipos(const Registro& reg)const;

    Conj<Conj<Registro >::Iterador > buscarEnTabla(const Registro& criterio)const;

  private:
	NombreTabla Nombre_;
	Conj<Registro > Registros_;
	Dicc<const NombreCampo&, Tipo > Campos_;//String
	Conj<NombreCampo > Claves_;
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
	aed2::Dicc<aed2::String, Tabla::CjDeIteradores > IndiceDS;//DiccString
	IndiceNat IndiceN;
	aed2::Dicc<aed2::Nat, Tabla::CjDeIteradores > IndiceDN; //DiccNat
	struct Acceso{
		   aed2::Conj<aed2::Conj<Registro >::Iterador >::Iterador S;
		   aed2::Conj<aed2::Conj<Registro >::Iterador >::Iterador N;
		   //<>
	};
	NombreCampo CampoR;
	aed2::Dicc<aed2::Nat, Acceso> ConsultaN; //Nat
	aed2::Dicc<aed2::String, Acceso> ConsultaS;//String
	int cantAccesos;
}; // class Tabla

}; // namespace aed2






#endif /* TABLA_H_ */
