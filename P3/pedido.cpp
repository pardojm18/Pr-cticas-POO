#include <iostream>
#include <iomanip>
#include "pedido.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"

using namespace std;

int Pedido::N_pedidos = 0;

Pedido::Pedido(Usuario_Pedido& up, Pedido_Articulo& pa, Usuario& u, const Tarjeta& t, const Fecha& f): tarjeta_(&t), fecha_(f), total_(0){
	
	if(&u != t.titular())
		throw Impostor(&u);
	if(t.caducidad() < f)
		throw Tarjeta::Caducada(t.caducidad());
	if(u.compra().begin() == u.compra().end())
		throw Pedido::Vacio(&u);

	for(auto it = u.compra().begin(); it != u.compra().end(); ++it){
		if(it->second > it->first->stock()){
			Articulo* a = it->first;
			const_cast<Usuario::Articulos&>(u.compra()).clear();
			throw SinStock(a);
		}
	}

	up.asocia(*this, u);
	auto carro = u.compra();

	for(auto it = carro.begin(); it != carro.end(); ++it){
		total_ += (it->first->precio() * it->second);
		pa.pedir(*this, *(it->first), it->first->precio(), it->second);
		it->first->stock() -= it->second;
		u.compra(*(it->first),0);
	}

	N_pedidos++;
	num_ = N_pedidos;

}

ostream& operator << (ostream& o, const Pedido& p){
	o << "Núm. pedido: " << p.numero() << endl;
	o << "Fecha:\t" << p.fecha() << endl;
	o << "Pagado con:\t" << *(p.tarjeta()) << endl;
	o << "Importe:\t" << fixed << setprecision(2) << p.total() << " €" << endl;

	return o;
}