#pragma once
/// ESTRUCTURA ///
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
    int idCategoria;
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
    nodoProductoD* lista;
    struct nodoCategorias *siguiente;
    struct nodoCategorias *anterior;

} nodoCategorias;

/// PROTOTIPADOS
void AltaProducto();
producto cargarProducto();
void mostrarProducto(producto A);
void showArchive();
void descontarStock(char aDescontar[100], char categoria[3], int cantidad);
void showCategorias();
/// PROTOTIPADOS LISTAS
nodoProductoD *agregarAlFinalDobleProducto(nodoProductoD *lista, nodoProductoD *nuevoNodo);
nodoProductoD *buscarUltimoDobleProducto(nodoProductoD *lista);
nodoProductoD *crearNodoDobleProducto(producto A);
nodoProductoD *inicListaDobleProducto();
nodoProductoD *borrarnodoProductoD(nodoProductoD *lista, int idPedido);
void showListproducto(nodoProductoD *lista);
nodoProductoD *despersistirListaDobleProductos(nodoProductoD *lista);
void mostrarProductoCorto(producto nombre);
int mostrarProductos(int id, int cursor);
void mostrarOpcionesProductos(nodoProductoD *lista, int cursor);
void mostrarUnProductoUsuario(int idUsuario, int id);
void printDescripcionProducto(producto mostrar);
void printCategoriaProducto(producto mostrar);
/// MOSTRAR STOCK
int mostrarStock(int id, int cursor);
void mostrarOpcionesStock(nodoProductoD *lista, int cursor);
