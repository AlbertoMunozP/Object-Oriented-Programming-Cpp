#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP
#include <iostream>
#include <map>

//FICHERO QUE UTILIZA
#include "pedido.hpp"

//DECLARACIONES ANTICIPADAS
class Articulo;
class Pedido;

using namespace std;

class LineaPedido {
    public:
      //CONSTRUCTOR
        explicit LineaPedido(double p, unsigned int c=1) : precio_venta_(p), cantidad_(c) {}

        //METODOS OBSREVADORES
        double precio_venta() const
        { return precio_venta_; }
        unsigned int cantidad() const
        { return cantidad_; }

    private:
        double precio_venta_;
        unsigned int cantidad_;
};

//CLASES DE LOS PEDIDOS

class OrdenaArticulos {
    public:
        //SOBRECARGA
        bool operator() (const Articulo * a1, const Articulo * a2) const;
};

class OrdenaPedidos {
    public:
      //SOBRECARGA
        bool operator() (const Pedido * p1, const Pedido * p2) const;
};

class Pedido_Articulo {
    public:
        //DECLARACION DE LOS MAPAS
        typedef map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
        typedef map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;

        //METODO PEDIR SOBRECARAGDO
        void pedir (Pedido& p, Articulo& a, double pr, unsigned int c=1);
        void pedir (Articulo& a, Pedido& p, double pr, unsigned int c=1);

        ItemsPedido detalle (Pedido& p) const;
        Pedidos ventas (Articulo& a) const;

        ostream& mostrarDetallePedidos(ostream& os) const;
        ostream& mostrarVentasArticulos(ostream& os) const;

    private:
        map<Pedido *, ItemsPedido, OrdenaPedidos> pArt;
        map<Articulo *, Pedidos, OrdenaArticulos> aPed;
};


//OPERADORES EN FLUJO
ostream& operator << (ostream& os, const LineaPedido& l);
ostream& operator<< (ostream& os, const Pedido_Articulo::ItemsPedido& i);
ostream& operator<< (ostream& os, const Pedido_Articulo::Pedidos& p);

#endif
