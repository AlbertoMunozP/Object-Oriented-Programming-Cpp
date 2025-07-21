

#ifndef TEST_AUTO_HPP_
#define TEST_AUTO_HPP_

#if !defined(P0) && !defined(P1) && !defined(P2) && !defined(P3) && !defined(P4)
#error Debe definir Px siendo x | 0 <= x <= 4 el n.º de la práctica a probar
#endif

#include <ctime>
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <memory>
#include <type_traits>
#include <locale>

#if __GLIBCXX__ >= 20160301
# define CPP11REGEX 1
# include <regex>
#else
# include <regex.h>
#endif

#include "fct.h"

#include "fecha.hpp"
#include "cadena.hpp"
#if defined(P2) || defined(P3) || defined(P4)
# include "articulo.hpp"
# include "tarjeta.hpp"
# include "usuario.hpp"
#endif
#if defined(P3) || defined(P4)
# include "pedido.hpp"
# include "pedido-articulo.hpp"
# include "usuario-pedido.hpp"
#endif


#define chk_incl_str(haystack, needle)                       \
  fct_xchk(strstr(haystack.c_str(), needle.c_str()) != NULL, \
           "failed chk_incl_str:\n'%s' not in '%s'",         \
           needle.c_str(), haystack.c_str())

#define chk_incl_cstr(haystack, needle)                      \
  fct_xchk(strstr(haystack.c_str(), needle) != NULL,         \
           "failed chk_incl_cstr:\n'%s' not in '%s'",        \
           (const char*)needle, haystack.c_str())

#define chk_eq_str(haystack, needle)                         \
  fct_xchk(strcmp(haystack.c_str(), needle.c_str()) == 0,    \
           "failed chk_eq_str:\n'%s' != '%s'",               \
           needle.c_str(), haystack.c_str())

#define chk_eq_cstr(haystack, needle)                        \
  fct_xchk(strcmp(haystack.c_str(), needle) == 0,            \
           "failed chk_eq_cstr:\n'%s' != '%s'",              \
	   (const char*)needle, haystack.c_str())


#ifndef CPP11REGEX

class BadRegex : public std::exception {
public:
  BadRegex(const char* regex) : regex_(regex) {}
  const char* regex() const { return regex_; }
private:
  const char* regex_;
};
#endif


#if !defined(P0) && !defined(P1)

inline bool operator ==(const Numero& a, const Numero& b) 
{
  return !(a < b) && !(b < a);
}
#endif


struct sin_separador : std::numpunct<char> {
protected:
  virtual string_type do_grouping     () const { return "\000"; }
  virtual char_type   do_decimal_point() const { return ','   ; }
};


template <typename T>
std::string toString(const T& o) 
{
  std::ostringstream os;
  os.imbue(std::locale(std::locale("es_ES.UTF-8"), new sin_separador()));
  os << o;
  return os.str();
}


std::string toEuros(double cantidad);

#ifdef P4

Articulo::Autores crea_autores(Autor& autor);
#endif

#ifndef CPP11REGEX

regoff_t find_regex(const char* regex, const char* text) noexcept(false);
#endif

#endif
