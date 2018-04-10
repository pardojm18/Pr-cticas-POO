#ifndef CADENA_HPP_
#define CADENA_HPP_

#include <iostream>
#include <cstring>

using namespace std;

class Cadena{
public:
	Cadena(const size_t& tam = 0, const char& cad = ' ');
	Cadena(const char* cad, size_t ini = -1);
	Cadena(const Cadena& cad, size_t ini = 0, size_t lon = -1);
	Cadena(Cadena&& a);
	void operator = (Cadena&& a);
	void operator = (const Cadena& a);
	char operator [] (const size_t& n) const {return s_[n];}
	char& operator [] (const size_t& n) {return s_[n];}
	char at(size_t n) const;
	char& at(size_t n);
	size_t length()	const {return tam_;}
	void operator +=(const Cadena& a);
	Cadena substr(const size_t& ini, const size_t& lon) const;
	const char* c_str() const {return s_;}
	~Cadena();
	static const int npos = -1;
	//P1
	typedef char* iterator;
    typedef const char* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    //ITERADORES
    iterator begin()  {return &s_[0];}
    iterator end()  {return &s_[tam_];}
    reverse_iterator rbegin() {return reverse_iterator (&s_[tam_]);}
    reverse_iterator rend() {return reverse_iterator (&s_[0]);}
    const_iterator cbegin() const {return &s_[0];}
    const_iterator cend() const {return &s_[tam_];}
    const_iterator begin() const {return &s_[0];}
    const_iterator end()  const  {return &s_[tam_];}
    const_reverse_iterator rbegin() const {return reverse_iterator (&s_[tam_]);}
    const_reverse_iterator rend() const {return reverse_iterator (&s_[0]);}
    const_reverse_iterator crbegin() const {return reverse_iterator (&s_[tam_]);}
    const_reverse_iterator crend() const {return reverse_iterator (&s_[0]);}
private:
	char* s_;
	size_t tam_;
};

template <> struct hash<Cadena> {
	size_t operator()(const Cadena& cad) const
	{ // conversión const char* ->string
	return hash<string>{}(cad.c_str());
	}
};

Cadena operator +(const Cadena& a, const Cadena& b);
bool operator < (const Cadena& a, const Cadena& b);
bool operator >= (const Cadena& a, const Cadena& b);
bool operator > (const Cadena& a, const Cadena& b);
bool operator <= (const Cadena& a, const Cadena& b);
bool operator == (const Cadena& a, const Cadena& b);
bool operator != (const Cadena& a, const Cadena& b);
ostream& operator << (ostream &o, const Cadena& a);
istream& operator >> (istream &i, Cadena& a);

#endif