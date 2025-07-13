#include "pedido-articulo.hpp"
#include <iomanip>

//OPERADOR EN FLUJO
ostream& operator << (ostream& os, const LineaPedido& l)
{
    os<<fixed<<setprecision(2)<<l.precio_venta()<<" €\t"<<l.cantidad();
    return os;
}

bool OrdenaPedidos::operator()(const Pedido * p1, const Pedido * p2) const
{return p1->numero() < p2->numero();}

bool OrdenaArticulos::operator()(const Articulo * a1, const Articulo * a2) const
{return a1->referencia() < a2->referencia();}



void Pedido_Articulo::pedir (Pedido &p, Articulo &a, double pr, unsigned int c)
{
    pArt[&p].insert(make_pair(&a, LineaPedido(pr, c)));
    aPed[&a].insert(make_pair(&p, LineaPedido(pr, c)));
}

void Pedido_Articulo::pedir(Articulo &a, Pedido &p, double pr, unsigned int c)
{pedir(p,a,pr,c);} 

Pedido_Articulo::ItemsPedido Pedido_Articulo::detalle (Pedido& p) const
{

    if(pArt.find(&p) != pArt.end())
         return pArt.find(&p)->second;
    else{
        Pedido_Articulo::ItemsPedido empty;
        return empty;
    }
}

Pedido_Articulo::Pedidos Pedido_Articulo::ventas (Articulo& a) const
{
    if(aPed.find(&a) != aPed.end())
        return aPed.find(&a)->second;
    else{
        Pedido_Articulo::Pedidos empty;
        return empty;
    }
}


//OPERADORES EN FLUJO
ostream& Pedido_Articulo::mostrarDetallePedidos(ostream& os) const
{
    double res = 0;
    for (auto pedido : pArt)
    {
        os <<"Pedido número: "<< pedido.first->numero()<< endl;
        os <<"Cliente: "<<pedido.first->tarjeta()->titular()->nombre()<< "      Fecha: " <<pedido.first->fecha()<<endl;
        res+=pedido.first->total();
        Pedido& ped=*pedido.first;
        os <<detalle(ped);
        os <<"Ventas totales   " <<fixed<<setprecision(2)<<res<<" € "<<endl;
    }
    return os;
}
ostream& Pedido_Articulo::mostrarVentasArticulos(ostream &os) const
{
    for (auto iter : aPed)
    {
        os<<"Venta de ["<<iter.first->referencia()<<"] \""<<iter.first->titulo()<<"\""<<endl;
        Articulo& a=*iter.first;
        os << ventas(a)<<endl;
    }
    return os;
}


ostream& operator<< (ostream& os, const Pedido_Articulo::ItemsPedido& i)
{
    double res = 0;

    os <<"PVP \tCantidad \tArtículo"<< endl;
    os <<"==================================================="<< endl;
    for (auto& it : i)
    {
        os<<setprecision(2)<<it.second.precio_venta()<<" €\t"<<it.second.cantidad()<<"\t\t["<<it.first->referencia()<<"] \""<<it.first->titulo()<<"\""<<endl;
        res+=(it.second.precio_venta()*it.second.cantidad());
    }
    os<<"==================================================="<<endl;
    os<<"Total:   "<<fixed<<setprecision(2)<<res<<endl;

    return os;
}

ostream& operator<< (ostream& os, const Pedido_Articulo::Pedidos& p)
{
    double prFinal=0;
    int cFinal=0;

    os<<"[Pedidos: "<<Pedido::n_total_pedidos()<<"]"<<endl;
    os<<"==================================================="<<endl;
    os<<"PVP \tCantidad \tFecha de venta"<<endl;
    os<<"==================================================="<<endl;
    for (auto& it : p)
    {
        os<<fixed<<setprecision(2)<<it.second.precio_venta()<<" €\t"<<it.second.cantidad()<<"\t\t"<<it.first->fecha()<< endl;
        prFinal+=(it.second.precio_venta()*it.second.cantidad());
        cFinal+=it.second.cantidad();
    }
    os<<"==================================================="<<endl;
    os<<fixed<<setprecision(2)<<prFinal<<" €        "<<cFinal<<endl;

    return os;
}
