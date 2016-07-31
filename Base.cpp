#include <ostream>
#include "Base.h"

using namespace std;
using namespace aed2;

Base::~Base() {}

Base::Base()
{
	this->TabMaxima = Tmax();
	this->Tablas = DiccLex<InfoTabla>();
};





const Conj<NombreTabla>::const_Iterador Base::DameTablas() const
{
	//return this->Tablas.claves().CrearIt();
	const Conj<NombreCampo>& conj = this->Tablas.DiccClaves();

	Conj<NombreCampo>::const_Iterador it = conj.CrearIt();

	return it;
};

Tabla& Base::DameTabla(const NombreTabla t) const
{
	return this->Tablas.Significado(t).TActual;
};

bool Base::HayJoin(const NombreTabla t1, const NombreTabla t2) const
{
	return this->Tablas.Significado(t1).Joins.Definido(t2) && this->Tablas.Significado(t1).Joins.Significado(t2).EnUso;
};

NombreCampo Base::CampoJoin(const NombreTabla t1, const NombreTabla t2) const
{
	return this->Tablas.Significado(t1).Joins.Significado(t2).CampoJ;
};

void Base::AgregarTabla(const Tabla& t)
{
	if(this->TabMaxima.NomTabla=="")
	{
		this->TabMaxima.NomTabla=t.nombre();
	}

	InfoTabla it = InfoTabla(t);
	this->Tablas.Definir(t.nombre(), it);
};

void Base::InsertarEntrada(const Registro& r, const NombreTabla& t)
{
	InfoTabla& InfoT = this->Tablas.Significado(t);

	InfoT.TActual.agregarRegistro(r);

	if(!InfoT.Joins.DiccClaves().EsVacio())
	{
		Registro r2=r;
		Conj<NombreTabla>::const_Iterador NomTab = InfoT.Joins.DiccClaves().CrearIt();

		while(NomTab.HaySiguiente()){

			InfoJoin& InfoJ = InfoT.Joins.Significado(NomTab.Siguiente());
			DatoCambio DatoC = DatoCambio(r2, t, true);
			InfoJ.Rcambios.AgregarAtras(DatoC);
			this->Tablas.Significado(NomTab.Siguiente()).Joins.Significado(t).Rcambios.AgregarAtras(DatoC);
			NomTab.Avanzar();

		}

	}

	if(InfoT.TActual.cantidadDeAccesos() > this->TabMaxima.Modif)
	{
		this->TabMaxima.Modif = InfoT.TActual.cantidadDeAccesos();
		this->TabMaxima.NomTabla = t;
	}

};

void Base::Borrar(const Registro cr, const NombreTabla t)
{

	InfoTabla& InfoT = this->Tablas.Significado(t);

	if(!InfoT.Joins.DiccClaves().EsVacio())
	{
		Conj<NombreTabla> conj = InfoT.Joins.DiccClaves();
		Conj<NombreTabla>::const_Iterador itNom = conj.CrearIt();

		while(itNom.HaySiguiente()){
			InfoJoin& InfoJ = InfoT.Joins.Significado(itNom.Siguiente());

			if(cr.Definido(InfoJ.CampoJ))
			{
				Conj<Conj<Registro>::const_Iterador> c = InfoT.TActual.buscarEnTabla(cr);
				Registro reg = c.CrearIt().Siguiente().Siguiente();
				DatoCambio DatoC = DatoCambio(reg, t, false);
				InfoJ.Rcambios.AgregarAtras(DatoC);
				this->Tablas.Significado(itNom.Siguiente()).Joins.Significado(t).Rcambios.AgregarAtras(DatoC);
			}else{

				Conj<Conj<Registro>::const_Iterador> eje = InfoT.TActual.buscarEnTabla(cr);
				Conj<Conj<Registro>::const_Iterador>::Iterador itReg = eje.CrearIt();

				while(itReg.HaySiguiente())
				{
					DatoCambio DatoC(itReg.Siguiente().Siguiente(), t, false);
					InfoJ.Rcambios.AgregarAtras(DatoC);
					this->Tablas.Significado(itNom.Siguiente()).Joins.Significado(t).Rcambios.AgregarAtras(DatoC);
					itReg.Avanzar();
				}
			}
			itNom.Avanzar();
		}
	}

	InfoT.TActual.borrarRegistro(cr);

	if(InfoT.TActual.cantidadDeAccesos() > this->TabMaxima.Modif)
	{
		this->TabMaxima.NomTabla = t;
		this->TabMaxima.Modif = InfoT.TActual.cantidadDeAccesos();
	}
};

void Base::GenerarVistaJoin(const NombreTabla t1, const NombreTabla t2, const NombreCampo c)
{
	Lista<DatoCambio> Rcambios = Lista<DatoCambio>();

	Tipo CampoT = this->Tablas.Significado(t1).TActual.tipoCampo(c);

	NombreCampo CampoJ = c;

	DiccLex<Conj<Registro>::Iterador> JoinS = DiccLex<Conj<Registro>::Iterador>();
	DiccNat<Conj<Registro>::Iterador> JoinN = DiccNat<Conj<Registro>::Iterador>();

	Conj<Registro> JoinC = Conj<Registro>();

	Tabla Ta1 = this->Tablas.Significado(t1).TActual;
	Tabla Ta2 = this->Tablas.Significado(t2).TActual;

	Conj<Dato> cjd1 = Ta1.dameColumna(c, Ta1.registros());
	Conj<Dato> cjd2 = Ta2.dameColumna(c, Ta2.registros());

	Conj<Dato>::Iterador itcjd1 = cjd1.CrearIt();

	DiccLex<bool> ds = DiccLex<bool>();
	DiccNat<bool> dn = DiccNat<bool>();

	Conj<Dato> cjD = Conj<Dato>();

	if(!CampoT)
	{
		while(itcjd1.HaySiguiente())
		{
			ds.Definir(itcjd1.Siguiente().valorString(), true);
			itcjd1.Avanzar();
		}

		Conj<Dato>::Iterador itcjd2 = cjd2.CrearIt();

		while(itcjd2.HaySiguiente())
		{
			bool Def = ds.Definido(itcjd2.Siguiente().valorString());

			if(Def)
			{
				cjD.AgregarRapido(itcjd2.Siguiente());
			}
			itcjd2.Avanzar();
		}

	}else
	{
		while(itcjd1.HaySiguiente())
		{
			dn.Definir(itcjd1.Siguiente().valorNat(), true);
			itcjd1.Avanzar();
		}

		Conj<Dato>::Iterador itcjd2 = cjd2.CrearIt();

		while(itcjd2.HaySiguiente())
		{
			bool Def = dn.Definido(itcjd2.Siguiente().valorNat());

			if(Def)
			{
				cjD.AgregarRapido(itcjd2.Siguiente());
			}
			itcjd2.Avanzar();
		}
	}

	if(!cjD.EsVacio())
	{
		Conj<Dato>::Iterador its = cjD.CrearIt();

		while(its.HaySiguiente())
		{
			Registro regModelo = Registro();

			regModelo.Definir(c, its.Siguiente());

			Conj<Conj<Registro>::const_Iterador> cjr1 = Ta1.buscarEnTabla(regModelo);
			Conj<Conj<Registro>::const_Iterador> cjr2 = Ta2.buscarEnTabla(regModelo);

			Registro r1 = cjr1.CrearIt().Siguiente().Siguiente();
			Registro r2 = cjr2.CrearIt().Siguiente().Siguiente();

			if(!CampoT)
			{
				Conj<Registro>::Iterador itnuevo = JoinC.AgregarRapido(r1.UnirRegistros(c, r2));
				JoinS.Definir(its.Siguiente().valorString(), itnuevo);

			}else
			{
				Conj<Registro>::Iterador itnuevo = JoinC.AgregarRapido(r1.UnirRegistros(c, r2));
				JoinN.Definir(its.Siguiente().valorNat(), itnuevo);
			}

			its.Avanzar();

		}
	}
	InfoJoin InfoJ1 = InfoJoin(CampoJ, CampoT, JoinS, JoinN, JoinC, true);
	InfoJoin InfoJ2 = InfoJoin(CampoJ, CampoT, JoinS, JoinN, JoinC, this->Tablas.Significado(t2).Joins.Definido(t1));
	this->Tablas.Significado(t1).Joins.Definir(t2, InfoJ1);
	this->Tablas.Significado(t2).Joins.Definir(t1, InfoJ2);


};

void Base::BorrarJoin(const NombreTabla t1, const NombreTabla t2)
{
	if(this->HayJoin(t2, t1)){
		this->Tablas.Significado(t1).Joins.Significado(t2).EnUso = false;
	}else{
		this->Tablas.Significado(t1).Joins.Borrar(t2);
		this->Tablas.Significado(t2).Joins.Borrar(t1);
	}
};

const Conj<Registro>& Base::Registros(const NombreTabla t) const
{
	return this->Tablas.Significado(t).TActual.registros();
};

Conj<Registro>& Base::VistaJoin(const NombreTabla t1, const NombreTabla t2)
{
	InfoTabla& InfoT1 = this->Tablas.Significado(t1);
    Tabla & Ta1 = InfoT1.TActual;

	InfoTabla& InfoT2 = this->Tablas.Significado(t2);
    Tabla & Ta2 = InfoT2.TActual;

	InfoJoin& InfoJ = InfoT1.Joins.Significado(t2);
	InfoJoin& InfoJ2 = InfoT2.Joins.Significado(t1);

	NombreCampo c = InfoJ.CampoJ;




		while(!InfoJ.Rcambios.EsVacia())
		{
			DatoCambio data = InfoJ.Rcambios.Primero();
			//std::cout << "Primero Rcambios: " << InfoJ.Rcambios.Primero().Reg.Significado("DNI").valorNat() << std::endl;
			//std::cout << "Primero Rcambios Accion: " << InfoJ.Rcambios.Primero().Accion << std::endl;

			InfoJ.Rcambios.Fin();
			InfoJ2.Rcambios.Fin();
			Registro r = data.Reg;

			Nat keyN;
			String keyS;

			if(InfoJ.CampoT)
			{
				keyN = r.Significado(c).valorNat();
			}else{
				keyS = r.Significado(c).valorString();
			}

			if(data.Accion)
			{
				NombreTabla NomTOrigen = data.NomOrigen;
				Registro regModelo = Registro();
				regModelo.Definir(c, r.Significado(c));

				Registro ROtro = Registro();

				if(NomTOrigen==t1)
				{


					if(Ta2.buscarEnTabla(regModelo).CrearIt().HaySiguiente()){
						ROtro = Ta2.buscarEnTabla(regModelo).CrearIt().Siguiente().Siguiente();
					}


				}else{

					if(Ta1.buscarEnTabla(regModelo).CrearIt().HaySiguiente()){
						ROtro = Ta1.buscarEnTabla(regModelo).CrearIt().Siguiente().Siguiente();
					}

				}

				if(!ROtro.Campos().EsVacio()){

					Registro RNuevo = r.UnirRegistros(c, ROtro);

					if(InfoJ.CampoT)
					{

						if(!InfoJ.JoinC.Pertenece(RNuevo)){
							Conj<Registro>::Iterador itnew = InfoJ.JoinC.AgregarRapido(RNuevo);
							InfoJ.JoinN.Definir(keyN,itnew);
						}

					}else{

						if(!InfoJ.JoinC.Pertenece(RNuevo)){
							Conj<Registro>::Iterador itnew = InfoJ.JoinC.AgregarRapido(RNuevo);
							InfoJ.JoinS.Definir(keyS,itnew);
						}
					}
				}
			}else{

				if(InfoJ.CampoT)
				{

					//std::cout << "JoinC antes de Borrar: " << InfoJ.JoinC.Cardinal() << std::endl;
					if(InfoJ.JoinN.Definido(keyN)){

						InfoJ.JoinN.Significado(keyN).EliminarSiguiente();
						InfoJ.JoinN.Borrar(keyN);

					}
					//std::cout << "JoinC despues de Borrar: " << InfoJ.JoinC.Cardinal() << std::endl;

//


				}else{


					InfoJ.JoinS.Significado(keyS).EliminarSiguiente();
					InfoJ.JoinS.Borrar(keyS);


				}
			}
		}

	//std::cout << "Base::VistaJoin: " << InfoJ.JoinC.Cardinal() << std::endl;
	return InfoJ.JoinC;
};

int Base::CantidadDeAccesos(const NombreTabla t) const
{
	return this->Tablas.Significado(t).TActual.cantidadDeAccesos();
};

const NombreTabla Base::TablaMaxima() const
{
	return this->TabMaxima.NomTabla;
};


Conj<Conj<Registro>::const_Iterador> Base::Buscar(const Registro c, const NombreTabla t) const
{

	return this->Tablas.Significado(t).TActual.buscarEnTabla(c);
};

/*
int main(){
	Base b;
	Conj<NombreCampo> claves;
	claves.AgregarRapido("Campo1");
	Registro reg = Registro();
	Dato d1 = Dato(1);
	reg.Definir("Campo1", d1);
	reg.Definir("Campo2", d1);
	Tabla t = Tabla("Tabla1", claves, reg);
	b.AgregarTabla(t);

	std::cout << b.DameTablas().Siguiente() << std::endl;
	assert(false);

}
*/
