//LIBRERIAS
#include<iostream>
#include<cstdio>
#include<cstring>
#include<stdexcept>
#include<iomanip>
#include "cadena.hpp"


using namespace std;
//
//CONSTRUCTORES
//

Cadena::Cadena(size_t x, char y) :  s_{new char[x+1]}, tam_{x}
{
	size_t i=0;
	while(i<x) { s_[i] = y;	i++; }
	s_[x]='\0';
}
//COPIA
Cadena::Cadena(const Cadena& cad) : s_{new char[cad.tam_+1]}, tam_{cad.tam_}
{	strcpy(s_,cad.s_);	}

//CONVERSION DESDE CADENA DE BAJO NIVEL
Cadena::Cadena(const char* c) : 	s_{new char[strlen(c) + 1]}, tam_{strlen(c)}
{	strcpy(s_, c);	}

//CONSTRUCTOR DE MOVIMIENTO
Cadena::Cadena(Cadena&& c) : s_(c.s_), tam_(c.tam_)
{
	c.tam_ = 0;
	c.s_ = new char[1];
	c.s_[0] = '\0';
}

//ASIGNACIÓN
Cadena& Cadena::operator =(const Cadena& c)
{
	if(this != &c)
	{
			tam_ = c.tam_;
			delete[] s_;
			s_ = new char[c.tam_ + 1];
			strcpy(s_, c.s_);
	}
	return *this;
}
//ASIGNACION DESDE CADENA DE BAJO NIVEL
Cadena& Cadena::operator=(const char *c)
{
	{
		if (*this != c) {
			tam_ = strlen(c);
			delete[] s_;
			s_ = new char[tam_+1];
			strcpy(s_, c);
		}
		return *this;
	}
}
//ASIGNACION POR MOVIMIENTO
Cadena& Cadena::operator=(Cadena&& c) {
	if (*this != c) {
		tam_ = c.tam_;
		delete[] s_;
		s_ = c.s_;
	}
	c.s_ = new char [1];
	c.s_[0] = '\0';
	c.tam_ = 0;
	return *this;
}

//CONCATENADOR DE CADENAS
Cadena& Cadena::operator +=(const Cadena& c)
{
	if (tam_ != 0 && c.tam_ != 0) {
	char * aux = new char[tam_ + c.tam_ + 1];
	strcpy(aux, s_);
	strcat(aux, c.s_);
	tam_ = tam_ + c.tam_;
	delete[] s_;
	s_ = new char[tam_ + 1];
	strcpy(s_, aux);
	s_[tam_] = '\0';
	delete[] aux;
}
return *this;
}

Cadena	operator	+(const Cadena& c1, const Cadena& c2)
{
	Cadena nueva(c1);
	nueva += c2;
	return nueva;
}

//SOBRECARGA INDICE

char& Cadena::operator[](size_t x)
{
	return s_[x];
}
const char& Cadena::operator[](size_t x) const
{
	return s_[x];
}

char& Cadena::at(size_t x)
{
	if(x >= tam_)
		throw std::out_of_range("Error en metodo at (version no const): Fuera de rango");
	return s_[x];
}

const char& Cadena::at(size_t x) const
{
	if(x >= tam_)
		throw std::out_of_range("Error en metodo at (version const): Fuera de rango");
	return s_[x];
}

//GENERADOR SUBCADENA
Cadena Cadena::substr(int indice, int t) const
{

	if (indice + t <= tam_ && indice >= 0 && t >= 0) {
		char * s = new char[t+1];
		int i = 0;
		int fin = indice + t;
		while (indice < fin)
		{
			s[i] = s_[indice];
			i++;
			indice++;
		}
		s[t] = '\0';
		Cadena Return(s);
		delete[] s;
		return Return;
	}
	else
		throw std::out_of_range("Se ha producido un error con el tamaño y/o indice substr.");

}

//OPERADORES DE EXTRACCION E INSERCION DEL FLUJO
ostream& operator<<(ostream& os, const Cadena& c) {
	os << (const char *)c;
	return os;
}

istream& operator>>(istream& is, Cadena& c) {
	char entry[33];
  if (is>>setw(33)>>entry) {
	Cadena aux(entry);
	c=aux;
} else {
		c="";
	}
return is;
}



//DESTRUCTOR
Cadena::~Cadena()
{ delete[] s_;	tam_ = 0;}
