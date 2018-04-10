#ifndef PEDIDOARTICULO_HPP_
#define PEDIDOARTICULO_HPP_

#include <iostream>
#include "pedido.hpp"
#include "articulo.hpp"

using namespace std;

struct OrdenaPedidos : public binary_function<Pedido*, Pedido*, bool>{
	bool operator()(const Pedido* p1, const Pedido* p2) const {return p1->numero() < p2->numero();}
};

struct OrdenaArticulos : public binary_function<Articulo*, Articulo*, bool> {
	bool operator()(const Articulo* a1, const Articulo* a2) const {return a1->referencia() < a2->referencia();}
};

class LineaPedido{
public:
	explicit LineaPedido(double precio_venta, unsigned cantidad = 1u): precio_venta_(precio_venta), cantidad_(cantidad) {}
	double precio_venta() const {return precio_venta_;}
	unsigned cantidad() const {return cantidad_;}
private:
	double precio_venta_;
	int cantidad_;
};

ostream& operator << (ostream& o, const LineaPedido& lp);

class Pedido_Articulo{
public:
	typedef map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
	typedef map<Pedido*, ItemsPedido, OrdenaPedidos> PedidoArticulo;	
	typedef map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
	typedef map<Articulo*, Pedidos, OrdenaArticulos> ArticuloPedido;

	void pedir(Pedido& p, Articulo& a, double pr, size_t cant = 1);
	void pedir(Articulo& a, Pedido& p, double pr, size_t cant = 1);
	ItemsPedido detalle (Pedido& p);
	Pedidos ventas (Articulo& a);
	void mostrarDetallePedidos(ostream& o);
	void mostrarVentasArticulos(ostream& o);

private:
	PedidoArticulo pa;
	ArticuloPedido ap;
};

ostream& operator << (ostream& o, const Pedido_Articulo::ItemsPedido& ip);
ostream& operator << (ostream& o, const Pedido_Articulo::Pedidos& pd);

#endif