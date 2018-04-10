#include <iomanip>
#include <functional>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>


#include "tarjeta.hpp"

using namespace std;

bool luhn(const Cadena& num);
class Usuario;

Numero::Numero(const Cadena& num){
	num_ = num;
	num_ = eliminarEspacios(num_);
	if(noDigitos(num_))
		throw Incorrecto(DIGITOS);
	if(num_.length() < 13 or num_.length() > 19)
		throw Incorrecto(LONGITUD);
	if(!(luhn(num_)))
		throw Incorrecto(NO_VALIDO);
}

struct EsBlanco : public unary_function<char, bool> {
	bool operator()(const char& c) const {return isspace(c);} 
};

struct EsDigito : public unary_function<char, bool> {
	bool operator()(const char& c) const {return isdigit(c);}
};

Cadena Numero::eliminarEspacios(Cadena& a){
	vector<char> aux;
	for(Cadena::const_iterator i = a.begin(); i != a.end(); ++i)
		aux.push_back(*i);


	aux.erase(remove_if(aux.begin(), aux.end(), EsBlanco()), aux.end());

	char* c = new char [aux.size() + 1];
	int j = 0;

	for(vector<char>::const_iterator i = aux.begin(); i != aux.end(); ++i){
		c[j] = *i;
		j++;
	}
	c[j] = '\0';
	

	return Cadena(c);

}



bool Numero::noDigitos(const Cadena& a){
	return find_if(a.begin(), a.end(), not1(EsDigito())) != a.end();
}

Tarjeta::Tarjeta(const Tipo& marca, const Numero& num, Usuario& us, const Fecha& cad):marca_(marca), num_(num), us_(&us), cad_(cad), titular_facial_(us.nombre() + " " + us.apellidos()){
	
	if(cad < Fecha())
		throw Caducada(cad);

	us_->es_titular_de(*this);

}

void Tarjeta::anular_titular(){
	us_ = nullptr;
}

Tarjeta::~Tarjeta(){
	if(us_ != nullptr)
		us_->no_es_titular_de(*this);
	
}

ostream& operator << (ostream &o, const Tarjeta& t){
	o << t.tipo() << endl;
	o << t.numero() << endl;
	o << t.titular_facial() << endl;
	o << setfill('0');
	o << "Caduca: " << setw(2) << t.caducidad().mes() << "/" << t.caducidad().anno() %100 << endl;

	return o;
}

ostream& operator << (ostream &o, const Tarjeta::Tipo& a){
	switch(a){
		case Tarjeta::VISA: o << "VISA";	break;
		case Tarjeta::Mastercard: o << "Mastercard";	break;
		case Tarjeta::Maestro: o << "Maestro";	break;
		case Tarjeta::JCB: o << "JCB";	break;
		case Tarjeta::AmericanExpress: o << "AmericanExpress";	break;
	}

	return o;
}

bool operator < (const Numero& a, const Numero& b){
	return (strcmp(a,b) < 0);
}

bool operator < (const Tarjeta& a, const Tarjeta& b){
	return a.numero() < b.numero();
}