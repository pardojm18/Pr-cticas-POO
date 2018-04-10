#ifndef FECHA_HPP_
#define FECHA_HPP_

#include <iostream>

using namespace std;

class Fecha{
public:
	
	class Invalida {
        const char* porque_;
    public:
        Invalida(const char* porque) : porque_(porque) {}
        const char* por_que() const { return porque_; }
    };
	explicit Fecha(int dia = 0, int mes = 0, int anno = 0);
	Fecha(const char* cadena);
	Fecha& operator ++();
	Fecha operator ++(const int x);
	Fecha& operator --();
	Fecha operator --(const int x);
	Fecha operator +(int x) const;
	Fecha operator -(int x) const;
	Fecha& operator +=(int x);
	Fecha& operator -=(int x);
	int dia() const	{return dia_;}
	int mes() const {return mes_;}
	int anno() const {return anno_;}
	char* cadena() const;
	static const int AnnoMinimo = 1902;
	static const int AnnoMaximo = 2037;
private:
	int dia_;
	int mes_;
	int anno_;
	void valida();
};

int operator - (const Fecha& a, const Fecha& b);
bool operator < (const Fecha& a, const Fecha& b);
bool operator <= (const Fecha& a, const Fecha& b);
bool operator > (const Fecha& a, const Fecha& b);
bool operator >= (const Fecha& a, const Fecha& b);
bool operator == (const Fecha& a, const Fecha& b);
bool operator != (const Fecha& a, const Fecha& b);
ostream& operator << (ostream &o, const Fecha& a);
istream& operator >> (istream &is, Fecha& a);
bool validaIs(int& dia, int& mes, int& anno);

#endif