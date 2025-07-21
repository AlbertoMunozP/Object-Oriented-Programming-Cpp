

#include "test-auto.hpp"


using namespace std;		

#ifdef P4
Articulo::Autores crea_autores(Autor& autor) {
  Articulo::Autores autores { &autor };
  return autores;
}
#endif


string toEuros(double cantidad) {
  ostringstream os;
  os.imbue(locale(locale("es_ES.UTF-8"), new sin_separador()));
  os << fixed << setprecision(2) << cantidad << " €";
  return os.str();
}

#ifndef CPP11REGEX
regoff_t find_regex(const char* regex, const char* text) noexcept(false) {
  regex_t reg;
  if (regcomp(&reg, regex, REG_EXTENDED) != 0)
    throw BadRegex(regex);
  regmatch_t matches[1] = {{-1, -1}};
  regexec(&reg, text, 1, matches, 0);
  regfree(&reg);

  return matches[0].rm_so;
}
#endif


FCT_BGN() {


  try {
    locale::global(locale("es_ES.UTF-8"));
  }
  catch(const runtime_error& e) {
    cerr << "Parece que no tienes la localización española "
      "\"es_ES.UTF-8\". Instálala antes. El mensaje de error es:\n"
	 << e.what() << "\nFin del programa" << endl;
    return 1;
  }

 
#if 0
  FCT_SUITE_BGN(Callar avisos de GCC) {
    FCT_TEST_BGN(callar avisos de GCC) {
      fct_chk(true);
    } FCT_TEST_END();
  }
  FCT_SUITE_END();
#endif

  FCTMF_SUITE_CALL(test_fecha);
  FCTMF_SUITE_CALL(test_cadena);
#if defined(P2) || defined(P3) || defined(P4)
  FCTMF_SUITE_CALL(test_p2);
#endif
#if defined(P3) || defined(P4)
  FCTMF_SUITE_CALL(test_p3_clases);
  FCTMF_SUITE_CALL(test_p3_informes);
#endif
#ifdef P4
  FCTMF_SUITE_CALL(test_p4);
#endif

  cerr << endl;
}
FCT_END()
