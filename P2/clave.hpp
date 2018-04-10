#include <iostream>
#include "cadena.hpp"

class Clave{
public:
	Clave(char* con);
	enum Razon {CORTA, ERROR_CRYPT};
	class Incorrecta {
        const Razon razon_;
    public:
        Incorrecta(const Razon raz) : razon_(raz) {}
        Razon razon() {return razon_;}
    };

private:
	Cadena contra;
};