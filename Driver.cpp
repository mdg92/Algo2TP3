#include "Driver.h"
#include <iostream>
using namespace aed2;

bool aed2::operator == (const aed2::Columna& c1, const aed2::Columna& c2)
{
  return c1.nombre == c2.nombre and c1.tipo == c2.tipo;
}

////////////////////////////////////////////////////////////////////////////////
// Dato
////////////////////////////////////////////////////////////////////////////////

Driver::Dato::Dato(const aed2::Nat& x)
  : tipo_( NAT ), nat_( x )
{}

Driver::Dato::Dato(const aed2::String& x)
  : tipo_( STR ), str_( x )
{}

bool Driver::Dato::esNat() const
{
  return tipo_ == NAT;
}

bool Driver::Dato::esString() const
{
  return tipo_ == STR;
}

TipoCampo Driver::Dato::tipo() const
{
  return tipo_;
}

const aed2::Nat& Driver::Dato::dameNat() const
{
  assert( esNat() );
  return nat_;
}

const aed2::String& Driver::Dato::dameString() const
{
  assert( esString() );
  return str_;
}

bool Driver::Dato::operator == (const Dato& otro) const
{
  return tipo_ == otro.tipo_ and (
    ( tipo_ == NAT and nat_ == otro.nat_ ) or
    ( tipo_ == STR and str_ == otro.str_ )
  );
}

bool Driver::Dato::operator != (const Dato& otro) const
{
  return not (*this == otro);
}

////////////////////////////////////////////////////////////////////////////////
// Base de datos
////////////////////////////////////////////////////////////////////////////////

Driver::Driver()
{
  base = Base();
}

Driver::~Driver()
{
  // // TODO ...
  // assert(false);
}

// Tablas

void Driver::crearTabla(const NombreTabla& nombre, const aed2::Conj<Columna>& columnas, const aed2::Conj<NombreCampo>& claves)
{
  std::cout << "creando tabla" << std::endl;

 Tabla* tabla = new Tabla(nombre, claves, columnas);
  std::cout << "creando tabla2" << std::endl;
  base.AgregarTabla(*tabla);
  std::cout << "creando tabla3" << std::endl;
}

void Driver::insertarRegistro(const NombreTabla& tabla, const Registro& registro)
{
  std::cout << "insertando" << std::endl;
  aed2::Registro r;
  auto it = registro.CrearIt();
  while (it.HaySiguiente())
    {
      Dato dato = it.SiguienteSignificado();
      if (dato.esNat()) {
        aed2::Dato d(dato.dameNat());
        r.Definir(it.SiguienteClave(), d);
      } else {
        aed2::Dato d(dato.dameString());
        r.Definir(it.SiguienteClave(), d);
      }
    }

  std::cout << "registro creado" << std::endl;
  base.InsertarEntrada(r, tabla);
}

void Driver::borrarRegistro(const NombreTabla& tabla, const NombreCampo& columna, const Dato& valor)
{
  // TODO ...
  // assert(false);
}

aed2::Conj<Columna> Driver::columnasDeTabla(const NombreTabla& tabla) const
{
  // TODO ...
  // assert(false);
}

aed2::Conj<NombreCampo> Driver::columnasClaveDeTabla(const NombreTabla& tabla) const
{
  // TODO ...
  // assert(false);
}

aed2::Conj<Driver::Registro> Driver::registrosDeTabla(const NombreTabla& tabla) const
{
  // TODO ...
  // assert(false);
}

aed2::Nat Driver::cantidadDeAccesosDeTabla(const NombreTabla& tabla) const
{
  // TODO ...
  // assert(false);
}

Driver::Dato Driver::minimo(const NombreTabla& tabla, const NombreCampo& columna) const
{
  // TODO ...
  // assert(false);
}

Driver::Dato Driver::maximo(const NombreTabla& tabla, const NombreCampo& columna) const
{
  // TODO ...
  // assert(false);
}

aed2::Conj<Driver::Registro> Driver::buscar(const NombreTabla& tabla, const Registro& criterio) const
{
  // TODO ...
  // assert(false);
}

aed2::Conj<NombreTabla> Driver::tablas() const
{
  aed2::Conj<NombreTabla> conjunto;
  auto it = base.DameTablas();
  while (it.HaySiguiente()) {
    conjunto.Agregar(it.Siguiente());
  }
  return conjunto;
};

NombreTabla Driver::tablaMaxima() const
{
  // TODO ...
  // assert(false);
}

// Indices

bool Driver::tieneIndiceNat(const NombreTabla& tabla) const
{
  // TODO ...
  // assert(false);
}

bool Driver::tieneIndiceString(const NombreTabla& tabla) const
{
  // TODO ...
  // assert(false);
}

NombreCampo Driver::campoIndiceNat(const NombreTabla& tabla) const
{
  // TODO ...
  // assert(false);
}

NombreCampo Driver::campoIndiceString(const NombreTabla& tabla) const
{
  // TODO ...
  // assert(false);
}

void Driver::crearIndiceNat(const NombreTabla& tabla, const NombreCampo& campo)
{
  // TODO ...
  // assert(false);
}

void Driver::crearIndiceString(const NombreTabla& tabla, const NombreCampo& campo)
{
  // TODO ...
  // assert(false);
}

// Joins

bool Driver::hayJoin(const NombreTabla& tabla1, const NombreTabla& tabla2) const
{
  // TODO ...
  // assert(false);
}

NombreCampo Driver::campoJoin(const NombreTabla& tabla1, const NombreTabla& tabla2) const
{
  // TODO ...
  // assert(false);
}

void Driver::generarVistaJoin(const NombreTabla& tabla1, const NombreTabla& tabla2, const NombreCampo& campo)
{
  // TODO ...
  // assert(false);
}

void Driver::borrarVistaJoin(const NombreTabla& tabla1, const NombreTabla& tabla2)
{
  // TODO ...
  // assert(false);
}

aed2::Conj<Driver::Registro> Driver::vistaJoin(const NombreTabla& tabla1, const NombreTabla& tabla2)/* const*/
{
  // TODO ...
  // assert(false);
}
