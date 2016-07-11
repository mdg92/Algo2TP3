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
	std::cout << "Driver::Driver()" << std::endl;
  this->base = Base();
}

Driver::~Driver()
{
  // // TODO ...
  // assert(false);
}

// Tablas

//void Driver::crearTabla(const NombreTabla& nombre, const aed2::Conj<Columna>& columnas, const aed2::Conj<NombreCampo>& claves)
//{
//	std::cout << "Driver::crearTabla" << std::endl;
// Tabla tabla = Tabla(nombre, claves, columnas);
// std::cout << "1" << std::endl;
//  base.AgregarTabla(tabla);
//  std::cout << "2" << std::endl;
//
//}

void Driver::crearTabla(const NombreTabla& nombre, const aed2::Conj<Columna>& columnas, const aed2::Conj<NombreCampo>& claves)
{
	std::cout << "Driver::crearTabla" << std::endl;
	//creamos con columnas un Registro
	Conj<Columna>::const_Iterador itcol=columnas.CrearIt();
	aed2::Registro reg;
	aed2::Dato d1(1);
	aed2::Dato d2("a");

	while(itcol.HaySiguiente()){
		if(itcol.Siguiente().tipo==0){
			reg.Definir(itcol.Siguiente().nombre,d1);
		}else{
			reg.Definir(itcol.Siguiente().nombre,d2);
		}
		itcol.Avanzar();
	}
	//assert(reg.Significado("nombre").EsString());
	aed2::Tabla tabla(nombre, claves, reg);
//	std::cout << "aa" << std::endl;
	base.AgregarTabla(tabla);


}

void Driver::insertarRegistro(const NombreTabla& tabla, const Registro& registro)
{
	std::cout << "Driver::insertarRegistro" << std::endl;
	//Paso registro de Driver a aed2 para poder usarlo.
  aed2::Registro r;
  Dicc<NombreCampo, Dato>::const_Iterador it = registro.CrearIt();
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
      it.Avanzar();
    }

  std::cout << "Registro creado. " << std::endl;
  base.InsertarEntrada(r, tabla);
  std::cout << "Insertado en la tabla." << std::endl;
}

void Driver::borrarRegistro(const NombreTabla& tabla, const NombreCampo& columna, const Dato& valor)
{
	std::cout << "Driver::borrarRegistro" << std::endl;
  assert(false);
}

aed2::Conj<Columna> Driver::columnasDeTabla(const NombreTabla& tabla) const
{
	std::cout << "Driver::columnasDeTabla " << std::endl;
	Conj<Columna> c = Conj<Columna>();
	//Creo las columnas a partir de campos() y tipoCampo().
	Conj<NombreCampo> conj =  this->base.DameTabla(tabla).campos();
	Conj<NombreCampo>::const_Iterador cit = conj.CrearIt();
	while(cit.HaySiguiente()){
		Columna col;
		col.nombre = cit.Siguiente();
		TipoCampo tc;
		if(this->base.DameTabla(tabla).tipoCampo(cit.Siguiente())){
			tc = NAT;
		}else{
			tc = STR;
		}
		col.tipo = tc;

		c.AgregarRapido(col);
		cit.Avanzar();
	}

	return c;
}

aed2::Conj<NombreCampo> Driver::columnasClaveDeTabla(const NombreTabla& tabla) const
{
	std::cout << "Driver::columnasClaveDeTabla" << std::endl;
	return this->base.DameTabla(tabla).claves();
}

aed2::Conj<Driver::Registro> Driver::registrosDeTabla(const NombreTabla& tabla) const
{
	std::cout << "Driver::registrosDeTabla" << std::endl;
	Conj<aed2::Registro>::const_Iterador c = this->base.DameTabla(tabla).registros().CrearIt();
	Conj<Driver::Registro> res;

	//Paso los registros de aed2 a Driver para poder devolverlos.

	while (c.HaySiguiente())
	{
		aed2::Registro reg = c.Siguiente();
		Conj<NombreCampo>::Iterador cr = reg.Campos().CrearIt();
		Driver::Registro r;

		while(cr.HaySiguiente()){

			if(reg.Significado(cr.Siguiente()).EsNat()){
				r.Definir(cr.Siguiente(), Driver::Dato(reg.Significado(cr.Siguiente()).valorNat()));
			}else if(reg.Significado(cr.Siguiente()).EsString()){
				r.Definir(cr.Siguiente(), Driver::Dato(reg.Significado(cr.Siguiente()).valorString()));
			}
		}

		res.AgregarRapido(r);

	}

  return res;
}

aed2::Nat Driver::cantidadDeAccesosDeTabla(const NombreTabla& tabla) const
{
	std::cout << "Driver::cantidadDeAccesosDeTabla" << std::endl;
	return this->base.DameTabla(tabla).cantidadDeAccesos();
}

Driver::Dato Driver::minimo(const NombreTabla& tabla, const NombreCampo& columna) const
{
	std::cout << "Driver::minimo" << std::endl;

	//Paso el dato de tipo aed2 a tipo Driver

	if(this->base.DameTabla(tabla).minimo(columna).EsNat()){
		return Driver::Dato(this->base.DameTabla(tabla).minimo(columna).valorNat());
	}else{
		return Driver::Dato(this->base.DameTabla(tabla).minimo(columna).valorString());
	}

}

Driver::Dato Driver::maximo(const NombreTabla& tabla, const NombreCampo& columna) const
{
	std::cout << "Driver::maximo" << std::endl;

	//Paso el dato de tipo aed2 a tipo Driver

	if(this->base.DameTabla(tabla).maximo(columna).EsNat()){
		return Driver::Dato(this->base.DameTabla(tabla).maximo(columna).valorNat());
	}else{
		return Driver::Dato(this->base.DameTabla(tabla).maximo(columna).valorString());
	}

}

aed2::Conj<Driver::Registro> Driver::buscar(const NombreTabla& tabla, const Registro& criterio) const
{
	std::cout << "Driver::buscar" << std::endl;

	aed2::Registro r;
	Dicc<NombreCampo, Dato>::const_Iterador it = criterio.CrearIt();

	//Paso los registros de aed2 a Driver para poder devolverlos.

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


	Conj<Conj<aed2::Registro>::Iterador>::Iterador c = this->base.Buscar(r, tabla).CrearIt();
	Conj<Driver::Registro> res;

	while (c.HaySiguiente())
	{
		aed2::Registro reg = c.Siguiente().Siguiente();
		Conj<NombreCampo>::Iterador cr = reg.Campos().CrearIt();
		Driver::Registro r;

		while(cr.HaySiguiente()){
			if(reg.Significado(cr.Siguiente()).EsNat()){
				r.Definir(cr.Siguiente(),  Driver::Dato(reg.Significado(cr.Siguiente()).valorNat()));
			}else if(reg.Significado(cr.Siguiente()).EsString()){
				r.Definir(cr.Siguiente(),  Driver::Dato(reg.Significado(cr.Siguiente()).valorString()));
			}

		}

		res.AgregarRapido(r);

	}

  return res;

}

aed2::Conj<NombreTabla> Driver::tablas() const
{
	std::cout << "Driver::tablas() " << std::endl;

	//Paso los NombreTabla del iterador devuelto por DameTablas a un conjunto.

	aed2::Conj<NombreTabla>::const_Iterador it = this->base.DameTablas();
	aed2::Conj<NombreTabla> conjunto;

	if(it.HaySiguiente()){
	std::cout << "it.Siguiente() de DameTablas() en tablas(): " << it.Siguiente() << std::endl;
	}

	while (it.HaySiguiente()) {
		conjunto.Agregar(it.Siguiente());
		it.Avanzar();
  }
  return conjunto;
};

NombreTabla Driver::tablaMaxima() const
{
	std::cout << "Driver::tablaMaxima" << std::endl;

	return this->base.TablaMaxima();
}

// Indices

bool Driver::tieneIndiceNat(const NombreTabla& tabla) const
{
	std::cout << "Driver::tieneIndiceNat" << std::endl;
	Conj<NombreCampo>::const_Iterador it = this->base.DameTabla(tabla).indices().CrearIt();
	bool res;
	while(it.HaySiguiente()){
		res = this->base.DameTabla(tabla).tipoCampo(it.Siguiente());
	}

	return res;
}

bool Driver::tieneIndiceString(const NombreTabla& tabla) const
{
	std::cout << "Driver::tieneIndiceString" << std::endl;
	Conj<NombreCampo>::const_Iterador it = this->base.DameTabla(tabla).indices().CrearIt();
	bool res;
	while(it.HaySiguiente()){
		res = !this->base.DameTabla(tabla).tipoCampo(it.Siguiente());
	}

	return res;
}

NombreCampo Driver::campoIndiceNat(const NombreTabla& tabla) const
{
	std::cout << "Driver::campoIndiceNat" << std::endl;
	Conj<NombreCampo>::const_Iterador it = this->base.DameTabla(tabla).indices().CrearIt();
	NombreCampo res;
	while(it.HaySiguiente()){
		if(this->base.DameTabla(tabla).tipoCampo(it.Siguiente())){
			res = it.Siguiente();
		}
	}

	return res;
}

NombreCampo Driver::campoIndiceString(const NombreTabla& tabla) const
{
	std::cout << "Driver::campoIndiceString" << std::endl;
	Conj<NombreCampo>::const_Iterador it = this->base.DameTabla(tabla).indices().CrearIt();
	NombreCampo res;
	while(it.HaySiguiente()){
		if(!this->base.DameTabla(tabla).tipoCampo(it.Siguiente())){
			res = it.Siguiente();
		}
	}

	return res;
}

void Driver::crearIndiceNat(const NombreTabla& tabla, const NombreCampo& campo)
{
	std::cout << "Driver::crearIndiceNat" << std::endl;
  	this->base.DameTabla(tabla).indexar(campo);
}

void Driver::crearIndiceString(const NombreTabla& tabla, const NombreCampo& campo)
{
	std::cout << "Driver::crearIndiceString" << std::endl;
	this->base.DameTabla(tabla).indexar(campo);
}

// Joins

bool Driver::hayJoin(const NombreTabla& tabla1, const NombreTabla& tabla2) const
{
	std::cout << "Driver::hayJoina" << std::endl;
  return this->base.HayJoin(tabla1, tabla2);
}

NombreCampo Driver::campoJoin(const NombreTabla& tabla1, const NombreTabla& tabla2) const
{
	std::cout << "Driver::campoJoin" << std::endl;
	return this->base.CampoJoin(tabla1, tabla2);
}

void Driver::generarVistaJoin(const NombreTabla& tabla1, const NombreTabla& tabla2, const NombreCampo& campo)
{
	std::cout << "Driver::generarVistaJoin" << std::endl;
	this->base.GenerarVistaJoin(tabla1, tabla2, campo);
}

void Driver::borrarVistaJoin(const NombreTabla& tabla1, const NombreTabla& tabla2)
{
	std::cout << "Driver::borrarVistaJoin" << std::endl;
	this->base.BorrarJoin(tabla1, tabla2);
}

aed2::Conj<Driver::Registro> Driver::vistaJoin(const NombreTabla& tabla1, const NombreTabla& tabla2)/* const*/
{
	std::cout << "Driver::vistaJoin" << std::endl;

	//Paso los registros de aed2 a Driver para poder devolverlos.

  	Conj<aed2::Registro>::Iterador c = this->base.VistaJoin(tabla1, tabla2).CrearIt();
	Conj<Driver::Registro> res;

	while (c.HaySiguiente())
	{
		aed2::Registro reg = c.Siguiente();
		Conj<NombreCampo>::Iterador cr = reg.Campos().CrearIt();
		Driver::Registro r;

		while(cr.HaySiguiente()){
			if(reg.Significado(cr.Siguiente()).EsNat()){
				r.Definir(cr.Siguiente(),  Driver::Dato(reg.Significado(cr.Siguiente()).valorNat()));
			}else if(reg.Significado(cr.Siguiente()).EsString()){
				r.Definir(cr.Siguiente(),  Driver::Dato(reg.Significado(cr.Siguiente()).valorString()));
			}

		}

		res.AgregarRapido(r);

	}

  return res;


}
