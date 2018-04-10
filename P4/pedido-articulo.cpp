#include <iomanip>
#include "pedido-articulo.hpp"

using namespace std;

ostream& operator << (ostream& o, const LineaPedido& lp){
	o << fixed;
	o << setprecision(2) << lp.precio_venta() << " €";
	o << "	" << lp.cantidad();
	return o;

}

void Pedido_Articulo::pedir(Pedido& p, Articulo& a, double pr, unsigned cant){
	pa[&p].insert(make_pair(&a,LineaPedido(pr,cant)));	
	ap[&a].insert(make_pair(&p,LineaPedido(pr,cant)));

}

void Pedido_Articulo::pedir(Articulo& a, Pedido& p, double pr, unsigned cant){
	
	pedir(p, a, pr, cant);

}

const Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle (Pedido& p){
	return pa.find(&p)->second;
}

Pedido_Articulo::Pedidos Pedido_Articulo::ventas (Articulo& a){
	if(ap.find(&a) != ap.end())
		return ap[&a];
	else{
		Pedido_Articulo::Pedidos aux;
		return aux;
	}
	
}

void Pedido_Articulo::mostrarDetallePedidos(ostream& o){
	double total = 0;

	for(PedidoArticulo::iterator it = pa.begin(); it != pa.end(); ++it){
		o << "Pedido núm. " << it->first->numero() << endl;
		o << "Cliente: " << it->first->tarjeta()->titular()->nombre() << " " << "\n";
		o << "Fecha: " << it->first->fecha() << it->second;
		total += it->first->total();
	}

	o << fixed;
	o << "TOTAL VENTAS \t" << setprecision(2) << total << " €" << endl;
}

void Pedido_Articulo::mostrarVentasArticulos(ostream& o){
	
	/*for(ArticuloPedido::const_iterator it = ap.begin(); it != ap.end(); ++it){
         o << "Ventas de " << "[" << it->first->referencia() << "] ";
         o << "\"" << it->first->titulo() << "\" \n" << it->second << endl;
    }*/
    for(auto papoa: ap){
    	Articulo* a = papoa.first;
    	o << "Ventas de [" << a->referencia() << "] " << a->titulo() << "\n" << ventas(*a);
    }

}



ostream& operator << (ostream& o, const Pedido_Articulo::ItemsPedido& ip){
	double precio = 0;

	Pedido_Articulo::ItemsPedido::const_iterator i;

	o << " PVP \t Cantidad \t Articulo \n";
	o <<  "====================================================" << endl;

	for(i = ip.begin(); i != ip.end(); ++i){
		o << i->second.precio_venta() << " €\t";
		o << i->second.cantidad() << "\t";
		o << "[" << i->first->referencia() << "] ";
		o << "\"" << i->first->titulo() << "\" " << endl;

		precio += i->second.precio_venta() * i->second.cantidad();
	}

	o << "===================================================" << endl;

	o << setprecision(2) << precio << " €" << endl;

	return o;
}

ostream& operator << (ostream& o, const Pedido_Articulo::Pedidos& pd){

	double precio = 0;
	int total = 0;

	Pedido_Articulo::Pedidos::const_iterator it;

	o << "[Pedidos: " << pd.size() << "]" << endl;
	o << "====================================================" << endl;
	o << " PVP \t Cantidad \t Fecha de venta \n";
	o << "====================================================" << endl;

	for(it = pd.begin(); it != pd.end(); ++it){
		o << it->second.precio_venta() << " €\t";
		o << it->second.cantidad() << "\t";
		o << it->first->fecha() << endl;

		precio += it->second.precio_venta() * it->second.cantidad();
		total += it->second.cantidad();
	}

	o << "====================================================" << endl;

	o << fixed;
	o << setprecision(2) << precio << " €\t" << total << endl;

	return o;
}
