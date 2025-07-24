#ifndef _ARTICULO_HPP_
#define _ARTICULO_HPP_
//FICHERO QUE USA
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
//CABECERAS
#include <iostream>
#include <locale>
#include <iomanip>
#include <set>

using namespace std;

class Autor {
    public:
        //CONSTRUCTOR
        Autor(const Cadena& n, const Cadena& ap, const Cadena& d) : nom_(n), ap_(ap), direccion_(d) {}
        //METODOS OBSERVADORES
        const Cadena& nombre() const noexcept;
        const Cadena& apellidos() const noexcept;
        const Cadena& direccion() const noexcept;

    private:
        const Cadena nom_;
        const Cadena ap_;
        const Cadena direccion_;
};


class Articulo{
 public:
   //DEFINICION DE SINONIMO
   typedef set<Autor *> Autores;
   //CONSTRUCTOR
   Articulo(Autores a,Cadena r, Cadena t, Fecha f, double p);

   //OBSERVADORES
   const Cadena& referencia() const noexcept;
   const Cadena& titulo() const noexcept;
   const Fecha& f_publi() const noexcept;
   double precio() const noexcept;
   double& precio() noexcept;
   const Autores& autores() const;
    void impresion_general(ostream&) const;
    //METODO VIRTUAL PURO
    virtual void impresion_especifica(ostream&) const = 0;
   //DESTRUCTOR VIRTUAL
    virtual ~Articulo() {}

    class Autores_vacios {};

 protected:
   const Cadena referencia_, titulo_;
   const Fecha f_publi_;
   double precio_;
   Autores au;
};


//CLASES DERIVADAS

class ArticuloAlmacenable : public Articulo {
    public:
        //CONSTRUCTOR
        explicit ArticuloAlmacenable(Autores a, const Cadena& r, const Cadena& t, const Fecha& f, double p, unsigned int s = 0) : Articulo(a,r,t,f,p), stock_(s) {}
        //METODOS OBSERVADORES
        unsigned int& stock();
        unsigned int stock() const;
        //METODO VIRTUAL PURO
        virtual void impresion_especifica(ostream&) const = 0;
    protected:
        unsigned int stock_;
};

class Libro : public ArticuloAlmacenable {
    public:
       //CONSTRUCTOR
        Libro(Autores a, const Cadena& r, const Cadena& t, const Fecha& f, double p, int n_pag, unsigned int s = 0) :  ArticuloAlmacenable(a,r,t,f,p,s), n_pag_(n_pag) {}
        //METODO OBSERVADOR
        int n_pag() const;
        //DEFINCION DEL METODO VIRTUAL PURO DE ArticuloAlmacenable
        void impresion_especifica(ostream&) const;
    private:
        const int n_pag_;
};

class Revista : public ArticuloAlmacenable {
    public:
      //CONSTRUCTOR
        Revista(Autores a, const Cadena& r, const Cadena& t, const Fecha& f, double p, unsigned int numero, int periodicidad, unsigned int s = 0) : ArticuloAlmacenable(a,r,t,f,p,s),  numero_(numero),   periodicidad_(periodicidad) {}
        //METODOS OBSERVADORES
        unsigned int numero() const;
        int periodicidad() const;
        //DECLARACION DEL METODO VIRTUAL PURO DE  ArticuloAlmacenable
        void impresion_especifica(ostream&) const;
    private:
        const unsigned int numero_;
        const int periodicidad_;
};

class LibroDigital : public Articulo {
    public:
      //CONSTRUCTOR
        LibroDigital(Autores a, const Cadena& r, const Cadena& t, const Fecha& f, double p, const Fecha& fe) : Articulo(a, r, t, f, p),  f_expir_(fe) {}
        //METODO OBSERVADOR
        const Fecha& f_expir() const;
        //DECLARACION DE METODO VIRTUAL PURO DE Articulo
        void impresion_especifica(ostream&) const;
    private:
        const Fecha f_expir_;
};


//OPERADOR DE INSERCION DE FLUJO
std::ostream& operator <<(std::ostream& os, const Articulo& art) noexcept;

//METODOS INLINE
inline const Cadena& Articulo::referencia() const noexcept {return referencia_;}
inline const Cadena& Articulo::titulo() const noexcept {return titulo_;}
inline const Fecha& Articulo::f_publi() const noexcept {return f_publi_;}
inline double Articulo::precio() const noexcept {return precio_;}
inline double& Articulo::precio() noexcept {return precio_;}
inline const Articulo::Autores& Articulo::autores() const { return au; }
inline const Cadena& Autor::nombre() const noexcept {return nom_;}
inline const Cadena& Autor::apellidos() const noexcept {return ap_;}
inline const Cadena& Autor::direccion() const noexcept {return direccion_;}
inline unsigned int& ArticuloAlmacenable::stock() {return stock_;}
inline unsigned int ArticuloAlmacenable::stock() const {return stock_;}
inline int Libro::n_pag() const  {return n_pag_;}
inline unsigned int Revista::numero() const  {return numero_;}
inline int Revista::periodicidad() const  {return periodicidad_;}
inline const Fecha& LibroDigital::f_expir() const  {return f_expir_;}






#endif
