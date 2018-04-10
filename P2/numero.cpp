#include <iostream>
#include "numero.hpp"
#include "lunch.cpp"

using namespace std;

Numero::Numero(const Cadena& num): num_(num){
	num_ = eliminarEspacios(num_);
	if(!noDigitos(num_))
		throw Incorrecto(DIGITOS);
	if(num_.length() < 13 or num_.length() > 19)
		throw Incorrecto(LONGITUD);
	if(!(lunch(num_)))
		throw Incorrecto(NO_VALIDO);
}

Cadena Numero::eliminarEspacios(Cadena& a){
	size_t i, j = 0;
	char* aux = new char[a.length()];

	for(i = 0; i < a.length(); i++){
		if(a[i] != ' '){
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