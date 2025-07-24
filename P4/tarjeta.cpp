#include "tarjeta.hpp"

#include <algorithm>
#include <functional>

using namespace std;


bool luhn(const Cadena& numero);	// Declaración adelantada

Numero::Numero(const Cadena& cad)
{
    char C[21] = {'\0'};

    unsigned int i = 0, j = 0;
    while (i < cad.length())
    {
        if (!isspace(cad[i])) {
            if (!isdigit(cad[i]))
                throw Incorrecto(DIGITOS);

            C[j] = cad[i];
            j++;
        }
        i++;
    }

    if (strlen(C) < 13 || strlen(C) > 19)
        throw Incorrecto(LONGITUD);

    num_ = C;

    if (!luhn(num_))
        throw Incorrecto(NO_VALIDO);
}




Tarjeta::Tarjetas Tarjeta::tarjetas_;

//CONSTRUCTOR
Tarjeta::Tarjeta(const Numero& num, Usuario& tit, const Fecha& ca) : numero_(num), titular_(&tit), caducidad_(ca), activa_(true)
{
    Fecha hoy;

    if (caducidad_ < hoy)
        throw Caducada(caducidad_);
    if (!tarjetas_.insert(numero_).second)
        throw Num_duplicado(numero_);


    tit.es_titular_de(*this);
}
//MODIFICADOR DE ESTADO DE TARJETAS
bool Tarjeta::activa(bool est)
{
    activa_ = est;
    return activa_;
}

Tarjeta::Tipo Tarjeta::tipo() const
{
    if (numero_[0] == '3' && (numero_[1] == '4' || numero_[1] == '7'))
        return AmericanExpress;
    else if (numero_[0] == '3')
        return JCB;
    else if (numero_[0] == '4')
        return VISA;
    else if (numero_[0] == '5')
        return Mastercard;
    else if (numero_[0] == '6')
        return Maestro;
    else
        return Otro;
}

bool operator< (const Tarjeta& t1, const Tarjeta& t2)
{
  return (t1.numero_ < t2.numero_);
 }

//DESTRUCTOR
Tarjeta::~Tarjeta()
{
    if(Usuario * usuario = const_cast<Usuario*>(titular_))
        usuario->no_es_titular_de(*this);
    tarjetas_.erase(numero_);
}

void Tarjeta::anula_titular()
{
    titular_ = nullptr;
    activa_ = false;
}


//OPERADOR DE INSERCION DE FLUJO


ostream& operator<< (ostream& os, Tarjeta::Tipo t)
{
    switch (t) {
        case Tarjeta::Otro:
              os << "Tipo indeterminado"; break;
        case Tarjeta::VISA:
              os << "VISA"; break;
        case Tarjeta::Mastercard:
              os << "Mastercard"; break;
        case Tarjeta::Maestro:
              os << "Maestro"; break;
        case Tarjeta::JCB:
              os << "JCB"; break;
        case Tarjeta::AmericanExpress:
              os << "AmericanExpress"; break;
    }

    return os;
}

ostream& operator<< (ostream& os, const Tarjeta& tarjeta)
{
    Cadena nombre = tarjeta.titular()->nombre();
    Cadena apellidos = tarjeta.titular()->apellidos();
    for(size_t i=0; i< nombre.length(); i++)
        nombre[i] = toupper(nombre[i]);

    for(size_t j=0; j< apellidos.length(); j++)
        apellidos[j] = toupper(apellidos[j]);

    os << tarjeta.tipo() << "\n";
    os << tarjeta.numero() << "\n";
    os << nombre << " " << apellidos << "\n";
    os << "Caduca: " << setfill('0') << setw(2) << tarjeta.caducidad().mes()<< '/' << setw(2) << (tarjeta.caducidad().anno() % 100)<< "\n";
    return os;
}
