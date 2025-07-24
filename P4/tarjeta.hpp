#ifndef TARJETA_HPP
#define TARJETA_HPP
//CABECERAS

#include <iostream>
#include <iomanip>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <set>

//FICHEROS QUE USA
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include "usuario.hpp"

using namespace std;

//DECLARACION ANTICIPADA DE USUARIO
class Usuario;

class Numero {
    public:
      //CAUSANTES DE EXCEPCIONES
      enum Razon {LONGITUD, DIGITOS, NO_VALIDO};
      //CONSTRUCTOR
      Numero(const Cadena& cad);
      //OPERADOR DE CONV
      operator const char * () const;
      //METODO AMIGO
      friend bool operator<(const Numero& num1, const Numero& num2);
      //CLASE DE EXCEPCION
      class Incorrecto {
          public:
              //CONSTRUCTOR DE EXCEPCION
              Incorrecto(Razon r): Razon(r) {}
              //OBSERVADOR DE CAUSA (ATRIBUTO)
              Razon razon() const { return Razon; }
          private:
              Numero::Razon Razon;
      };

    private:
        Cadena num_;

};

//METODOS INLINE

//OPERADOR DE CONVERSION
inline Numero::operator const char * () const
{ return (const char *) num_; }

//OPERADORES ARITMETICOS
inline bool operator<(const Numero& num1, const Numero& num2)
{ return (num1.num_ < num2.num_); }


class Tarjeta {
    public:
        //TIPOS DE TARJETA
        enum Tipo {Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress};

        typedef set<Numero> Tarjetas;
        //CONSTRUCTORES
        Tarjeta(const Numero& num, Usuario& tit, const Fecha& f);
        //PROHIBICION DE COPIA  Y ASIGNACION DE TARJETAS
        Tarjeta(const Tarjeta&) = delete;
        void operator=(const Tarjeta& ) = delete;

        //METODOS OBSERVADORES
        const Numero& numero() const;
        const Usuario * titular() const;
        const Fecha& caducidad() const;
        bool activa() const;
        bool activa(bool estado);
        Tipo tipo() const;

        //METODO AMIGO DE LA CLASE
        friend bool operator< (const Tarjeta& t1, const Tarjeta& t2);

        //DESTRUCTOR
        ~Tarjeta();

        //CLASE DE EXCEPCION
        class Caducada {
            public:
                //CONSTRUCTOR
                Caducada(const Fecha& caducidad) : f(caducidad) {}
                //OBSERVADOR
                const Fecha& cuando() const;
            private:
                Fecha f;
        };
        //CLASE DE EXCEPCION
        class Num_duplicado {
            public:
                //CONSTRUCTOR
                Num_duplicado(const Numero& num) : Numero(num) {}
                //OBSERVADOR
                const Numero& que() const;
            private:
                Numero Numero;
        };

        class Desactivada {};

    private:
        const Numero numero_;
        const Usuario * titular_;
        const Fecha caducidad_;
        bool activa_;

        static Tarjetas tarjetas_;

        friend class Usuario;
        void anula_titular();
};

//SOBRECARGADO OPERADOR DE INSERCIÓN DE FLUJO
ostream& operator<< (ostream& os, const Tarjeta& tarjeta);
ostream& operator<< (ostream& os, Tarjeta::Tipo t);

//OBSERVADORES
inline const Numero& Tarjeta::numero() const
{ return numero_; }

inline const Usuario * Tarjeta::titular() const
{ return titular_; }

inline const Fecha& Tarjeta::caducidad() const
{ return caducidad_; }

inline bool Tarjeta::activa() const
{ return activa_; }

inline const Fecha& Tarjeta::Caducada::cuando() const
{ return f; }

inline const Numero& Tarjeta::Num_duplicado::que() const
{ return Numero; }

#endif
