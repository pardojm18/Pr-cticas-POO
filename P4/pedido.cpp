#include <iostream>
#include <iomanip>
#include "pedido.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"

using namespace std;

int Pedido::N_pedidos = 0;

Pedido::Pedido(Usuario_Pedido& up, Pedido_Articulo& pa, Usuario& u, const Tarjeta& t, const Fecha& f): tarjeta_(&t), fecha_(f), total_(0){
	
	if(&u != t.titular()){
		throw Pedido::Impostor(&u);
	}

	if(t.caducidad()<f){
		throw Tarjeta::Caducada(t.caducidad());
	}

	if(u.compra().empty()){
		throw Vacio(&u);
	}

	bool pedido_final_vacio = true;
	Usuario::Articulos carrito = u.compra();
	for(auto i : carrito){
		Articulo *pArt = i.first;
		unsigned cantidad = i.second;
		double precio = pArt->precio();
		
		if(ArticuloAlmacenable* paa = dynamic_cast<ArticuloAlmacenable*>(pArt)){	
			if(cantidad > paa->stock()){
				const_cast<Usuario::Articulos&>(u.compra()).clear();
			 	throw SinStock(pArt);
			}
		
			paa->stock() -= cantidad;
			pa.pedir(*pArt,*this, precio, cantidad);
			total_ += precio * cantidad;
			u.compra(*pArt,0);
			pedido_final_vacio = false;
			
		}else if(LibroDigital* pdl = dynamic_cast<LibroDigital*>(pArt)){
			if(pdl->f_expir() > fecha_){
				pa.pedir(*this,*pArt, precio, cantidad);
				total_ += precio * cantidad;
				u.compra(*pArt,0);
				pedido_final_vacio = false;
			}
		}
	}
	
	if(pedido_final_vacio) throw Vacio(&u);
	up.asocia(u,*this);

	++N_pedidos;
	num_ = N_pedidos;

}

ostream& operator << (ostream& o, const Pedido& p){
	o << "Núm. pedido: " << p.numero() << endl;
	o << "Fecha:\t" << p.fecha() << endl;
	o << "Pagado con:\t" << *(p.tarjeta()) << endl;
	o << "Importe:\t" << fixed << setprecision(2) << p.total() << " €" << endl;

	return o;
}