#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include "productos.h"
#define ArchProductos "Stock.Dat"

/// CARGAR UN PRODUCTO A LOS ARCHIVOS.
void AltaProducto()
{
    FILE *buffer = fopen(ArchProductos, "ab");
    producto Aux;
    if (buffer != NULL)
    {

        Aux = cargarProducto();
        fwrite(&Aux, sizeof(producto), 1, buffer);
        fclose(buffer);
    }
    else
    {
        printf("\nNo se pudo abrir el archivo.\n");
    }
}

/// FUNCION AUXILIAR DE CARGA.
producto cargarProducto()
{

    producto nuevo;
    printf("Ingrese el nombre del producto: \n");
    fflush(stdin);
    gets(nuevo.nombre);
    printf("Ingrese una categoria: \n");
    showCategorias();
    fflush(stdin);
    gets(nuevo.categoria);
    printf("Ingrese una descripcion: (280 caracteres) \n");
    fflush(stdin);
    gets(nuevo.descripcion);
    printf("Ingrese el precio venta: \n");
    fflush(stdin);
    scanf("%f", &nuevo.precioVenta);
    printf("Ingrese precio de compra: \n");
    fflush(stdin);
    scanf("%f", &nuevo.precioCosto);
    fflush(stdin);
    printf("Ingrese la cantidad de stock: \n");
    scanf("%i", &nuevo.cantidad);
    nuevo.flagStock = 0;

    return nuevo;
}

/// Para descontar stock. Necesita modificacion. De momento descuenta de a 1.
void descontarStock(char aDescontar[100], char categoria[])
{

    FILE *buffer = fopen(ArchProductos, "r+b");
    producto Aux;
    int flag = 0;
    if (buffer != NULL)
    {

        while (fread(&Aux, sizeof(producto), 1, buffer) > 0 && flag == 0)
        {
            if (strcmpi(Aux.categoria, categoria) == 0)
            {

                if (0 == strcmpi(Aux.nombre, aDescontar))
                {
                    fseek(buffer, sizeof(producto) * (-1), SEEK_CUR);
                    Aux.cantidad = (Aux.cantidad - 1);
                    mostrarProducto(Aux);
                    fwrite(&Aux, sizeof(producto), 1, buffer);
                    flag = 1;
                    fclose(buffer);
                }
            }
        }
    }
}

/// MOSTRAR EL ARCHIVO

void showArchive()
{
    FILE *buffer = fopen(ArchProductos, "rb");
    producto Aux;
    if (buffer != NULL)
    {
        while (fread(&Aux, sizeof(producto), 1, buffer) > 0)
        {

            mostrarProducto(Aux);
        }
        fclose(buffer);
    }
}

/// MOSTRAR CATEGORIAS (PARA ELEGIR DONDE ASISGNAR EL PRODUCTO)
void showCategorias()
{
    printf("\nIngrese 1.1 para Smartphones Samsung. \n");
    printf("\nIngrese 1.2 para Smartphones Apple. \n");
    printf("\nIngrese 1.3 para Smartphones. \n");
    printf("\nIngrese 2.1 para Tablets Samsung. \n");
    printf("\nIngrese 2.2 para Tablets Apple. \n");
    printf("\nIngrese 2.3 para Otros Tablets. \n");
    printf("\nIngrese 3.1 para Notebooks Samsung. \n");
    printf("\nIngrese 3.2 para Notebooks Apple. \n");
    printf("\nIngrese 3.3 para Otras Notebooks. \n");
}

/// MUESTRA 1 SOLO PRODUCTO.
void mostrarProducto(producto A)
{
    printf("---------------------------------------------");
    printf("\nProducto: %s \n", A.nombre);
    printf("\nDescripcion: %s \n", A.descripcion);
    printf("\nValor Final: $ %.2f \n", A.precioVenta);
    printf("\nCosto: $ %.2f \n", A.precioCosto);
    printf("\nCantidad de stock: %i \n", A.cantidad);
    printf("---------------------------------------------");
    if (A.flagStock == 0)
    {
        printf("\nStock Disponible \n");
    }
    else
    {
        printf("\n Sin stock disponible. \n");
    }
}
