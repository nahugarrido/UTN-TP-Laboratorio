#pragma once
/// ACA VAN LAS ESTRUCTURAS Y PROTOTIPADOS

/// ESTRUCTURAS
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
    producto dato;
    struct nodoProductoD* siguiente;
    struct nodoProductoD* anterior;
} nodoProductoD;


/// FUNCIONES
int menuUsuario(int id, int cursor);
void mostrarOpcionesUsuario(int cantidadOpciones,opciones arreglo[], int cursor);
void switchUsuario(int id, int opcion);
int mostrarProductos(int id, int cursor);
int contarOpcionesProductos(nodoProductoD* lista);
void mostrarOpcionesProductos(int cantidadOpciones,nodoProductoD* lista, int cursor);
