#ifndef TARJETA_HPP_
#define TARJETA_HPP_
#include <iostream>
#include <cstdlib>
#include "fecha.hpp"
#include "cadena.hpp"
#include "usuario.hpp"

using namespace std;

class Usuario;

class Numero{
public:
	enum Razon{LONGITUD, DIGITOS, NO_VALIDO};
	class Incorrecto{
		const Razon r_;
	public:
		Incorrecto(const Razon& r): r_(r){}
		const Razon razon() const {return r_;}
	};
	Numero(const Cadena& num);
	operator const char*() const {return num_.c_str();}
private:
	Cadena num_;
	Cadena eliminarEspacios(Cadena& a);
	bool noDigitos(const Cadena& a);
};

bool operator < (const Numero& a, const Numero& b);

class Tarjeta{
public:
	class Caducada {
        const Fecha f;
    public:
        Caducada(const Fecha& a) : f(a) {}
        const Fecha cuando() const {return f;}
    };
	enum Tipo {VISA, Mastercard, Maestro, JCB, AmericanExpress};
	Tarjeta(const Tipo& marca, const Numero& num, Usuario& us, const Fecha& cad = Fecha());
	Tipo 	tipo() 		const	{return marca_;}
	Numero 	numero()	const	{return num_;}
	const Usuario* titular()	const	{return us_;}
	Fecha 	caducidad()	const	{return cad_;}
	Cadena 	titular_facial() const {return titular_facial_;}
	void	anular_titular();
	~Tarjeta();
private:
	Tarjeta(const Tarjeta& t);
	Tarjeta operator = (const Tarjeta& t);
	Tipo marca_;
	Numero num_;
	Usuario* us_;
	Fecha cad_;
	Cadena titular_facial_;
};

bool operator < (const Tarjeta& a, const Tarjeta& b);
ostream& operator << (ostream &o, const Tarjeta& a);
ostream& operator << (ostream &o, const Tarjeta::Tipo& a);



#endif