#include <stdio.h>
#include <ctime>
#include <time.h>
#include "fecha.hpp"
using namespace std;



Fecha::Fecha(int dia, int mes, int anno): dia_(dia), mes_(mes), anno_(anno){

	time_t tiempo_calendario = time(NULL);
	tm* tiempo_descompuesto = localtime(&tiempo_calendario);
	time_t mktime(tm*);
	if(dia_ == 0){
		dia_ = tiempo_descompuesto->tm_mday;
	}
	if(mes_ == 0){
		mes_ = tiempo_descompuesto->tm_mon + 1;
	}
	if(anno_ == 0){
		anno_ = tiempo_descompuesto->tm_year + 1900;
	}

	valida();
	
}

Fecha::Fecha(const char* cadena){
	sscanf(cadena, "%d/%d/%d", &dia_, &mes_, &anno_);

	time_t tiempo_calendario = time(NULL);
	tm* tiempo_descompuesto = localtime(&tiempo_calendario);
	time_t mktime(tm*);
	if(dia_ == 0){
		dia_ = tiempo_descompuesto->tm_mday;
	}
	if(mes_ == 0){
		mes_ = tiempo_descompuesto->tm_mon + 1;
	}
	if(anno_ == 0){
		anno_ = tiempo_descompuesto->tm_year + 1900;
	}

	valida();

}

void Fecha::valida(){
	int dias [] = {31,28,31,30,31,30,31,31,30,31,30,31};

	if(anno_ % 4 == 0 && (anno_ % 400 == 0 || anno_ % 100 != 0))
		dias[1] = 29;

	if (anno_ > AnnoMaximo)
		throw Invalida("Anno maximo superado");
	if (anno_ < AnnoMinimo)
		throw Invalida("Anno minimo superado");
	if(mes_ < 1 or mes_ > 12)
		throw Invalida("Mes invalido");
	if(dia_ < 1 or dia_ > dias[mes_ - 1]){
		throw Invalida("Dia incorrecto");
	}

}

Fecha& Fecha::operator ++(){
	*this += 1;
	return *this;
}

Fecha Fecha::operator ++(const int x){
	Fecha aux (*this);
	*this += 1;
	return aux;
}

Fecha& Fecha::operator --(){
	*this += - 1;
	return *this;
}

Fecha Fecha::operator --(const int x){
	Fecha aux (*this);
	*this += -1;
	return aux;
}

Fecha Fecha::operator + (int x) const{
	
    Fecha aux = *this;
	aux += x;
	return aux;
}

Fecha Fecha::operator - (int x) const{
	Fecha aux = *this;
	aux += -x;
	return aux;

}

Fecha& Fecha::operator +=(int x){
	tm datestruct = {0,0,0,0,0,0,0,0,0};

    datestruct.tm_mday = dia_+ x;
    datestruct.tm_mon = mes_ -1;
    datestruct.tm_year = anno_ - 1900;

    mktime(&datestruct);

    dia_ = datestruct.tm_mday;
    mes_ = datestruct.tm_mon + 1;
    anno_ = datestruct.tm_year + 1900;

    valida();

    return *this;
}

Fecha& Fecha::operator -=(int x){
	*this += -x;
	return *this;
}

int operator - (const Fecha& a, const Fecha& b){

	double dias;

	tm tiempoA = {0,0,0,0,0,0,0,0,0};
	tm tiempoB = {0,0,0,0,0,0,0,0,0};

	tiempoA.tm_mday = a.dia();
	tiempoA.tm_mon = a.mes() - 1;
	tiempoA.tm_year = a.anno() - 1900;

	tiempoB.tm_mday = b.dia();
	tiempoB.tm_mon = b.mes() - 1;
	tiempoB.tm_year = b.anno() - 1900;

	dias = difftime(mktime(&tiempoA), mktime(&tiempoB));
	return dias/86400;
}

bool operator < (const Fecha& a, const Fecha& b){
	int dif = a - b;
	if(dif < 0)
		return true;
	else
		return false;
}

bool operator <= (const Fecha& a, const Fecha& b){
	return !(b < a);
}

bool operator > (const Fecha& a, const Fecha& b){
	return b < a;
}

bool operator >= (const Fecha& a, const Fecha& b){
	return !(a < b);
}

bool operator == (const Fecha& a, const Fecha& b){
	int dif = a - b;
	if(dif == 0)
		return true;
	else
		return false;
}

bool operator != (const Fecha& a, const Fecha& b){
	return !(a == b);
}

/*ostream& operator << (ostream &o, const Fecha& a){
	tm tiempo = {0,0,0,0,0,0,0,0,0};
	const char* DIASEM [] = {"domingo", "lunes", "martes", "miércoles", "jueves", "viernes", "sábado"};
	const char* MES [] = {"enero","febrero","marzo","abril","mayo","junio","julio","agosto","septiembre","octubre","noviembre","diciembre"};

	tiempo.tm_mday = a.dia();
	tiempo.tm_mon = a.mes() - 1;
	tiempo.tm_year = a.anno() - 1900;

	mktime(&tiempo);

	o << DIASEM[tiempo.tm_wday] << " " << a.dia() << " de " << MES[tiempo.tm_mon] << " de " << a.anno() << endl;

	return o;

}*/

Fecha::operator const char*() const{
	static char cad[sizeof("miércoles DD de septiembre de AAAA")];
 	const char* DIASEM{nullptr};
 	const char* nombreMes{nullptr};

 	tm mk {0, 0, 0, dia_, mes_ - 1, anno_ - 1900, 0, 0 , 0};
 	mktime(&mk);

 	int diaSemana = mk.tm_wday;

 	switch (diaSemana){
	    case 1:
	        DIASEM = "lunes";    break;
	    case 2:
	        DIASEM = "martes";   break;
	    case 3:
	        DIASEM = "miércoles";    break;
	    case 4:
	        DIASEM = "jueves";   break;
	    case 5:
	        DIASEM = "viernes";    break;
	    case 6:
	        DIASEM = "sábado";   break;
	    case 0:
	        DIASEM = "domingo";    break;
	    }

	    switch (mes_){
	        case 1:
	        nombreMes = "enero";    break;
	    case 2:
	        nombreMes = "febrero";   break;
	    case 3:
	        nombreMes = "marzo";    break;
	    case 4:
	        nombreMes = "abril";   break;
	    case 5:
	        nombreMes = "mayo";    break;
	    case 6:
	        nombreMes = "junio";   break;
	    case 7:
	        nombreMes = "julio";    break;
	    case 8:
	        nombreMes = "agosto";    break;
	    case 9:
	        nombreMes = "septiembre";   break;
	    case 10:
	        nombreMes = "octubre";    break;
	    case 11:
	        nombreMes = "noviembre";   break;
	    case 12:
	        nombreMes = "diciembre";    break;
	    }

	    sprintf(cad, "%s %i de %s de %i", DIASEM, dia_, nombreMes, anno_ );

	   
	    return const_cast<char*> (cad);

}