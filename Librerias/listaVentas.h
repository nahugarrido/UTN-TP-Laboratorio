#pragma once

typedef struct
{
    char pais[50];
    char provincia[50];
    char ciudad[50];
    char direccion[50];
} destino;

typedef struct
{
    char nombre[30];
    char descripcion[280];
    float precioVenta;
    float precioCosto;
    int cantidad;
    int flagStock; // 0 en stock // 1 fuera de stock
} producto;

typedef struct
{
    int idCliente;
    producto dato;
    int cantidad;
} subVenta;

typedef struct
{
    subVenta articulo;
<<<<<<< HEAD
    struct nodoVenta *siguiente;
    struct nodoVenta *anterior;
=======
     struct nodoVenta *siguiente;
     struct nodoVenta *anterior;
>>>>>>> d7249cd0e8f0c82f82dcf9a3ff020e468a4068e2

} nodoVenta;

nodoVenta *agregarAlFinalDobleVenta(nodoVenta *listaDobleAutos, nodoVenta *nuevoNodo);
nodoVenta *buscarUltimoDobleVenta(nodoVenta *listaVentas);
nodoVenta *crearNodoDobleVenta(producto A);
nodoVenta *inicListaDobleVenta();
nodoVenta *borrarNodoVenta(nodoVenta *listaVentas, int idPedido);
void showListVenta(nodoVenta *listaVentas);
