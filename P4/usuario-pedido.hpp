#ifndef USUARIO_PEDIDO_HPP
#define USUARIO_PEDIDO_HPP

//FICHEROS QUE USO
#include <iostream>
#include <map>
#include <set>

using namespace std;

//DECLARACIONES ANTICIPADAS
class Usuario;
class Pedido;

class Usuario_Pedido  {
    public:

        typedef set<Pedido *> Pedidos;

        //CREADORES DE ENLACES
        void asocia(Usuario& u, Pedido& ped);
        void asocia(Pedido& p, Usuario& u);

        //OBSERVADORES
        Pedidos pedidos (Usuario& u) const;
        Usuario * cliente (Pedido& p) const;

    private:
        typedef map<Usuario *, Pedidos> UsuariosPedidos;
        typedef map<Pedido *, Usuario *> PedidosUsuarios;

        UsuariosPedidos usuarios_;
        PedidosUsuarios pedidos_;
};

#endif
