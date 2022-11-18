#include <stdio.h>
#include <stdlib.h>
#define archivoVentas "Ventas.dat"

typedef struct
{
    char nombre[30];
    char descripcion[100];
    float precioVenta;
    float precioCosto;
    int cantidad;
    int flagStock; // 0 en stock // 1 fuera de stock
} producto;

typedef struct
{
    producto dato;
    int cantidad;
    float subtotal;
    int flag;
} subVenta;

typedef struct
{
    subVenta dato;
    struct nodoListaDSubVenta *sig;
    struct nodoListaDSubVenta *ant;
} nodoListaDSubVenta;

typedef struct
{
    char pais[50];
    char provincia[50];
    char ciudad[50];
    char direccion[50];
} destino;

typedef struct
{
    subVenta arreglo[50];
    destino despachar;
    float total;
    int idVenta;
    int idCliente;
    int estadoEnvio; // 0 no despachado // 1 despachado
    int estadoVenta; // 0 normal // 1 cancelada
} venta;

typedef struct
{
    int nroCategoria;
    char nombreCategoria[25];
} categoria;

typedef struct
{
    producto dato;
    struct nodoProductoD *siguiente;
    struct nodoProductoD *anterior;
} nodoProductoD;

typedef struct
{
    categoria Categoria;
    nodoProductoD *lista;
    struct nodoCategorias *siguiente;
    struct nodoCategorias *anterior;

} nodoCategorias;

typedef struct
{
    char username[30]; //
    char password[30]; //
    venta compras[30]; /// Fila
    subVenta carrito[50];
    int validosCarrito;
    int validosCompras;
    float saldo;
    int admin;         // 0 no es admin  // 1 es admin
    int estadoCliente; // 0 baja // 1 alta
    int idCliente;
} usuario;

typedef struct
{
    venta dato;
    struct nodoVentaD *siguiente;
    struct nodoVentaD *anterior;
} nodoVentaD;

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
subVenta BuscarProductoArraySubVenta(usuario A, char producto[]);
venta buscarVentaEnRegistroUsuario(int idVenta, int idUsuario);
int generarIdVenta();
venta buscarUnaVentaEnArray(usuario A, int idVenta);
destino pedirDatosEnvio(destino Aux);
/// PROTOTIPADOS LISTA DOBLE DE VENTAS;
nodoVentaD *despersistirListaDobleVentasExitosas(nodoVentaD *lista);