#pragma once
/// ESTRUCTURA ///
typedef struct

{
    char nombre[30];
    char nombreCategoria[30];
    char descripcion[100];
    float precioVenta;
    float precioCosto;
    int nroCategoria;
    int cantidad;
    int flagStock; // 0 en stock // 1 fuera de stock
} producto;

typedef struct
{
    producto dato;
    struct nodoProductoD *siguiente;
    struct nodoProductoD *anterior;
} nodoProductoD;

typedef struct
{
    int nroCategoria;
    char nombreCategoria[25];
} categoria;

typedef struct
{
    categoria Categoria;
    nodoProductoD *lista;
    struct nodoCategoria *siguiente;
    struct nodoCategoria *anterior;

} nodoCategoria;

/// PROTOTIPADOS
void AltaProducto();
producto cargarProducto();
void mostrarProducto(producto A);
void showArchive();
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
int mostrarProductos(int id, int cursor, int nroCategoria);
void mostrarOpcionesProductos(nodoProductoD *lista, int cursor);
void mostrarUnProductoUsuario(int idUsuario, int id, int nroCategoria);
void printDescripcionProducto(producto mostrar);
void printCategoriaProducto(producto mostrar);
/// MOSTRAR STOCK
int mostrarStock(int id, int cursor, int nroCategoria);
void mostrarOpcionesStock(nodoProductoD *lista, int cursor);
/// TDA ESTRUCTURAS COMPUESTAS CATEGORIAS
nodoCategoria *inicCategoria();
nodoCategoria *inicCategoria();
nodoCategoria *agregarAlPrincipioCategoria(nodoCategoria *lista, nodoCategoria *nuevo);
nodoCategoria *alta(nodoCategoria *listaCategorias, nodoProductoD *nuevo, int nroCategoria);
nodoCategoria *buscarCategoria(nodoCategoria *lista, int nroCategoria);
categoria crearCategoria(nodoProductoD *nuevo);
/// MOSTRAR CATEGORIAS
nodoCategoria *cargarListaDeListas(nodoCategoria *lista);
