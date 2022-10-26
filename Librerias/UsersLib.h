#pragma once

typedef struct
{
    char userName[30];
    char password[30];
    int saldo;
    int admin;
    int idCliente;
    int estadoCliente;
    /// venta compras[100];

} usuario;

typedef struct
{
    char nombre[30];
    char descripcion[100];
    int cantidad;
    int flagStock; // 0 en stock // 1 fuera de stock
} producto;

typedef struct
{
    int idCliente;
    int producto;
    int cantidad;
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
    int id;
    int flagEstado; // 0 baja  // 1 alta
} venta;

///// FUNCIONES /////
void AltaUsuario();
int verificarPorUserName(char User[]);
usuario pedirDatos();
int contadorRegistros();
void mostrarCliente(usuario Aux);
void showArchive();
void AltaAdmin();
void mostrarAdmin();