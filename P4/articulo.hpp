#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_
#include <iostream>
#include <set>
#include "fecha.hpp"
#include "cadena.hpp"

using namespace std;

class Autor{
public:
	Autor(const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion): nombre_(nombre), apellidos_(apellidos), direccion_(direccion) {}
	const Cadena& nombre() const {return nombre_;}
	const Cadena& apellidos() const {return apellidos_;}
	const Cadena& direccion() const {return direccion_;}
private:
	Cadena nombre_;
	Cadena apellidos_;
	Cadena direccion_;
};

class Articulo{
public:
	class Autores_vacios{};
	typedef set<Autor*> Autores;
	explicit Articulo(const Autores& autores, const Cadena& ref, const Cadena& tit, const Fecha& fpubl, double prec);
	//Observadores
	Cadena referencia() const {return referencia_;}
	Cadena titulo() const {return titulo_;}
	Fecha f_publi() const {return f_publi_;}
	double precio() const {return precio_;}
	//unsigned stock() const {return stock_;}
	//Funciones P4
	virtual void impresion_especifica(ostream& o) const = 0;
	const Autores& autores() const {return autores_;}
	//Modificadores
	double& precio() {return precio_;}
	//unsigned& stock() {return stock_;}
	virtual ~Articulo() {}
private:
	Cadena referencia_;
	Cadena titulo_;
	Fecha f_publi_;
	double precio_;
	//unsigned stock_;
	Autores autores_;
};

ostream& operator << (ostream &o, const Articulo& a);

class ArticuloAlmacenable : public Articulo{
	unsigned stock_;
public:
	ArticuloAlmacenable(const Autores& autores, const Cadena& ref, const Cadena& tit, const Fecha& fpubl, double prec, unsigned sto = 0): 
		Articulo(autores, ref, tit, fpubl, prec), stock_(sto){}
	unsigned stock() const {return stock_;}
	unsigned& stock() {return stock_;}
};

class Libro: public ArticuloAlmacenable{
public:
	Libro(const Autores& autores, const Cadena& ref, const Cadena& tit, const Fecha& fpubl, double prec, unsigned n_pag, unsigned sto = 0) : 
		ArticuloAlmacenable(autores, ref, tit, fpubl, prec, sto), n_pag_(n_pag) {}
	unsigned n_pag() const {return n_pag_;}
	void impresion_especifica(ostream& o) const;
private:
	unsigned n_pag_;
};

class Cederron: public ArticuloAlmacenable{
public:
	Cederron(const Autores& autores, const Cadena& ref, const Cadena& tit, const Fecha& fpubl, double prec, unsigned tam, unsigned sto = 0) : 
		ArticuloAlmacenable(autores, ref, tit, fpubl, prec, sto), tam_(tam) {}
	unsigned tam() const {return tam_;}
	void impresion_especifica(ostream& o) const;
private:
	unsigned tam_;
};

class LibroDigital : public Articulo{
public:
	LibroDigital(const Autores& autores, const Cadena& ref, const Cadena& tit, const Fecha& fpubl, double prec, const Fecha& f_expir) :
		Articulo(autores, ref, tit, fpubl, prec), f_expir_(f_expir) {}
	void impresion_especifica(ostream& o) const;
	Fecha f_expir() const {return f_expir_;}
private:
	Fecha f_expir_;		
};

#endif