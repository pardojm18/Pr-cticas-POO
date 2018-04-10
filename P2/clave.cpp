#include <iostream>
#include <unistd.h>
#include "clave.hpp"

using namespace std;

Clave::Clave(char* con){
	if(strlen(con) < 5)
		throw Incorrecta(CORTA);
	Cadena aux (con);


}