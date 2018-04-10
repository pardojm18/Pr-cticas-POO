#ifndef USUARIOARTICULO_HPP_
#define USUARIOARTICULO_HPP_

#include <iostream>
#include <map>
#include <set>

#include "usuario.hpp"
#include "pedido.hpp"

using namespace std;

class Usuario_Pedido{
public:
	typedef set<Pedido*> Pedidos;
	typedef map<Usuario*, Pedidos> UsuarioPedidos;
	typedef map<Pedido*, Usuario*> PedidoUsuario;

	void asocia(Usuario& u, Pedido& p) {up[&u].insert(&p); pu[&p] = &u;}
	void asocia(Pedido& p, Usuario& u) {asocia(u,p);}

	const Pedidos& pedidos(Usuario& u) {return up[&u];}
	const Usuario* cliente(Pedido& p) {return pu[&p];}

private:
	UsuarioPedidos up;
	PedidoUsuario pu;
};

#endif