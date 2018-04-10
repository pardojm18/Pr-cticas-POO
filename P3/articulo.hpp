#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_
#include <iostream>
#include "fecha.hpp"
#include "cadena.hpp"

using namespace std;

class Articulo{
public:
	explicit Articulo(const Cadena& ref, const Cadena& tit, const Fecha& fpubl, double prec, unsigned sto);
	//Observadores
	Cadena referencia() const {return referencia_;}
	Cadena titulo() const {return titulo_;}
	Fecha f_publi() const {return f_publi_;}
	double precio() const {return precio_;}
	unsigned stock() const {return stock_;}
	//Modificadores
	double& precio() {return precio_;}
	unsigned& stock() {return stock_;}
private:
	Cadena referencia_;
	Cadena titulo_;
	Fecha f_publi_;
	double precio_;
	unsigned stock_;
};

ostream& operator << (ostream &o, const Articulo& a);

#endif