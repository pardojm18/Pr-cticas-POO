#include <iostream>
#include <iomanip>
#include "articulo.hpp"

using namespace std;

Articulo::Articulo(const Autores& autores, const Cadena& ref, const Cadena& tit, const Fecha& fpubl, double prec){
	
	if(autores.empty())
		throw Autores_vacios();

	autores_ = autores;
	referencia_ = ref;
	titulo_ = tit;
	f_publi_ = fpubl;
	precio_ = prec;
	//stock_ = sto;
}

ostream& operator <<(ostream& o, const Articulo& a)
{
	o << "[" << setw(3) << setfill('0') << a.referencia() << "] " << "\"" << a.titulo() << "\", " << "de ";
	

	for(auto i = a.autores().begin(); i != a.autores().end(); ++i){
		if (i == a.autores().begin())
			o << (*i)->apellidos();
		else
			o << ", " << (*i)->apellidos();
	}
	
	o << ". " << a.f_publi().anno() << ". ";
	o << fixed << setprecision(2) << a.precio() << " €\n\t";

	a.impresion_especifica(o);

	return o;
}

void Libro::impresion_especifica(ostream& o) const{
	o << n_pag() << " págs., "<< stock() <<" unidades.";
}

void Cederron::impresion_especifica(ostream& o) const{
	o << tam() << " MB, " <<stock() << " unidades.";
}

void LibroDigital::impresion_especifica(ostream& o) const{
	o << "A la venta hasta el " << f_expir() <<".";
}