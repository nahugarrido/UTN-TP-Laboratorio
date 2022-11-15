#include <stdio.h>
#include <stdlib.h>
#include "productos.h"
#include "UserLibs.h"
#include "carritoCompras.h"
#define archivoVentas "Ventas.dat"
///////////
/// PROTOTIPADOS  DE LA FUNCION GENERAR COMPRA. ///
void descontarSaldoAuxiliar(int idUsuario, float gasto);
int verificarSaldo(float saldo, float gasto);
void generarCompra(int idUsuario, float gasto);
void compraConfirmada(int id, float gasto);
void persistirCompraEnUsuarioyVentas(int idUsuario, int idVenta);
void descontarLoDelCarrito(usuario A);
void descontarStock(char aDescontar[100], int cantidad);
void cambiarEstadoSubVenta(char nombreProducto[], int idUsuario);
void quitarProducto(char nombreProducto[], int idUsuario);
usuario BuscarProductoArraySubVenta(usuario A, char producto[]);
venta buscarVentaEnRegistroUsuario(int idVenta, int idUsuario);
int generarIdVenta();
venta buscarUnaVentaEnArray(usuario A, int idVenta);
destino pedirDatosEnvio(destino Aux);
/// PROTOTIPADOS LISTA DOBLE DE VENTAS;
nodoVentaD *despersistirListaDobleVentasExitosas(nodoVentaD *lista);
