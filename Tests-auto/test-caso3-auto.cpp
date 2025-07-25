

#include "test-auto.hpp"

using namespace std;

namespace {
  const Cadena referencia("1234XYZ");
  const Cadena titulo("Prueba");
  const Fecha  fecha(10, 10, 2000);
  const Cadena sId("pperez");
  const Cadena sNombre("Perico");
  const Cadena sApellidos("Perez Palotes");
  const Cadena sDireccion("13 Rue del Percebe");
  const Clave  clave("pedrofueacomprarpan");
  const Numero nTarjeta("01234 56789 012 8");
  const Numero nTarjeta2("01234567890128");
  const Numero nTarjeta3("11234567890126");
  const Fecha  fHoy;
  const Fecha  fUnaSemana = fHoy + 7;
  const Fecha  fSiguienteAnno(1, 1, fHoy.anno() + 1);
#ifdef P4
  Autor autor("Harry", "Potter", "Hogwarts");
  Articulo::Autores autores { &autor };
  Libro articulo1(autores, "111", "The Standard Template Library",
		  fHoy, 42.10, 200, 50);
  Revista articulo2(autores, "110", "Programadores de C++",
		     fHoy, 11.95, 136, 30, 50);
#else
  Articulo articulo1("111", "The Standard Template Library", fHoy, 42.10, 50),
    articulo2("110", "Fundamentos de C++", fHoy, 35.95, 50);
#endif

  Usuario* pU { nullptr };
    
  Usuario_Pedido  *pAsocUsuarioPedido;
  Pedido_Articulo *pAsocPedidoArticulo;
  Usuario         *pU2;
  Tarjeta         *pTarjetaU;
  const Tarjeta   *pTarjetaU2;
  const Fecha     fAyer = fHoy - 1;
  
  const Pedido  *pPed1, *pPed2;
  const unsigned cantidad_A1_P1 = 1;
  const unsigned cantidad_A1_P2 = 3;
  const unsigned cantidad_A2_P2 = 5;
  
  bool bPrimera = true;

  using TIPO = Tarjeta::Tipo;

#if defined(P3) || defined(P4)
  struct Usu_Ped {
      typedef std::set<Pedido*> Pedidos;

      std::map<Usuario*, Pedidos> pedidos_;
      std::map<Pedido*, Usuario*> cliente_;
  };

  struct Ped_Art {
    typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido; 
    typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos; 

    std::map<Pedido  *, ItemsPedido, OrdenaPedidos  > pedidos_articulos_;
    std::map<Articulo*, Pedidos    , OrdenaArticulos> articulos_pedidos_;
  };
#endif
}

FCTMF_FIXTURE_SUITE_BGN(test_p3_clases) {

  if (bPrimera) {
    bPrimera = false;
    cerr << "\n---------- PRÁCTICA 3 ----------\n" << endl;
  }


  FCT_TEST_BGN(LineaPedido - valor por defecto en 2do. parametro constructor) {
    const double pVenta  {  10.5  };
    const LineaPedido lp { pVenta /* , 1u */};
    fct_chk_eq_dbl(lp.precio_venta(), pVenta);
    fct_chk_eq_int(lp.cantidad    (),      1);
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(LineaPedido - constructor de 2 parametros) {
    const double      pVenta   { 7.3 };
    const unsigned    cantidad { 5   };
    const LineaPedido lp       { pVenta, cantidad };
    fct_chk_eq_dbl(lp.precio_venta(), pVenta  );
    fct_chk_eq_int(lp.cantidad()    , cantidad);
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(LineaPedido - insercion en flujo) {
    const LineaPedido lp { 9.2, 42 };
    chk_incl_cstr(toString(lp), "9,20 €");
    chk_incl_cstr(toString(lp), "42");
  }
  FCT_TEST_END();

  FCT_SETUP_BGN() {
    pAsocUsuarioPedido  = new Usuario_Pedido ;
    pAsocPedidoArticulo = new Pedido_Articulo;
    pU  = new Usuario(sId, sNombre, sApellidos, sDireccion, clave);
    pU2 = new Usuario("u2", "Mario", "Segali", "Mundo 1-1", "jumpman");
    pTarjetaU  = new Tarjeta(nTarjeta , *pU , fUnaSemana);
    pTarjetaU2 = new Tarjeta(nTarjeta3, *pU2, fUnaSemana);
  }
  FCT_SETUP_END();

  FCT_TEARDOWN_BGN() {
    delete pTarjetaU2;
    delete pTarjetaU;
    delete pU2;
    delete pU;
    delete pAsocPedidoArticulo;
    delete pAsocUsuarioPedido;
  }
  FCT_TEARDOWN_END();


  FCT_TEST_BGN(Pedido - carrito vacio) {
    Usu_Ped* pU_P = reinterpret_cast<Usu_Ped*>(pAsocUsuarioPedido);
    Ped_Art* pP_A = reinterpret_cast<Ped_Art*>(pAsocPedidoArticulo);
    try {
      Pedido {*pAsocUsuarioPedido, *pAsocPedidoArticulo, *pU, *pTarjetaU, fHoy};
      fct_xchk(false, "Se esperaba una excepción Pedido::Vacio");
    }
    catch(const Pedido::Vacio& ex) {
      fct_chk(&ex.usuario() == pU);
      fct_xchk(pU_P->pedidos_.empty(), "En pedido no viable: "
              "enlace Usuario-Pedido incorrecto.");
      fct_xchk(pU_P->cliente_.empty(), "En pedido no viable: "
              "enlace Pedido-Usuario incorrecto.");
      fct_xchk(pP_A->pedidos_articulos_.empty(), "En pedido no viable: "
              "enlace Pedido-Articulo incorrecto.");
      fct_xchk(pP_A->articulos_pedidos_.empty(), "En pedido no viable: "
              "enlace Articulo-Pedido incorrecto.");
    }
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Pedido - impostor) {
    Usu_Ped* pU_P = reinterpret_cast<Usu_Ped*>(pAsocUsuarioPedido);
    Ped_Art* pP_A = reinterpret_cast<Ped_Art*>(pAsocPedidoArticulo);
    pU2->compra(articulo1, 3);
    try {
      Pedido {*pAsocUsuarioPedido, *pAsocPedidoArticulo, *pU2, *pTarjetaU, fHoy};
      fct_xchk(false, "Se esperaba una excepción Pedido::Impostor");
    }
    catch(const Pedido::Impostor& ex) {
      fct_chk(&ex.usuario() == pU2);
      fct_xchk(articulo1.stock() == 50, "En pedido no viable: "
              "articulo1.stock() == %d != 50", articulo1.stock());
      fct_xchk(pU_P->pedidos_.empty(), "En pedido no viable: "
              "enlace Usuario-Pedido incorrecto.");
      fct_xchk(pU_P->cliente_.empty(), "En pedido no viable: "
              "enlace Pedido-Usuario incorrecto.");
      fct_xchk(pP_A->pedidos_articulos_.empty(), "En pedido no viable: "
              "enlace Pedido-Articulo incorrecto.");
      fct_xchk(pP_A->articulos_pedidos_.empty(), "En pedido no viable: "
              "enlace Articulo-Pedido incorrecto.");
      articulo1.stock() = 50;
    }
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(Pedido - sin stock) {
    Usu_Ped* pU_P = reinterpret_cast<Usu_Ped*>(pAsocUsuarioPedido);
    Ped_Art* pP_A = reinterpret_cast<Ped_Art*>(pAsocPedidoArticulo);
    pU->compra(articulo1, 9001);
    pU->compra(articulo2, 5);
    try {
      Pedido {*pAsocUsuarioPedido, *pAsocPedidoArticulo, *pU, *pTarjetaU, fHoy};
      fct_xchk(false, "Se esperaba una excepción Pedido::SinStock");
    }
    catch (const Pedido::SinStock& ex) {
      fct_chk(&ex.articulo() == &articulo1);
      fct_xchk(pU->compra().empty(), "Pedido sin stock: carrito no vaciado.");
      fct_xchk(articulo1.stock() == 50, "Vendido artículo de un pedido sin stock: "
              "articulo1.stock() == %d != 50", articulo1.stock());
      fct_xchk(articulo2.stock() == 50, "Vendido artículo de un pedido sin stock: "
              "articulo2.stock() == %d != 50", articulo2.stock());
      fct_xchk(pU_P->pedidos_.empty(), "Vendido artículo de un pedido sin stock: "
              "enlace Usuario-Pedido incorrecto.");
      fct_xchk(pU_P->cliente_.empty(), "Vendido artículo de un pedido sin stock: "
              "enlace Pedido-Usuario incorrecto.");
      fct_xchk(pP_A->pedidos_articulos_.empty(), "Vendido artículo de un pedido sin stock: "
              "enlace Pedido-Articulo incorrecto.");
      fct_xchk(pP_A->articulos_pedidos_.empty(), "Vendido artículo de un pedido sin stock: "
              "enlace Articulo-Pedido incorrecto.");
      articulo1.stock() = 50;
      articulo2.stock() = 50;
      pU_P->pedidos_.clear();
      pU_P->cliente_.clear();
      pP_A->pedidos_articulos_.clear();
      pP_A->articulos_pedidos_.clear();
    }
    pU->compra(articulo1, 5);
    pU->compra(articulo2, 9001);
    try {
      Pedido {*pAsocUsuarioPedido, *pAsocPedidoArticulo, *pU, *pTarjetaU, fHoy};
      fct_xchk(false, "Se esperaba una excepción Pedido::SinStock");
    }
    catch (const Pedido::SinStock& ex) {
      fct_chk(&ex.articulo() == &articulo2);
      fct_xchk(pU->compra().empty(), "Pedido sin stock: carrito no vaciado.");
      fct_xchk(articulo1.stock() == 50, "Vendido artículo de un pedido sin stock: "
              "articulo1.stock() == %d != 50", articulo1.stock());
      fct_xchk(articulo2.stock() == 50, "Vendido artículo de un pedido sin stock: "
              "articulo2.stock() == %d != 50", articulo2.stock());
      fct_xchk(pU_P->pedidos_.empty(), "Vendido artículo de un pedido sin stock: "
              "enlace Usuario-Pedido incorrecto.");
      fct_xchk(pU_P->cliente_.empty(), "Vendido artículo de un pedido sin stock: "
              "enlace Pedido-Usuario incorrecto.");
      fct_xchk(pP_A->pedidos_articulos_.empty(), "Vendido artículo de un pedido sin stock: "
              "enlace Pedido-Articulo incorrecto.");
      fct_xchk(pP_A->articulos_pedidos_.empty(), "Vendido artículo de un pedido sin stock: "
              "enlace Articulo-Pedido incorrecto.");
      articulo1.stock() = 50;
      articulo2.stock() = 50;
      pU_P->pedidos_.clear();
      pU_P->cliente_.clear();
      pP_A->pedidos_articulos_.clear();
      pP_A->articulos_pedidos_.clear();
    }
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(Pedido - tarjeta caducada) {
    Usu_Ped* pU_P = reinterpret_cast<Usu_Ped*>(pAsocUsuarioPedido);
    Ped_Art* pP_A = reinterpret_cast<Ped_Art*>(pAsocPedidoArticulo);
    pU->compra(articulo1, 4);
    try {
      Pedido {*pAsocUsuarioPedido, *pAsocPedidoArticulo, *pU, *pTarjetaU, fHoy + 30};
      fct_xchk(false, "Se esperaba una excepción Tarjeta::Caducada");
    }
    catch (const Tarjeta::Caducada& ex) {
      fct_chk(ex.cuando() == fUnaSemana);

      fct_xchk(articulo1.stock() == 50, "En pedido no viable: "
              "articulo1.stock() == %d != 50", articulo1.stock());
      fct_xchk(pU_P->pedidos_.empty(), "En pedido no viable: "
              "enlace Usuario-Pedido incorrecto.");
      fct_xchk(pU_P->cliente_.empty(), "En pedido no viable: "
              "enlace Pedido-Usuario incorrecto.");
      fct_xchk(pP_A->pedidos_articulos_.empty(), "En pedido no viable: "
              "enlace Pedido-Articulo incorrecto.");
      fct_xchk(pP_A->articulos_pedidos_.empty(), "En pedido no viable: "
              "enlace Articulo-Pedido incorrecto.");
      articulo1.stock() = 50;
    }
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Pedido - tarjeta desactivada) {
    Usu_Ped* pU_P = reinterpret_cast<Usu_Ped*>(pAsocUsuarioPedido);
    Ped_Art* pP_A = reinterpret_cast<Ped_Art*>(pAsocPedidoArticulo);
    pU->compra(articulo2, 4);
    pTarjetaU->activa(false);
    try {
      Pedido(*pAsocUsuarioPedido, *pAsocPedidoArticulo, *pU, *pTarjetaU, fHoy);
      fct_xchk(false, "Se esperaba una excepción Tarjeta::Caducada");
    }
    catch (const Tarjeta::Desactivada& ex) {
      fct_xchk(articulo2.stock() == 50, "En pedido no viable: "
              "articulo1.stock() == %d != 50", articulo1.stock());
      fct_xchk(pU_P->pedidos_.empty(), "En pedido no viable: "
              "enlace Usuario-Pedido incorrecto.");
      fct_xchk(pU_P->cliente_.empty(), "En pedido no viable: "
              "enlace Pedido-Usuario incorrecto.");
      fct_xchk(pP_A->pedidos_articulos_.empty(), "En pedido no viable: "
              "enlace Pedido-Articulo incorrecto.");
      fct_xchk(pP_A->articulos_pedidos_.empty(), "En pedido no viable: "
              "enlace Articulo-Pedido incorrecto.");
      articulo2.stock() = 50;
    }
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(Pedido - actualizacion relacionados y asociaciones) {
    const unsigned int cantidad { 1u };
    pU->compra(articulo1, cantidad);
    pU->compra(articulo2, cantidad);
    const unique_ptr<const Pedido> pPed {
      new Pedido {*pAsocUsuarioPedido, *pAsocPedidoArticulo, *pU, *pTarjetaU, fHoy} 
    };
    
    fct_xchk(pU->compra().empty(), "Carrito no vacío tras ralizar pedido.");
    fct_xchk(articulo1.stock() == 49, "Existencias de articulo no actualizadas: "
            "articulo1.stock() == %d != 49", articulo1.stock());
    fct_xchk(articulo2.stock() == 49, "Existencias de articulo no actualizadas: "
            "articulo2.stock() == %d != 49", articulo2.stock());
    
    fct_xchk(pAsocUsuarioPedido->cliente(*const_cast<Pedido*>(pPed.get())) == pU,
             "El usuario asociado al pedido no es el comprador.");
    if (pAsocUsuarioPedido->pedidos(*pU).size() == 1) {
      fct_xchk(*pAsocUsuarioPedido->pedidos(*pU).begin() == pPed.get(),
               "El pedido asociado no corresponde al comprador.");
    }
    else
      fct_xchk(false, "El número de pedidos asociados al usuario debe ser 1.");
    
    const Pedido_Articulo::ItemsPedido itPed {
      pAsocPedidoArticulo->detalle(* const_cast<Pedido*>(pPed.get())) 
	  };
    if (itPed.size() == 2) {
      auto it = itPed.cbegin();
      fct_xchk(it->first == &articulo2,
               "Artículo inesperado o desordenado en pedido.");
      fct_xchk(it->second.cantidad() == cantidad, "Cantidad incorrecta "
               "en pedido: %d != %d", it->second.cantidad(), cantidad);
      fct_xchk(it->second.precio_venta() == articulo2.precio(),
               "Precio de venta incorrecto en pedido: %f != %f",
               it->second.precio_venta(), articulo2.precio());
      ++it;
      fct_xchk(it->first == &articulo1,
               "Artículo inesperado o desordenado en pedido.");
      fct_xchk(it->second.cantidad() == cantidad, "Cantidad incorrecta "
               "en pedido: %d != %d", it->second.cantidad(), cantidad);
      fct_xchk(it->second.precio_venta() == articulo1.precio(),
               "Precio de venta incorrecto en pedido: %f != %f",
               it->second.precio_venta(), articulo1.precio());
    }
    else
      fct_xchk(false, "El pedido debería tener 2 artículos");
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(Pedido - observadores) {
    pU->compra(articulo1, 1);
    pU->compra(articulo2, 1);
    const double totalEsperado {articulo1.precio() + articulo2.precio()};
    const unique_ptr<const Pedido> pPed {
      new Pedido {*pAsocUsuarioPedido, *pAsocPedidoArticulo, *pU, *pTarjetaU}
    };
    fct_xchk(pPed->numero() == 2, "Número de pedido incorrecto: "
             "pPed->numero() == %d != %d", pPed->numero(), 2);
    fct_xchk(pPed->tarjeta() == pTarjetaU,
             "La tarjeta asociada al pedido no es la del pago.");
    fct_xchk(pPed->fecha() == fHoy, "Fecha del pedido incorrecta.");
    fct_xchk(pPed->total() == totalEsperado, "Importe total de pedido incorrecto: "
             "pPed->total() == %f != %f", pPed->total(), totalEsperado);
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(Pedido - insercion en flujo) {
    pU->compra(articulo1, 1);
    pU->compra(articulo2, 1);
    const double totalEsperado {articulo1.precio() + articulo2.precio()};
    const unique_ptr<const Pedido> pPed {
      new Pedido {*pAsocUsuarioPedido, *pAsocPedidoArticulo, *pU, *pTarjetaU}
    };
    const string sPed {toString(*pPed)};
    chk_incl_cstr(sPed, "Núm. pedido:");
    chk_incl_cstr(sPed, "Fecha:"      );
    chk_incl_cstr(sPed, "Pagado con:" );
    chk_incl_cstr(sPed, "Tipo indeterminado" );
    chk_incl_cstr(sPed, "Importe:"    );
    chk_incl_str (sPed, toString(pPed->numero()));
    chk_incl_cstr(sPed, pPed->fecha().cadena()  );
    chk_incl_cstr(sPed, pTarjetaU->numero()     );
    chk_incl_str (sPed, toEuros(totalEsperado)  );
  }
  FCT_TEST_END();
  

  FCT_TEST_BGN(Pedido---Articulo - detalle de un pedido) {
    pU->compra(articulo1, 1);
    const unique_ptr<const Pedido> pPed {
      new Pedido { *pAsocUsuarioPedido, *pAsocPedidoArticulo,
	  *pU, *pTarjetaU, fHoy }
    };
    const Pedido_Articulo::ItemsPedido detalle {
      pAsocPedidoArticulo->detalle(*const_cast<Pedido*>(pPed.get()))
	};
    if (detalle.size() == 1) {
      const auto& it = detalle.cbegin();
      const LineaPedido& lp { detalle.cbegin()->second };
      fct_chk(it->first == &articulo1);
      fct_chk_eq_dbl(lp.precio_venta(), articulo1.precio());
      fct_chk_eq_int(lp.cantidad(), 1);
    }
    else
      fct_chk(!"El pedido debería tener un solo elemento");
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(Pedido---Articulo - insercion en flujo de ItemsPedido) {
    const unsigned int cantidad { 1u };
    pU->compra(articulo1, cantidad);
    const unique_ptr<const Pedido> pPed {
      new Pedido { *pAsocUsuarioPedido, *pAsocPedidoArticulo,
	  *pU, *pTarjetaU, fHoy }
    };
    const Pedido_Articulo::ItemsPedido detalle {
      pAsocPedidoArticulo->detalle(*const_cast<Pedido*>(pPed.get()))
	};
    const string sDetalle { toString(detalle) };
    chk_incl_str(sDetalle, toString(pPed->total()));
    chk_incl_str(sDetalle, toString(cantidad));
  }
  FCT_TEST_END();
}
FCTMF_FIXTURE_SUITE_END()

FCTMF_FIXTURE_SUITE_BGN(test_p3_informes) {

  FCT_SETUP_BGN() {
    pAsocUsuarioPedido  = new Usuario_Pedido ;
    pAsocPedidoArticulo = new Pedido_Articulo;
    pU  = new Usuario(sId, sNombre, sApellidos, sDireccion, clave);
    pU2 = new Usuario("u2", "Mario", "Segali", "Mundo 1-1", "jumpman");
    pTarjetaU  = new Tarjeta(nTarjeta, *pU, fUnaSemana);
    pTarjetaU2 = new Tarjeta(nTarjeta3,*pU2,fUnaSemana);

    pU->compra(articulo1, cantidad_A1_P1);
    pPed1 = new Pedido(*pAsocUsuarioPedido, *pAsocPedidoArticulo, 
		       *pU, *pTarjetaU, fHoy);

    pU2->compra(articulo1, cantidad_A1_P2);
    pU2->compra(articulo2, cantidad_A2_P2);
    pPed2 = new Pedido(*pAsocUsuarioPedido, *pAsocPedidoArticulo,
                       *pU2, *pTarjetaU2, fHoy);
  };
  FCT_SETUP_END();

  FCT_TEARDOWN_BGN() {
    delete pPed2;
    delete pPed1;
    delete pTarjetaU2;
    delete pTarjetaU;
    delete pU2;
    delete pU;
    delete pAsocPedidoArticulo;
    delete pAsocUsuarioPedido;
  }
  FCT_TEARDOWN_END();

  FCT_TEST_BGN(Pedido---Articulo - ventas de un articulo vendido) {
    const auto& pedArticulo1 = pAsocPedidoArticulo->ventas(articulo1);
    if (pedArticulo1.size() == 2) {
      auto it = pedArticulo1.find(const_cast<Pedido*>(pPed1));
      fct_chk_eq_dbl(it->second.precio_venta(), articulo1.precio());
      fct_chk_eq_int(it->second.cantidad(), cantidad_A1_P1);
      ++it;
      fct_chk_eq_dbl(it->second.precio_venta(), articulo1.precio());
      fct_chk_eq_int(it->second.cantidad(), cantidad_A1_P2);
    }
    else
      fct_chk(!"El artículo 1 debería tener 2 ventas");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Pedido---Articulo - ventas de un articulo no comprado) {
#ifdef P4
    Autor Hitler("Adolf", "Hitler", "Berlin");
    Articulo::Autores a { &Hitler };
    Libro MeinKampf(a, "666", "Mein Kampf", fHoy, 55.55, 555);
#else
    Articulo MeinKampf { "666", "Mein Kampf", fHoy, 55.55, 555 };
#endif
    const auto& pedArticulo3 = pAsocPedidoArticulo->ventas(MeinKampf);
    fct_chk(pedArticulo3.empty());
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Pedido---Articulo - insercion en flujo de Pedidos) {
    const auto& pedArticulo1 = pAsocPedidoArticulo->ventas(articulo1);
    const string sPedidos { toString(pedArticulo1) };
    
    chk_incl_str(sPedidos,  toString(articulo1.precio()));
    chk_incl_str(sPedidos,  toString(cantidad_A1_P1));
    chk_incl_cstr(sPedidos, pPed1->fecha().cadena());
    chk_incl_str(sPedidos,  toString(cantidad_A1_P2));
    chk_incl_cstr(sPedidos, pPed2->fecha().cadena());
    
    const double totalEsperado =
      (cantidad_A1_P1 + cantidad_A1_P2) * articulo1.precio();
    chk_incl_str(sPedidos, toEuros(totalEsperado));
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(Pedido---Articulo - mostrar detalle pedidos) {
    ostringstream os;
    pAsocPedidoArticulo->mostrarDetallePedidos(os);
    const string sDetalle { os.str() };
    
    const double totalEsperado =
      (cantidad_A1_P1 + cantidad_A1_P2) * articulo1.precio()
      + cantidad_A2_P2 * articulo2.precio();
    chk_incl_str(sDetalle, toEuros(totalEsperado));
    chk_incl_cstr(sDetalle, (const char*)(articulo1.titulo()));
    chk_incl_cstr(sDetalle, (const char*)(articulo2.titulo()));
    chk_incl_str(sDetalle, toString(cantidad_A1_P1));
    chk_incl_str(sDetalle, toString(cantidad_A1_P2));
    chk_incl_str(sDetalle, toString(cantidad_A2_P2));
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Pedido---Articulo - mostrar ventas agrupadas) {
    ostringstream os;
    pAsocPedidoArticulo->mostrarVentasArticulos(os);
    const string sDetalle { os.str() };
    
    const string sRegexPrefijo { "€[[:space:]]+"   }; // "(€[[:space:]]|^)";  
    const string sRegexSufijo  { "([[:space:]]|$)" };
#ifndef CPP11REGEX
    const string 
      sRegexA1P1(sRegexPrefijo + toString(cantidad_A1_P1) + sRegexSufijo),
      sRegexA1P2(sRegexPrefijo + toString(cantidad_A1_P2) + sRegexSufijo),
      sRegexA2P2(sRegexPrefijo + toString(cantidad_A2_P2) + sRegexSufijo);
    const regoff_t 
      posCantidad_A1_P1 = find_regex(sRegexA1P1.c_str(), sDetalle.c_str()),
      posCantidad_A1_P2 = find_regex(sRegexA1P2.c_str(), sDetalle.c_str()),
      posCantidad_A2_P2 = find_regex(sRegexA2P2.c_str(), sDetalle.c_str());
    fct_chk(posCantidad_A1_P1 != -1);
    fct_chk(posCantidad_A1_P2 != -1);
    fct_chk(posCantidad_A2_P2 != -1);
    fct_chk(posCantidad_A2_P2 < posCantidad_A1_P1);
    fct_chk(posCantidad_A1_P1 < posCantidad_A1_P2);
#else
    regex  		
      sRegexA1P1(sRegexPrefijo + toString(cantidad_A1_P1) + sRegexSufijo),
      sRegexA1P2(sRegexPrefijo + toString(cantidad_A1_P2) + sRegexSufijo),
      sRegexA2P2(sRegexPrefijo + toString(cantidad_A2_P2) + sRegexSufijo);
    smatch cantidad_A1_P1, cantidad_A1_P2, cantidad_A2_P2;
    fct_chk(regex_search(sDetalle, cantidad_A1_P1, sRegexA1P1));
    fct_chk(regex_search(sDetalle, cantidad_A1_P2, sRegexA1P2));
    fct_chk(regex_search(sDetalle, cantidad_A2_P2, sRegexA2P2));
    fct_chk(cantidad_A2_P2.position(0) < cantidad_A1_P1.position(0));
    fct_chk(cantidad_A1_P1.position(0) < cantidad_A1_P2.position(0));
#endif
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(Usuario---Pedido - pedidos de un usuario) {
    const auto& pedidosU2 = pAsocUsuarioPedido->pedidos(*pU2);
    if (pedidosU2.size() == 1)
      fct_chk(*pedidosU2.begin() == pPed2);
    else
      fct_chk(!"Debería haber 1 pedido registrado del usuario 2");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Usuario---Pedido - usuario de los pedidos) {
    fct_chk(pAsocUsuarioPedido->cliente(*const_cast<Pedido*>(pPed1)) == pU );
    fct_chk(pAsocUsuarioPedido->cliente(*const_cast<Pedido*>(pPed2)) == pU2);
  }
  FCT_TEST_END();
}
FCTMF_FIXTURE_SUITE_END()
