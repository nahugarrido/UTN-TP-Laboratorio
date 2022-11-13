#pragma once
#include "productos.h"
/// ACA VAN LAS ESTRUCTURAS Y PROTOTIPADOS

/// ESTRUCTURAS


/// FUNCIONES
int menuProductos2(int id, int cursor);
void mostrarOpcionesProductos2(int cantidadOpciones,opciones arreglo[], int cursor);
void switchProductos(int id, int opcion);

/// FUNCIONES MENU ADMIN PRODUCTOS
void ingresarProductoAbuscar(char productoBuscado[50]);
void buscarProducto(nodoProductoD* listaProductos,char productoBuscado[]);
nodoProductoD* crearNodoDobleProducto(producto aux);
nodoProductoD* despersistirListaDobleProductos(nodoProductoD* lista);
nodoProductoD* agregarAlFinalDobleProducto(nodoProductoD*lista,nodoProductoD*aux2);
void agregarProductoAdmin();
void borrarPantalla();
void buscarProductoFuncion();
void cargarProductoNuevoFuncion();
int seleccionarSiNoMenuProducto(int cursor); /// 1 ES SI 2 ES NO
void mostrarSiNoMenuProducto(int cursor);


