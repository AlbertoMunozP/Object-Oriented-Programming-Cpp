#ifndef CADENA_HPP_
#define CADENA_HPP_

#include<cstring>
#include<iterator>

class Cadena {
	public:
		//CONSTRUCTORES
		explicit Cadena(size_t x=0, char y=' ');
		Cadena(const Cadena& cad);
	    Cadena(const char* c);
		Cadena(Cadena&& c);

		//ASIGNACIÓN
		Cadena& operator =(const Cadena& c);
		Cadena& operator= (const char *c);
		Cadena& operator=(Cadena&& c);


		//CONCATENADOR DE CADENAS
		Cadena& operator +=(const Cadena& c);

		//CONVERSOR CADENA A CADENA BAJO NIVEL
		explicit operator const char* () const;

		//SOBRECARGA INDICE
		char& operator[] (size_t x);
		const char& operator[](size_t x) const;

		char& at(size_t x);
		const char& at(size_t x) const;

		//GENERADOR SUBCADENA
		Cadena substr(int indice, int t) const;

		//METODOS OBSERVADORES
		size_t length() const noexcept {return tam_;};

		//ITERADORES
		typedef char * iterator;
		typedef const char * const_iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
		iterator begin() const noexcept { return s_;}
		iterator end() const noexcept { return s_+tam_; }
		const_iterator cbegin() const noexcept { return s_; }
		const_iterator cend() const noexcept { return s_+tam_; }
		reverse_iterator rbegin() const noexcept { return reverse_iterator(end()); }
		reverse_iterator rend() const noexcept { return reverse_iterator(begin()); }
		const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }
		const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }
		//DESTRUCTOR
		~Cadena();

	private:
		char *s_;
		size_t tam_;
};

Cadena operator	+(const Cadena& c1, const Cadena& c2);
//OPERADORES DE COMPARACION DE CADENAS
bool operator ==(const Cadena& c1, const Cadena& c2);
bool operator !=(const Cadena& c1, const Cadena& c2);
bool operator >(const Cadena& c1, const Cadena& c2);
bool operator <(const Cadena& c1, const Cadena& c2);
bool operator >=(const Cadena& c1, const Cadena& c2);
bool operator <=(const Cadena& c1, const Cadena& c2);

//OPERADORES DE EXTRACCION E INSERCION DEL FLUJO
std::ostream& operator<<(std::ostream& os, const Cadena& c);
std::istream& operator>>(std::istream& is, Cadena& c);

//CONVERSOR CADENA A CADENA BAJO NIVEL
inline Cadena::operator const char*() const{return s_;};



// OPERADORES DE COMPARACIÓN
inline bool operator==(const Cadena& cad1, const Cadena& cad2)
{ return(strcmp ((const char*)(cad1.substr(0, cad1.length())), (const char*)(cad2.substr(0, cad2.length()))) == 0); }

inline bool operator!=(const Cadena& cad1, const Cadena& cad2)
{ return (!(cad1 == cad2)); }

inline bool operator<(const Cadena& cad1, const Cadena& cad2)
{ return(strcmp ((const char*)(cad1.substr(0, cad1.length())), (const char*)(cad2.substr(0, cad2.length()))) < 0); }

inline bool operator>(const Cadena& cad1, const Cadena& cad2)
{ return (!(cad1 < cad2) && !(cad1 == cad2)); }

inline bool operator<=(const Cadena& cad1, const Cadena& cad2)
{ return ((cad1 < cad2) || (cad1 == cad2)); }

inline bool operator>=(const Cadena& cad1, const Cadena& cad2)
{ return (!(cad1 < cad2)); }


namespace std {
template <>
struct hash<Cadena> {
size_t operator() (const Cadena& cad) const
{
hash<string> hs;
auto p{(const char*)(cad)};
string s{p};
size_t res{hs(s)};
return res;
}
};
}






#endif
