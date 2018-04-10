#include <ctime>
#include <cstdlib>
#include <random>
#include <unistd.h>
#include <crypt.h>
#include <iomanip>

#include "usuario.hpp"
#include "tarjeta.hpp"


using namespace std;

unordered_set<Cadena> Usuario::listado;

Clave::Clave(const char* con){
	if(strlen(con) < 5) 
		throw Incorrecta(CORTA);

	random_device r;
	uniform_int_distribution<size_t> d{0, 63};

	char vector[] {"ABCDEFGHIJKLMNOPQRSTUVWXYZ.0123456789/abcdefghijklmnopqrstuvwxyz"};
	char salt[] { vector[d(r)], vector[d(r)] };

	const char * const contr= crypt(con, salt);

	if(!contr)
		throw Incorrecta(ERROR_CRYPT);

	contra=contr;

}

bool Clave::verifica(const char* cl) const{
	return contra == crypt(cl,contra.c_str());
}

Usuario::Usuario(const Cadena& id, const Cadena& nom, const Cadena& apell, const Cadena& dir, const Clave& cl):id_(id), nom_(nom), apell_(apell), dir_(dir),cl_(cl){
	//pair<agregados::iterator,bool> a = ;
	if(!(listado.insert(id_).second))
		throw Id_duplicado(id_);
}

void Usuario::es_titular_de(Tarjeta& t){
	if(this == t.titular())
		tarjetas_.insert(make_pair(t.numero(),&t));
}

void Usuario::no_es_titular_de(Tarjeta& t){
	//Tarjetas::iterator it;
	//it = tarjetas_.find(t.numero());
	t.anular_titular();
	tarjetas_.erase(t.numero());
}

void Usuario::compra(Articulo& a, size_t cant){
	if(cant == 0)
		articulos_.erase(&a);
	else
		articulos_[&a] = cant;

	/*if(cant != 0){
		articulos_.insert(make_pair(&a,cant));
	}*/
}

Usuario::~Usuario(){
	for(Tarjetas::iterator it = tarjetas_.begin();it != tarjetas_.end();++it){
		it->second->anular_titular();
	}
	listado.erase(id_);
}

ostream& operator << (ostream& o, const Usuario& u){
	o << u.id() << " [" << u.cl_.clave() << "] " << u.nombre() << " " << u.apellidos()
		<< "\n" << u.direccion() << "\n" << "Tarjetas:\n";
		for(Usuario::Tarjetas::const_iterator i = u.tarjetas().begin(); i != u.tarjetas().end(); ++i)
			o << i->second->numero() << endl;
	return o;
}

ostream& mostrar_carro(ostream& os, const Usuario& u){
	os << "Carrito de compra de " << u.id() << " [Artículos: " << u.n_articulos() << "]" << endl;
	os << " Cant. Artículo" << endl;
	os << "===========================================================" << endl;
  
	for(Usuario::Articulos::const_iterator i = u.compra().begin(); i != u.compra().end(); ++i){
		os << i->second << " [" << i->first->referencia() << "] ";
    	os << "\"" << i->first->titulo() << "\"";
    	os << ", " << i->first->f_publi().anno() << ". ";
		os << fixed << setprecision(2) << i->first->precio() << " €" << endl;
	}
  
  	return os;
}