#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_
#include <iostream>
#include "tarjeta.hpp"

using namespace std;

class Usuario_Pedido;
class Pedido_Articulo;
class Usuario;

class Pedido{
public:
	class Vacio{
		Usuario* u;
	public:
		Vacio(Usuario* us):u(us){}
		Usuario& usuario() const {return *u;}
	};
	class Impostor{
		Usuario* u;
	public:
		Impostor(Usuario* us):u(us){}
		Usuario& usuario() const {return *u;}
	};
	class SinStock{
		Articulo* a;
	public:
		SinStock(Articulo* ar):a(ar){}
		Articulo& articulo() const {return *a;}
	};

	Pedido(Usuario_Pedido& up, Pedido_Articulo& pa, Usuario& u, const Tarjeta& t, const Fecha& f = Fecha());
	int numero() const {return num_;}
	const Tarjeta* tarjeta() const {return tarjeta_;}
	Fecha fecha() const {return fecha_;}
	double total() const {return total_;}
	static int n_total_pedidos(){return N_pedidos;}
private:
	static int N_pedidos;
	int num_;
	const Tarjeta* tarjeta_;
	Fecha fecha_;
	double total_;
};

ostream& operator << (ostream& o, const Pedido& p);

#endif