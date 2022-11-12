#pragma once
/// ACA VAN LAS ESTRUCTURAS Y PROTOTIPADOS

/// ESTRUCTURAS
typedef struct
{
    char nombre[30];
    char descripcion[100];
    char categoria[3];
    float precioVenta;
    float precioCosto;
    int cantidad;
    int flagStock; // 0 en stock // 1 fuera de stock
} producto;

typedef struct{

    producto dato;
    struct nodoProductoD * anterior;
    struct nodoProductoD * siguiente;

}nodoProductoD;
typedef struct
{
    producto dato;
    int cantidad;
    float subtotal;
} subVenta;

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

typedef struct
{
    char pais[50];
    char provincia[50];
    char ciudad[50];
    char direccion[50];
} destino;


//typedef struct
//{
//    subVenta arreglo[50];
//    destino despachar;
//    int id;
//    int flagEstado; // 0 baja  // 1 alta
//} venta;

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
