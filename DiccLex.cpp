#include "DiccLex.h"
#include <iostream>
using namespace aed2;
int main(){
	DiccLex<Nat> p;
	Nat i=2;
	p.Definir("ahora",i);
	std::cout<<p.Definido("ahora")<<"\n";
	p.Definir("ahora1",i);
	p.Definir("ahra",i);
	p.Definir("aora",i);
	p.Definir("hora",i);
	p.Definir("sahora",i);
	p.Definir("afhora1",i);
	p.Definir("ahrsa",i);
	p.Definir("aorag",i);
	p.Definir("hogra",i);
	p.Definir("ahoraew",i);
	p.Definir("ahorewa1",i);
	p.Definir("ahqra",i);
	p.Definir("aoeqra",i);
	p.Definir("horqweqwa",i);
	p.Definir("ahwqora",i);
	p.Definir("ahoqra1",i);
	p.Definir("ahrewqqa",i);
	p.Definir("aoweqra",i);
	p.Definir("hoewqra",i);
	p.Definir("ahoreea",i);
	p.Definir("ahqweora1",i);
	i++;
	p.Definir("ahra",i);
	p.Definir("aoeqwra",i);
	p.Definir("horasda",i);
	p.Definir("ahorsada",i);
	p.Definir("ahosara1",i);
	p.Definir("ahrasda",i);
	p.Definir("aorsdaa",i);
	p.Definir("zoradsa",i);
	p.Definir("Horadsa",i);
	std::cout<<p.Minimo()<<"\n";
	std::cout<<p.Maximo()<<"\n";
	std::cout<<p.DiccClaves()<<"\n";
	p.Borrar("ahra");
	std::cout<<p.DiccClaves()<<"\n";
	std::cout<<p.Significado(p.Minimo())<<"\n";
	return 3;


};