#include "pedido.hpp"

int Pedido::N_pedidos = 0;

Pedido::Pedido(Usuario_Pedido& uP, Pedido_Articulo& pA, Usuario& u, const Tarjeta& t, Fecha f)
: num_(N_pedidos + 1), tarjeta_ (&t), fecha_(f), total_(0)
{
    bool vacio=true;
    if (u.compra().empty()) throw Vacio(u);
    if (&u != t.titular()) throw Impostor(u);
    if (t.caducidad() < f) throw Tarjeta::Caducada(t.caducidad());
    if (!t.activa()) throw Tarjeta::Desactivada();

    for (auto artic: u.compra())
    {
      if (ArticuloAlmacenable* almc=dynamic_cast<ArticuloAlmacenable*>(artic.first)){
        if(almc->stock() < artic.second){
            u.vaciar_carro();
            throw SinStock(*artic.first);
        }
      }
    }

    for(auto artic: u.compra()){
       if (ArticuloAlmacenable *almcc = dynamic_cast<ArticuloAlmacenable *>(artic.first)){
         almcc->stock() -= artic.second;
         total_ += artic.first->precio() * artic.second;
         pA.pedir(*this, *artic.first, artic.first->precio(), artic.second);
         vacio = false;
      }
      else {
        LibroDigital * ld = dynamic_cast<LibroDigital *>(artic.first);
           if(ld->f_expir() >= f) {
               total_ += artic.first->precio() * artic.second;
               pA.pedir(*this, *artic.first, artic.first->precio(), artic.second);
               vacio = false;
      }
     }
    }
    if (vacio)
        throw Vacio(u);
    N_pedidos++;
    uP.asocia(*this, u);
    u.vaciar_carro();
}

ostream& operator << (ostream& os, const Pedido& p)
{
    os << "Núm. pedido:\t" << p.numero() << endl;
    os << "Fecha: \t" << p.fecha() << endl;
    os << "Pagado con:\t" << p.tarjeta()->tipo() << " n.º: " << p.tarjeta()->numero() << endl;
    os << "Importe: \t" << fixed << setprecision(2) << p.total() << " €" << endl;
    return os;
}
