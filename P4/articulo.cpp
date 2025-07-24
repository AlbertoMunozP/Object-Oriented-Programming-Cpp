#include "articulo.hpp"
//CONSTRUCTOR
Articulo::Articulo(Autores a, Cadena r, Cadena t, Fecha f, double p) : referencia_(r), titulo_(t), f_publi_(f), precio_(p)
{
    if (a.empty()) throw Autores_vacios();
    au.insert(a.begin(), a.end());
}
//OPERADORES EN FLUJO
ostream& operator<< (ostream& os, const Articulo& a) noexcept
{
    a.impresion_general(os);
    a.impresion_especifica(os);
    return os;
}

void Articulo::impresion_general(ostream & os) const
{
    os << "[" << referencia() << "] ";
    os << '"' << titulo() << "\", de ";
    auto ult = autores().end();
    ult--;
    for (auto iter : autores()) {
        os << (*iter).apellidos();
        if (iter != (*ult))
            os << ", ";
        else
            os << ". ";
    }
    os << f_publi().anno() << ". ";
    os << fixed << setprecision(2) << precio() << " €" << endl << "\t";
}

void Libro::impresion_especifica(ostream & os) const
{
  os << n_pag_ << " págs., " << stock_ << " unidades."; 
}

void Revista::impresion_especifica(ostream & os) const
{
    os << "Número: " << numero_ << ", Periodicidad: " << periodicidad_ << " días." << endl;
    os << "\tPróximo número a partir de: " << f_publi_ + periodicidad_ << ".";
}

void LibroDigital::impresion_especifica(ostream & os) const
{
   os << "A la venta hasta el " << f_expir_ << ".";
  }
