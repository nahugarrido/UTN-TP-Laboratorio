#pragma once
/// ESTRUCTURA ///
typedef struct
{
    char nombre[30];
    char descripcion[280];
    char categoria[3];
    float precioVenta;
    float precioCosto;
    int cantidad;
    int flagStock; // 0 en stock // 1 fuera de stock
} producto;

/// PROTOTIPADOS

void AltaProducto();
producto cargarProducto();
void mostrarProducto(producto A);
void showArchive();
void descontarStock(char aDescontar[100], char categoria[3]);
void showCategorias();
