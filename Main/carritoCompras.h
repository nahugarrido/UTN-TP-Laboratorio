#pragma once
#include "productos.h"
#include "UserLibs.h"
#include "sistema.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#define KEY_UP 72 + 256
#define KEY_DOWN 80 + 256
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_LEFT 75 + 256
#define KEY_RIGHT 77 + 256
#define KEY_S 83
#define KEY_s 115

/// ACA VAN LAS ESTRUCTURAS Y PROTOTIPADOS

/// PROTOTIPADO DE LISTAS
nodoListaDSubVenta *agregarAlFinalDSubVenta(nodoListaDSubVenta *lista, nodoListaDSubVenta *nuevoNodo);
nodoListaDSubVenta *buscarUltimoDSubVenta(nodoListaDSubVenta *lista);
nodoListaDSubVenta *crearNodoDSubVenta(subVenta A);
nodoListaDSubVenta *inicListaDoblesubVenta();
nodoListaDSubVenta *obtenerSubVenta(usuario A, nodoListaDSubVenta *lista);
nodoListaDSubVenta *borrarnodoListaDSubVenta(nodoListaDSubVenta *lista, int idPedido);
void showListsubVenta(nodoListaDSubVenta *lista);
void mostrarsubVentaCorto(subVenta nombre);
int mostrarsubVentas(int id, int cursor);
void mostrarOpcionesCarrito(nodoListaDSubVenta *lista, int cursor);
nodoListaDSubVenta *obtenerListaDSubVentas(nodoListaDSubVenta *lista);
nodoListaDSubVenta *despersistirListaDSubVenta(nodoListaDSubVenta *lista, int id);
nodoListaDSubVenta *obtenerSubVenta(usuario A, nodoListaDSubVenta *lista);
usuario BuscarUsuario(int idCliente);
producto ObtenerProducto(producto dato);
void verificarStockParaAgregarAlCarrito(int cantidadProductos, int idCliente, producto Dato);
//int sumarIgualesDelCarrito(int cantidad, producto Dato, int idCliente);
///
int contarOpcionessubVentas(nodoListaDSubVenta *lista);
int mostrarsubVentas(int id, int cursor);
int capturarTeclaCarrito();
void suma();
