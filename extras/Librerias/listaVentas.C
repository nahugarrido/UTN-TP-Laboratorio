#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include "listaCompras.h"

nodoVenta *inicListaDobleVenta()
{
    return NULL;
}

nodoVenta *crearNodoDobleVenta(venta A)
{

    nodoVenta *aux = sizeof(nodoVenta);

    aux->articulo = A;

    aux->siguiente = NULL;
    aux->anterior = NULL;

    return aux;
}

nodoVenta *buscarUltimoDobleVenta(nodoVenta *listaVentas)
{
    nodoVenta *ultimo;

    if (listaVentas == NULL)
    {

        ultimo = NULL;
    }
    else
    {
        if (listaVentas->siguiente == NULL)
        {
            ultimo = listaVentas;
        }
        else
        {
            ultimo = buscarUltimoDobleVenta(listaVentas->siguiente);
        }
    }

    return ultimo;
}

nodoVenta *agregarAlFinalDobleVenta(nodoVenta *listaVentas, nodoVenta *nuevoNodo)
{

    if (listaVentas == NULL)
    {
        listaVentas = nuevoNodo;
    }
    else
    {
        nodoVenta *ultimo = buscarUltimoDobleVenta(listaVentas);
        ultimo->siguiente = nuevoNodo;
        nuevoNodo->anterior = ultimo;
    }

    return listaVentas;
}

nodoVenta *borrarNodoVenta(nodoVenta *listaVentas, int idPedido)
{

    nodoVenta *seg;
    nodoVenta *ante;
    subVenta temporal;

    if ((listaVentas != NULL) && (listaVentas->articulo.id == idPedido))
    {

        nodoVenta *aux = listaVentas;
        temporal = aux->listaVentas = listaVentas->siguiente;
        free(aux);
    }
    else
    {
        seg = listaVentas;
    }
    while ((seg != NULL) && (seg->articulo.articulo != idPedido))
    {

        ante = seg;
        seg = seg->siguiente;
    }
    if (seg != NULL)
    {
        ante->siguiente = seg->siguiente;
        temporal = seg->articulo;
        free(seg);
    }

    return listaVentas;
}

void showListVenta(nodoVenta *listaVentas)
{
    nodoVenta *seg = listaVentas;

    if (seg != NULL)
    {
        while (seg != NULL)
        {
            printf("\n-----------------------------------\n");
            printf("\nID DEL CLIENTE: %s \n", seg->articulo.idCliente);
            printf("\nProducto: %s \n", seg->articulo.dato);
            printf("\nCantidad: %i \n", seg->articulo.cantidad);
            printf("\n-----------------------------------\n");
            seg = seg->siguiente;
        }
    }
}
