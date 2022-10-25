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
    int idCliente;
    producto dato;
    int cantidad;
} subVenta;

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
    subVenta articulo;
    typedef struct nodoVenta *siguiente;
    typedef struct nodoVenta *anterior;

} nodoVenta;

nodoVenta *agregarAlFinalDobleVenta(nodoVenta *listaDobleAutos, nodoVenta *nuevoNodo);
nodoVenta *buscarUltimoDobleVenta(nodoVenta *listaVentas);
nodoVenta *crearNodoDobleVenta(producto A);
nodoVenta *inicListaDobleVenta();
nodoVenta *borrarNodoVenta(nodoVenta *listaVentas, int idPedido);
void showListVenta(nodoVenta *listaVentas);
