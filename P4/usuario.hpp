#ifndef USUARIO_HPP_
#define USUARIO_HPP_
#include <ctime>
#include <unordered_set>
#include <unordered_map>
#include <cstring>
#include <map>

#include "cadena.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"

using namespace std;

class Tarjeta;
class Numero;

class Clave{
public:
	Clave(const char* con);
	enum Razon {CORTA, ERROR_CRYPT};
	class Incorrecta {
        const Razon razon_;
    public:
        Incorrecta(const Razon raz) : razon_(raz) {}
        const Razon razon() const {return razon_;}
    };
    
	Cadena clave() const {return contra;}
	bool verifica(const char* cl) const;

private:
	Cadena contra;
};

class Usuario{
public:
	typedef map<Numero, Tarjeta*> Tarjetas;
	typedef unordered_map<Articulo*, size_t> Articulos;
	typedef char* iterator;
	class Id_duplicado{
		const Cadena c;
	public:
		Id_duplicado(const Cadena& a):c(a){}
		const Cadena idd() const {return c;}
	};
	Usuario(const Cadena& id, const Cadena& nom, const Cadena& apell, const Cadena& dir, const Clave& cl);
	//Enlace tarjeta
	void es_titular_de(Tarjeta& t);
	void no_es_titular_de(Tarjeta& t);
	const Tarjetas& tarjetas() const {return tarjetas_;}
	//Enlace articulos
	void compra(Articulo& a, size_t cant = 1);
	const Articulos& compra() const {return articulos_;}
	size_t n_articulos() const {return articulos_.size();}
	//Observadores
	Cadena id() const {return id_;}
	Cadena nombre() const {return nom_;}
	Cadena apellidos() const {return apell_;}
	Cadena direccion() const {return dir_;}
	//destructor
	~Usuario();
	friend ostream& operator << (ostream& o, const Usuario& u);
	//Funciones propias
private:
	Usuario (const Usuario&);
	Usuario operator = (const Usuario&);
	Cadena id_, nom_, apell_, dir_;
	Clave cl_;
	Tarjetas tarjetas_;
	Articulos articulos_;
	static unordered_set<Cadena> listado;
};

ostream& operator << (ostream& o, const Usuario& u);
ostream& mostrar_carro(ostream& o, const Usuario& u);


#endif