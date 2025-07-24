#ifndef _USUARIO_HPP_
#define _USUARIO_HPP_
//FICHEROS QUE USA
#include "articulo.hpp"
#include "cadena.hpp"
#include "tarjeta.hpp"
//CABECERAS
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <cstdlib>
#include <unistd.h>
#include <cstring>

//DECLARACION PREVIA
class Numero;
class Tarjeta;

class Clave{
 public:
   //CONSTRUCTOR
   Clave(const char* c);

   //OBSERVADORES
   Cadena clave() const noexcept;
   bool verifica(const char* c) const;

   //TIPOS DE EXCEPCION
   enum Razon{CORTA, ERROR_CRYPT};

  //CLASE DE EXCEPCION
  class Incorrecta{
    public:
      Incorrecta(const Clave::Razon r);
      Clave::Razon razon() const noexcept;
    private:
      Clave::Razon razon_;
    };
 private:
   Cadena clave_;
};

//METODOS INLINE
inline Cadena Clave::clave() const noexcept {return clave_;}
inline Clave::Incorrecta::Incorrecta(const Clave::Razon r): razon_{r}{}
inline Clave::Razon Clave::Incorrecta::razon() const noexcept{return razon_;}





class Usuario{
 public:
   typedef std::map<Numero, Tarjeta*> Tarjetas;     //MAPA DE TAREJTAS
   typedef std::unordered_map<Articulo*, unsigned int> Articulos;   //MAPA DE ARTICULOS
   //CONSTRUCTORES (SE PROHIBE USAR EL CTOR Y ASIGNACION DE COPIA POR DEFECTO)
   Usuario(const Cadena& i, const Cadena& n, const Cadena& a, const Cadena& d, const Clave& c);
   Usuario(const Usuario& u) = delete;
   Usuario& operator =(const Usuario& u) = delete;

   //OBSERVADORES
   const Cadena& id() const noexcept;
   const Cadena& nombre() const noexcept;
   const Cadena& apellidos() const noexcept;
   const Cadena& direccion() const noexcept;
   const Tarjetas& tarjetas() const noexcept;
   const Articulos& compra() const noexcept;
   size_t n_articulos() const noexcept;

   //RELACION CON TARJETA
   void es_titular_de(Tarjeta& tar);
   void no_es_titular_de(Tarjeta& tar);

   //RELACION CON ARTICULO
   void compra(Articulo& art, size_t cant = 1);

   //MODIFICADORA DEL CARRITO
   void vaciar_carro();

   //DESTRUCTOR
   ~Usuario();

   //CLASE DE EXCEPCION
   class Id_duplicado{
    public:
      Id_duplicado(const Cadena& i);
      const Cadena& idd() const noexcept;
    private:
      Cadena idd_;
   };

    friend std::ostream& mostrar_carro(std::ostream& os, const Usuario& user);
    friend std::ostream& operator <<(std::ostream& os, const Usuario&u);


 private:
   const Cadena id_, nombre_, apellidos_, direccion_;
   Clave clave_;
   Tarjetas tarjetas_;
   Articulos compra_;
   static std::unordered_set<Cadena> usuarios_; //SET DE USUARIOS
};

//MMETODOS INLINE
inline const Cadena& Usuario::id() const noexcept{return id_;}
inline const Cadena& Usuario::nombre() const noexcept{return nombre_;}
inline const Cadena& Usuario::apellidos() const noexcept{return apellidos_;}
inline const Cadena& Usuario::direccion() const noexcept{return direccion_;}
inline const Usuario::Tarjetas& Usuario::tarjetas() const noexcept{return tarjetas_;}
inline const Usuario::Articulos& Usuario::compra() const noexcept{return compra_;}
inline size_t Usuario::n_articulos() const noexcept{return compra_.size();}
inline Usuario::Id_duplicado::Id_duplicado(const Cadena& i):idd_(i){}
inline const Cadena& Usuario::Id_duplicado::idd() const noexcept{return idd_;}
#endif
