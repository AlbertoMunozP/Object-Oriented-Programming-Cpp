#ifndef FECHA_HPP_
#define FECHA_HPP_
#include<ctime>

#define FECHA_HPP_ANNO_MIN 1902
#define FECHA_HPP_ANNO_MAX 2037


class Fecha {
  public:
        explicit Fecha(int dia__ = 0, int mes__ = 0,int anno__ = 0);
        Fecha(const char *s);


        //CONVERSOR FECHA A CONST CHAR*
        const char* cadena() const;

        //OPERADORES MIEMBROS DE LA CLASE
        Fecha operator++ (int);
    		Fecha& operator++ ();
    		Fecha operator-- (int);
    		Fecha& operator-- ();
    		Fecha operator+ (int n) const;
    		Fecha operator- (int n) const;
    		Fecha& operator += (int n);
    		Fecha& operator -= (int n);

        //METODOS OBSERVADORES
        int dia() const noexcept {return dia_;}
        int mes() const noexcept {return mes_;}
        int anno() const noexcept {return anno_;}

        static const int AnnoMinimo = FECHA_HPP_ANNO_MIN;
        static const int AnnoMaximo = FECHA_HPP_ANNO_MAX;

        class Invalida {
          public:
            Invalida(const char* msg) : msg_info(msg) {}
            const char* por_que() const;
          private:
            const char* msg_info;
    };

    private:
        int dia_,mes_,anno_;
        void valida();
};


//OPERADORES INSERCION Y EXTRACCION DE FLUJO
std::ostream& operator<<(std::ostream& os, const Fecha& fe);
std::istream& operator>>(std::istream& is, Fecha& fe);

bool operator==(const Fecha& fecha1, const Fecha& fecha2);
bool operator!=(const Fecha& fecha1, const Fecha& fecha2);
bool operator<(const Fecha& fecha1, const Fecha& fecha2);
bool operator>(const Fecha& fecha1, const Fecha& fecha2);
bool operator<=(const Fecha& fecha1, const Fecha& fecha2);
bool operator>=(const Fecha& fecha1, const Fecha& fecha2);


//METODOS INLINE
inline bool operator==(const Fecha& f1, const Fecha& f2)
{
return (f1.dia() == f2.dia() && f1.mes() == f2.mes() && f1.anno() == f2.anno());
}

inline bool operator!=(const Fecha& f1, const Fecha& f2)
{
return (!(f1 == f2));
}

inline bool operator<(const Fecha& f1, const Fecha& f2)
{
return (f1.anno() < f2.anno() || (f1.anno() == f2.anno() && f1.mes() < f2.mes()) || (f1.anno() == f2.anno() && f1.mes() == f2.mes() && f1.dia() < f2.dia()));
}

inline bool operator>(const Fecha& f1, const Fecha& f2)
{
return (!(f1 < f2) && !(f1 == f2));
}

inline bool operator<=(const Fecha& f1, const Fecha& f2)
{
return (f1 < f2 || f1 == f2);
}

inline bool operator>=(const Fecha& f1, const Fecha& f2)
{
return (!(f1 < f2));
}

inline const char * Fecha::Invalida::por_que() const
{ return (msg_info); }





#endif
