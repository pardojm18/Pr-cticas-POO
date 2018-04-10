#ifndef CADENA_HPP_
#define CADENA_HPP_

#include <iostream>
#include <cstring>

class Cadena{
public:
	Cadena(const size_t& tam = 0, const char& cad = ' ');
	Cadena(const char* cad, size_t ini = -1);
	Cadena(const Cadena& cad, size_t ini = 0, size_t lon = -1);
	void operator = (const Cadena& a);
	char operator [] (const size_t& n) const {return s_[n];}
	char& operator [] (const size_t& n) {return s_[n];}
	char at(size_t n) const;
	char& at(size_t n);
	operator const char*() const;
	size_t length()	const {return tam_;}
	void operator +=(const Cadena& a);
	Cadena substr(const size_t& ini, const size_t& lon) const;
	const char*c_str() const {return s_;}
	~Cadena();
	static const int npos = -1;
private:
	char* s_;
	size_t tam_;
};

Cadena operator +(const Cadena& a, const Cadena& b);
bool operator < (const Cadena& a, const Cadena& b);
bool operator >= (const Cadena& a, const Cadena& b);
bool operator > (const Cadena& a, const Cadena& b);
bool operator <= (const Cadena& a, const Cadena& b);
bool operator == (const Cadena& a, const Cadena& b);
bool operator != (const Cadena& a, const Cadena& b);

#endif