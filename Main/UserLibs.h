#pragma once
#include "productos.h"

/// ACA VAN LAS ESTRUCTURAS Y PROTOTIPADOS

typedef struct
{
    producto dato;
    int cantidad;
    float subtotal;
    int flag;
} subVenta;

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

///// ESTRUCTURAS USER LIBS
typedef struct
{
    subVenta dato;
    struct nodoListaDSubVenta *sig;
    struct nodoListaDSubVenta *ant;
} nodoListaDSubVenta;

/// ESTRUCTURAS MENU USUARIO
typedef struct
{
    usuario dato;
    struct nodoProductoD *siguiente;
    struct nodoProductoD *anterior;
} nodoUsuarioD;

/// ESTRUCTURAS LISTA PILAS SUBVENTAS
typedef struct
{
    venta dato;
    struct nodoVentaS *siguiente;
} nodoVentaS;

typedef struct
{
    nodoVentaS *lista;
} Pila;

typedef struct
{
    venta dato;
    struct nodoVentaD *siguiente;
    struct nodoVentaD *anterior;
} nodoVentaD;

/// FUNCIONES
void AltaUsuario();
int verificarPorUserName(char User[]);
usuario pedirDatos();
int contadorRegistros();
void mostrarCliente(usuario Aux);
void showArchiveClientes();
void AltaAdmin();
void mostrarAdmin();
void BajaCliente(usuario A);
usuario BuscarUnClientePorUserName(char nombreUsuario[]);
usuario modificarDatosCliente(usuario A);
void modificarUnCliente(usuario A);
usuario BuscarUnClientePorID(int IdUsuario);
int VerificarPorID(int IdCliente);
void verInformacionUsuarioID();
void verUnCliente();
void modificarClienteMenu();
usuario modificarEstadoContable(usuario A);
void modificarEstadoCliente(usuario A);
void modificarEstadoClienteMenu();

/// FUNCIONES MENU USUARIOS
int mostrarUsuarios(int id, int cursor);
int obtenerIdUsuarioList(nodoUsuarioD *lista, int cursor);
nodoUsuarioD *despersistirListaDobleusuarios(nodoUsuarioD *lista);
void mostrarusuarioCorto(usuario aux);
nodoUsuarioD *inicListaDobleusuario();
nodoUsuarioD *crearNodoDobleusuario(usuario A);
nodoUsuarioD *buscarUltimoDobleusuario(nodoUsuarioD *lista);
nodoUsuarioD *agregarAlFinalDobleusuario(nodoUsuarioD *lista, nodoUsuarioD *nuevoNodo);
int contarOpcionesusuarios(nodoUsuarioD *lista);
void mostrarOpcionesUsuarios(nodoUsuarioD *lista, int cursor);
int capturarTecla3();
/// OTRAS
void saldoDisponible(int id);
/// BASICAS LISTAS SIMPLES SUBVENTAS
nodoVentaS *inicLista();
nodoVentaS *crear(venta dato);
nodoVentaS *agregarPrincipio(nodoVentaS *lista, nodoVentaS *nuevonodoVentaS);
nodoVentaS *buscarUltimo(nodoVentaS *lista);
nodoVentaS *agregar(nodoVentaS *lista, nodoVentaS *nuevonodoVentaS);
void mostrarLista(nodoVentaS *lista);
/// PILAS SUBVENTA
void inicPila(Pila *p);
void apilar(Pila *p, venta dato);
venta desapilar(Pila *p);
venta tope(Pila *p);
int pilavacia(Pila *p);
void mostrar(Pila *p);
/// BASICAS LISTAS DOBLES SUBVENTAS
nodoVentaD *inicListaDobleVenta();
nodoVentaD *crearNodoDobleVenta(venta A);
nodoVentaD *buscarUltimoDobleVenta(nodoVentaD *lista);
nodoVentaD *agregarAlFinalDobleVenta(nodoVentaD *lista, nodoVentaD *nuevoNodo);
int contarOpcionesVentas(nodoVentaD *lista);
/// MOSTRAR HISTORIAL DE VENTAS
int historialComprasId(int id, int cursor);
/// MOSTRAR HISTORIAL TODAS LAS COMPRAS
int historialComprasTodas(int id, int cursor);
void mostrarOpcionesVentaTodas(nodoVentaD *lista, int cursor);
void cancelarVentaMenu(int idUsuario);
void cancelarCompraMenu(int idUsuario);
usuario cancelarVentaEnArray(usuario A, int idVenta);
void cancelarVentaEnArchivoUsuarios(int idUsuario);
void cancelarVentaEnArchivoVentas(int idVenta);
float calcularSubTotal(int idUsuario);
int cancelarVentaAdmin(int idUsuario, int idVenta);
int cancelarVenta(int idUsuario, int idVenta);

