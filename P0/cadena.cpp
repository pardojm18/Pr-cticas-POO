#include "stdio.h"
#include "cadena.hpp"

using namespace std;

Cadena::Cadena(const size_t& tam, const char& cad){
	s_ = new char[tam + 1];
	tam_ = tam;

	size_t i = 0;

	for(i = 0; i < tam_; i++)
		s_[i] = cad;

	s_[i] = '\0';
}

Cadena::Cadena(const char* cad, size_t n){

	if(n > strlen(cad))
		tam_ = strlen(cad);
	else if(n == 0)
		tam_ = 0;
	else
		tam_ = n;

	s_ = new char[tam_ + 1];

	size_t i;

	for(i = 0; i < tam_; i++)
		s_[i] = cad[i];

	s_[i] = '\0';

}

Cadena::Cadena(const Cadena& cad, size_t ini, size_t lon){

	size_t ipos;

	if(lon == npos){
		ipos = ini;
		tam_ = cad.tam_ - ini;
	}else if(ini > cad.tam_-1){
		throw out_of_range("Posicion inicial mayor que la longitud");
	}else if(lon > cad.tam_ - ini){
		ipos = ini;
		tam_ = cad.tam_ - ini;
	}else if (lon == 0){
		tam_ = 0;
		ipos = 0;
	}else{
		tam_ = lon;
		ipos = ini;
	}

	s_ = new char[tam_ + 1];
	size_t i;

	for(i = 0; i < tam_; i++){
		s_[i] = cad.s_[ipos];
		ipos++;
	}
	s_[i] = '\0';

}

void Cadena::operator = (const Cadena& a){
	delete [] s_;

	tam_ = a.tam_;

	s_ = new char[tam_ + 1];

	size_t i;

	for(i = 0; i < tam_; i++)
		s_[i] = a.s_[i];
	s_[i] = '\0';
}

Cadena::operator const char*() const{
	return s_;
}

char Cadena::at(size_t n) const{
	if(n >= tam_)
		throw(out_of_range("Fuera de rango"));
	return s_[n];
}
char& Cadena::at(size_t n){
	if(n >= tam_)
		throw(out_of_range("Fuera de rango"));
	return s_[n];
}

void Cadena::operator +=(const Cadena& a){

	char* aux = new char[tam_];

	for(size_t i = 0; i < tam_+1; i++)
		aux[i] = s_[i];
	delete[] s_;

	tam_ = tam_ + a.tam_;
	s_ = new char[tam_ + 1];

	strcpy(s_, aux);
	strcat(s_, a.s_);

}

Cadena Cadena::substr(const size_t& ini, const size_t& lon) const{
	if (ini > tam_ or lon > (tam_ - ini))
		throw(out_of_range("Fuera de rango"));

	char* aux = new char[lon];
	size_t j = ini;

	for(size_t i = 0; i < lon; i++){
		aux[i] = s_[j];
		j++;
	}

	Cadena ab(aux);
	return ab;

}

Cadena::~Cadena(){
	delete[] s_;
	tam_ = 0;
}

Cadena operator +(const Cadena& a, const Cadena& b){
	Cadena aux = a;
	aux +=b;
	return aux;
}

bool operator < (const Cadena& a, const Cadena& b){
	int valor = strcmp(a.c_str(), b.c_str());
	if(valor < 0)
		return true;
	return false;
}

bool operator >= (const Cadena& a, const Cadena& b){
	return !(a < b);
}

bool operator > (const Cadena& a, const Cadena& b){
	return b < a;
}

bool operator <= (const Cadena& a, const Cadena& b){
	return !(b < a);
}

bool operator == (const Cadena& a, const Cadena& b){
	if(a.length() != b.length())
		return false;
	int contA = 0;
	int contB = 0;

	for(size_t i = 0; i < a.length(); i++)
		contA += a[i];
	for(size_t i = 0; i < b.length(); i++)
		contB += b[i];

	if(contA != contB)
		return false;

	return true;
}

bool operator != (const Cadena& a, const Cadena& b){
	return !(a == b);
}