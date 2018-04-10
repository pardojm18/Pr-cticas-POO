#include <iomanip>
#include <functional>
#include <iostream>
#include <algorithm>
#include <stdexcept>

#include "tarjeta.hpp"

using namespace std;

bool luhn(const Cadena& num);
class Usuario;

Numero::Numero(const Cadena& num): num_(num){
	num_ = eliminarEspacios(num_);
	if(num_.length() < 13 or num_.length() > 19)
		throw Incorrecto(LONGITUD);
	if(!noDigitos(num_))
		throw Incorrecto(DIGITOS);
	if(!(luhn(num_)))
		throw Incorrecto(NO_VALIDO);
}

Cadena Numero::eliminarEspacios(Cadena& a){
	size_t i, j = 0;
	char* aux = new char[a.length()];

	for(i = 0; i < a.length(); i++){
		if(isdigit(a[i])){
			aux[j] = a[i];
			j++;
		}
	}
	return aux;
}

bool Numero::noDigitos(const Cadena& a){
	for(size_t i = 0; i < a.length(); i++){
		if((int)a[i] > 57 or (int)a[i] < 48){
			return false;
		}
	}

	return true;
}

Tarjeta::Tarjeta(const Tipo& marca, const Numero& num, Usuario& us, const Fecha& cad):marca_(marca), num_(num), us_(&us), cad_(cad){
	
	if(cad < Fecha())
		throw Caducada(cad);

	titular_facial_ = (us.nombre());
	titular_facial_ += " ";
	titular_facial_ += us.apellidos();
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