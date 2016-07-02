#ifndef DATO_H_
#define DATO_H_

#include <cassert>
#include "Tipos.h"
#include "aed2\Dicc.h"
#include "aed2\Conj.h"
#include "aed2\TiposBasicos.h"

namespace aed2
{
typedef bool Tipo;

class Dato{
public:
	Dato(const String& x);
	Dato(const Nat& x);
	~Dato();
	const Tipo tipo()const;
	const Nat& valorNat()const;
	const String& valorString()const;
	const bool mismoTipo(const Dato& b)const;
	const bool EsString()const;
	const bool EsNat()const;
	//	const Dato min()const;
//	const Dato min(aed2::Conj<Dato& >& cjd)const;
//	const Dato max(aed2::Conj<Dato& >& cjd)const;
	const bool operator <=(const Dato& a)const;
	const bool operator ==(const Dato& b)const;


//	const Tipo tipo()const;
//	const Nat& valorNat(const Dato& a)const;
//	const String& valorString(const Dato& a)const;
//	const bool mismoTipo(const Dato& a, const Dato& b)const;
//	const bool EsString(const Dato& a)const;
//	const bool EsNat(const Dato a)const;
//	const Dato min(aed2::Conj<Dato& >& cjd)const;
//	const Dato max(aed2::Conj<Dato& >& cjd)const;
//	const bool operator <=(const Dato& a)const;


private:
	 Tipo tipo_;
	 String valorString_;
	 Nat valorNat_;
};


}; // fin del namespace aed2
#endif /* DATO_H_ */
