#pragma once
#include "carritoCompras.h"
/// ACA VAN LAS ESTRUCTURAS Y PROTOTIPADOS
typedef struct
{
    char username[30];     //
    char password[30];     //
    subVenta compras[100]; /// Fila
    subVenta carrito[50];
    int validosCarrito;
    float saldo;
    int admin;         // 0 no es admin  // 1 es admin
    int estadoCliente; // 0 baja // 1 alta
    int idCliente;
} usuario;

///// ESTRUCTURAS USER LIBS
//typedef struct
//{
//    char username[30];     //
//    char password[30];     //
//    venta compras[100]; /// Fila
//    nodoListaDSubVenta carrito;
//    float saldo;
//    int admin;         // 0 no es admin  // 1 es admin
//    int estadoCliente; // 0 baja // 1 alta
//    int idCliente;
//} usuario;

typedef struct
{
    char pais[50];
    char provincia[50];
    char ciudad[50];
    char direccion[50];
} destino;

typedef struct {
    subVenta dato;
    struct nodoListaDSubVenta* sig;
    struct nodoListaDSubVenta* ant;
}nodoListaDSubVenta;


typedef struct {
subVenta arreglo[50];
destino despachar;
float total;
int idVenta;
int idCliente;
int estadoEnvio; // 0 no despachado // 1 despachado
int estadoVenta; // 0 normal // 1 cancelada
} venta;

/// ESTRUCTURAS MENU USUARIO
typedef struct
{
    usuario dato;
    struct nodoProductoD *siguiente;
    struct nodoProductoD *anterior;
} nodoUsuarioD;


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
