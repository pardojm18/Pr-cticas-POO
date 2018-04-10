#include <iostream>
#include "articulo.hpp"

using namespace std;

Articulo::Articulo(const Cadena& ref, const Cadena& tit, const Fecha& fpubl, double prec, unsigned sto){
	referencia_ = ref;
	titulo_ = tit;
	f_publi_ = fpubl;
	precio_ = prec;
	stock_ = sto;
}

ostream& operator << (ostream &o, const Articulo& a){
	char comillas = '"';
	o << "[" << a.referencia() << "] " << comillas << a.titulo() << comillas << ", " << a.f_publi().anno() << ". " << a.precio() << " €";
	return o;
}