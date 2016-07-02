#ifndef TABLA_H_
#define TABLA_H_

#include "Dato.h"
#include "Tipos.h"
#include "aed2/Dicc.h"
#include "aed2/Conj.h"
#include "aed2/TiposBasicos.h"

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

    /**
     * Esta clase representa un registro, es decir, un mapeo de nombres de columna a valores.
     */
    typedef aed2::Dicc<NombreCampo, Dato> Registro;

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


    aed2::Conj<NombreCampo> campos(const NombreTabla& tabla) const;

    aed2::TipoCampo tipoCampo(const NombreTabla& tabla) const;

    /**
     * Devuelve el conjunto de registros de la tabla.
     *
     * PRE:.
     */
    aed2::Conj<Registro > registros() const;

    aed2::Nat cantidadDeAccesos(const NombreTabla& tabla) const;

    void agregarRegistro(const Registro& reg);

    Tabla(const NombreTabla& nombre, const aed2::Conj<NombreCampo >& claves, const Registro& columnas);

    Tabla(const Tabla& t);

    /**
     * destruye el contenido de la Tabla, liberando la memoria dinámica alocada.
     */
    ~Tabla();

    /**
     * Inserta un registro en tabla.
     *
     * PRE: idem especificación TAD Driver :: insertarEntrada
     */
    void insertarRegistro(const NombreTabla& tabla, const  Registro& registro);

    /**
     * Borra una serie de registros de  tabla.
     *
     * PRE:
     *
     *  - 'columna' es una columna de dicha tabla.
     *  - el tipo de 'valor' coincide con el tipo de dicha columna.
     */
    void borrarRegistro(const NombreTabla& tabla, const NombreCampo& columna, const Dato& valor);


    void indexar(const NombreTabla& tabla) const;

    aed2::Nat cantidadDeAccesosDeTabla(const NombreTabla& tabla) const;



    /**
     * Devuelve el minimo valor de una columna de la tabla.
     *
     * PRE:
     *  - .
     *  - idem especificación TAD Tabla :: minimo
     */
    Dato minimo(const NombreTabla& tabla, const NombreCampo& columna) const;

    /**
     * Devuelve el maximo valor de una columna de la tabla.
     *
     * PRE:
     *  -.
     *  - idem especificación TAD Tabla :: maximo
     */
    Dato maximo(const NombreTabla& tabla, const NombreCampo& columna) const;


  // Indices

    /**
     * Indica si una tabla tiene índice definido sobre un campo de tipo Nat.
     *
     * PRE:.
     */
    bool tieneIndiceNat(const NombreTabla& tabla) const;

    /**
     * Indica si una tabla tiene índice definido sobre un campo de tipo String.
     *
     * PRE: .
     */
    bool tieneIndiceString(const NombreTabla& tabla) const;

    /**
     * Devuelve el campo sobre el cuál está definido el índice de tipo Nat.
     *
     * PRE:
     *  - .
     *  - existe un índice de tipo Nat en dicha tabla.
     */
    const NombreCampo& campoIndiceNat(const NombreTabla& tabla) const;

    /**
     * Devuelve el campo sobre el cuál está definido el índice de tipo String.
     *
     * PRE:
     *  - '.
     *  - existe un índice de tipo String en dicha tabla.
     */
    const NombreCampo& campoIndiceString(const NombreTabla& tabla) const;

    /**
     * Crea un índicede tipo Nat sobre un campo de la tabla.
     *
     * PRE:
     *  - .
     *  - no existe un índice de tipo Nat en dicha tabla.
     *  - 'campo' pertenece a las columnas de dicha tabla, y la columna es de tipo Nat.
     */
    void crearIndiceNat(const NombreTabla& tabla, const NombreCampo& campo);

    /**
     * Crea un índicede tipo String sobre un campo de la tabla.
     *
     * PRE:
     *  - .
     *  - no existe un índice de tipo String en dicha tabla.
     *  - 'campo' pertenece a las columnas de dicha tabla, y la columna es de tipo String.
     */
    void crearIndiceString(const NombreTabla& tabla, const NombreCampo& campo);

  // Joins

    /**
     * Indica si existe un join entre 'tabla1' y 'tabla2'.
     */
    bool hayJoin(const NombreTabla& tabla1, const NombreTabla& tabla2) const;

    /**
     * Devuelve el campo sobre el cuál se hace el join entre dos tablas.
     *
     * PRE: existe un Join entre las tablas 'tabla1' y 'tabla2'.
     */
    const NombreCampo& campoJoin(const NombreTabla& tabla1, const NombreTabla& tabla2) const;


  private:
	NombreTabla Nombre_;
	aed2::Conj<Registro > Registros_;
	aed2::Dicc<const NombreCampo&, aed2::Tipo > Campos_;//String
	aed2::Conj<NombreCampo > Claves_;
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
