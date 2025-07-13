#include<iostream>
#include<cstdio>
#include<locale>
#include "fecha.hpp"

using namespace std;

//
//		METODOS PUBLICOS
//


//CONSTRUCTORES

Fecha::Fecha (int dia__, int mes__, int anno__) : dia_(dia__), mes_(mes__), anno_(anno__)
{
	if(dia__ == 0 || mes__== 0 || anno__== 0) {

		std::time_t tiempo_calendario = std::time(nullptr);
		std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);

  	if(dia_==0) dia_ = tiempo_descompuesto->tm_mday;
		if(mes_==0) mes_ = tiempo_descompuesto->tm_mon + 1;
		if(anno_==0) anno_ = tiempo_descompuesto->tm_year + 1900;


	}
	valida();
}


//CONVERSOR DE CADENA A FECHA
Fecha::Fecha(const char *s)
{
	int d,m,a;
	int x = sscanf(s,"%d/%d/%d", &d, &m,&a);
	if(x!=3) {
			Fecha::Invalida error("Error en el formato utilizado");
			throw error;
	}
		Fecha f(d, m, a);
		dia_ = f.dia();
		mes_ = f.mes();
		anno_ = f.anno();

	//valida();

}

//CONVERSOR DE FECHA A CADENA
 const char* Fecha::cadena() const
{
	setlocale(LC_ALL, "es_ES.UTF-8");
	struct tm fe = {};

	fe.tm_mday = dia_;
	fe.tm_mon = mes_ - 1;
	fe.tm_year = anno_ - 1900;

	mktime(&fe);

	static char * fecha = new char [50];

	strftime(fecha, 50, "%A %e de %B de %Y", &fe);
	return fecha;
}

//SOBRECARGA DE OPERADORES
Fecha Fecha::operator++ (int)
{
	Fecha t;
	t = *this;
	*this += 1;
	return t;
}

Fecha& Fecha::operator++ ()
{*this += 1; return *this;}

Fecha Fecha::operator-- (int)
{
	Fecha t;
	t = *this;
	*this += -1;
	return t;
}

Fecha& Fecha::operator-- ()
{*this += -1; return *this;}

Fecha Fecha::operator+ (int n) const
{
	Fecha t;
	t = *this;
	t += n;
	return t;
}

Fecha Fecha::operator- (int n) const
{
	Fecha t;
	t = *this;
	t += -n;
	return t;
}

Fecha& Fecha::operator+= (int n)
{
	struct tm tmpo = {};
	tmpo.tm_mday = dia_;
	tmpo.tm_mon = mes_ - 1;
	tmpo.tm_year = anno_ - 1900;
	tmpo.tm_mday += n;
  mktime(&tmpo);
	dia_ = tmpo.tm_mday;
	mes_ = tmpo.tm_mon + 1;
	anno_ = tmpo.tm_year + 1900;
  valida();

	return *this;
}

Fecha& Fecha::operator-= (int n)
{*this += -n; return *this;}



//OPERADORES DE INSERCION Y EXTRACCION EN FLUJO
istream& operator>>(istream& is, Fecha& fe)
{
	char entry[50];
	is >> entry;
	int ndia, nmes, nanno;
	int n = sscanf(entry, "%02d/%02d/%04d", &ndia, &nmes, &nanno);
	if (n != 3) {
		is.setstate(ios::failbit);
		throw Fecha::Invalida("Error por formato incorrecto");
	}
	else
	{
		try {
			Fecha a(entry);
			fe = a;
		} catch (const Fecha::Invalida& e){
			is.setstate(ios::failbit);
			throw e;
		}
		return is;
	}
}

ostream& operator<<(ostream& os, const Fecha& fe)
{ os << fe.cadena();  return os;}







void Fecha::valida()
{
    if(mes_ < 1 || mes_ > 12)
    {
    	Fecha::Invalida incorrect_month("Mes introducido es incorrecto");
			throw incorrect_month;
		}

    if(anno_ < AnnoMinimo || anno_ > AnnoMaximo)
    {
    	Fecha::Invalida incorrect_year("Anno introducido es incorrecto");
			throw incorrect_year;
		}

		if (mes_ == 1 || mes_ == 3 || mes_ == 5 || mes_ == 7 || mes_ == 8 || mes_ == 10 || mes_ == 12)
		{
			if (dia_ < 1 || dia_ > 31)
				throw Invalida("Dia introducido es incorrecto");
		}
		else if (mes_ == 4 || mes_ == 6 || mes_ == 9 || mes_ == 11)
		{
			if (dia_ < 1 || dia_ > 30)
				throw Invalida("Dia introducido es incorrecto");
		}
				else if (mes_ == 2)
				{
					if (anno_ % 4 == 0 && (anno_ % 400 == 0 || anno_ % 100 != 0))
					{
							if (dia_ < 1 || dia_ > 29)
							throw Invalida("Dia introducido es incorrecto");
						}
						else
						{
							if (dia_ < 1 || dia_ > 28)
							throw Invalida("Dia introducido es incorrecto");
						}
					}
}
