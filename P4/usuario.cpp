#include "usuario.hpp"

#include <random>

std::unordered_set<Cadena> Usuario::usuarios_;

//CONSTRUCTOR
Clave::Clave(const char* C){
  if (strlen(C) < 5)
      throw Clave::Incorrecta(CORTA);
  else {
      const char* s = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";

      random_device random;
      uniform_int_distribution<int> dist(0,strlen(s));

      char cif[2];
      cif[0] = s[dist(random)];
      cif[1] = s[dist(random)];

      char * pass = crypt(C, cif);
      if (pass == nullptr)
          throw Clave::Incorrecta(ERROR_CRYPT);
      clave_ = Cadena(pass);

}
}


bool Clave::verifica(const char* c) const{
 return !strcmp(crypt(c, static_cast<const char*>(clave_)), static_cast<const char*>(clave_));
}

//CONSTRUCTOR
Usuario::Usuario(const Cadena& i, const Cadena& n, const Cadena& a, const
Cadena& d, const Clave& c): id_{i}, nombre_{n}, apellidos_{a}, direccion_{d}, clave_{c}{
 if(!usuarios_.insert(i).second){
   Usuario::Id_duplicado err(i);
   throw err;
 }
}

//DESTRUCTOR
Usuario::~Usuario(){
 for(auto& i:tarjetas_)
    i.second->anula_titular();

 usuarios_.erase(id_);
}

//METODOS PARA LAS RELACIONES

void Usuario::es_titular_de(Tarjeta& tar){
    if (this == tar.titular())
        tarjetas_.insert(std::make_pair(tar.numero(), &tar));
}

void Usuario::no_es_titular_de(Tarjeta& tar){
    tar.anula_titular();
    tarjetas_.erase(tar.numero());
}

void Usuario::compra(Articulo& art, size_t cant)
{
	if (cant == 0)
		compra_.erase(&art);
	else
        compra_[&art] = cant;
}

void Usuario::vaciar_carro()
{
   compra_.clear();
 }


//OPERADORES DE INSERCION EN FLUJO
ostream& operator<< (ostream& os, const Usuario& user)
{
	os << user.id() << " [" << user.clave_.clave() << "] " << user.nombre() << " " << user.apellidos() << "\n";
	os << user.direccion() << "\n";
	os << "Tarjetas:" << "\n";
	for (auto& t:user.tarjetas_)
		os << t.second->numero() << "\n";
	return os;
}

ostream& mostrar_carro(ostream& os, const Usuario& user){
	os<< "Carrito de la compra de " <<user.id_<<"[Artículos: " << user.n_articulos() << "]\n";
    for(auto& art:user.compra_)
        os << art.second << " [" << art.first->referencia() << "] \"" << art.first->titulo() << "\", " << art.first->f_publi().anno() << ". " << fixed << setprecision(2) << art.first->precio() << " €" << endl;

    return os;
}
