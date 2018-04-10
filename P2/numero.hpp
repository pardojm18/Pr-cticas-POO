#include <iostream>
#include "cadena.hpp"

using namespace std;

class Numero{
public:
	enum Razon{LONGITUD, DIGITOS, NO_VALIDO}
	class Incorrecto{
		const Razon r_;
	public:
		Incorrecto(const Razon& r): r_(r){}
		Razon razon() const {return r_;}
	};
	Numero(const Cadena& num);
	operator const char*() const {return num_;}
	friend bool operator < (const Numero& a, const Numero& b);
private:
	Cadena num_;
	Cadena eliminarEspacios(Cadena& a);
	bool noDigitos(const Cadena& a)
};

bool operator < (const Numero& a, const Numero& b)	{return a.num_ < b.num_;}