#ifndef PEDIDO_HPP
#define PEDIDO_HPP
#include <iostream>

//FICHEROS QUE USA
#include "tarjeta.hpp"
#include "../P1/fecha.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"
#include "usuario.hpp"

using namespace std;

//DECLARACION PREVIA
class Pedido_Articulo;

class Pedido {
    public:
        //CONSTRUCTOR
        Pedido(Usuario_Pedido& uP, Pedido_Articulo& pA, Usuario& u, const Tarjeta& t, Fecha f=Fecha());

        //METODOS OBSERVADORES
        int numero() const
        { return num_; }
        const Tarjeta * tarjeta() const
        { return tarjeta_; }
        const Fecha& fecha() const
        { return fecha_; }
        double total() const
        { return total_; }
        static int n_total_pedidos()
        { return N_pedidos; }

        //CLASES DE EXCEPCION

        class Vacio {
            public:
                Vacio(const Usuario& u) : usuario_(&u) {}
                const Usuario& usuario() const
                { return *usuario_; }
            private:
                const Usuario * usuario_;
        };
        class Impostor {
            public:
                Impostor(const Usuario& u) : usuario_(&u) {}
                const Usuario& usuario() const
                { return *usuario_; }
            private:
                const Usuario * usuario_;
        };
        class SinStock {
            public:
                SinStock(const Articulo& articulo) : articulo_(&articulo) {}
                const Articulo& articulo() const
                { return *articulo_; }
            private:
                const Articulo * articulo_;
        };

    private:
        static int N_pedidos;
        int num_;
        const Tarjeta * tarjeta_;
        Fecha fecha_;
        double total_;
};
//OPERADOR EN FLUJO
ostream& operator << (ostream& os, const Pedido& p);

#endif
