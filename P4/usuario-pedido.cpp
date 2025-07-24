#include <map>
#include <set>

#include "usuario-pedido.hpp"
#include "usuario.hpp"
#include "pedido.hpp"

using namespace std;

void Usuario_Pedido::asocia(Usuario &u, Pedido &p)
{
    usuarios_[&u].insert(&p);
    pedidos_[&p] = &u;
}

void Usuario_Pedido::asocia(Pedido &p, Usuario &u)
{ asocia(u, p); }  

Usuario_Pedido::Pedidos Usuario_Pedido::pedidos(Usuario &u) const
{
    if (usuarios_.find(&u) != usuarios_.end())
        return usuarios_.find(&u)->second;
    else
        return Pedidos();
}

Usuario* Usuario_Pedido::cliente(Pedido &p) const
{
    if (pedidos_.find(&p) != pedidos_.end())
        return pedidos_.find(&p)->second;
    else
        return nullptr;
}
