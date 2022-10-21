#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define KEY_UP 72 +256
#define KEY_DOWN 80 +256
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_LEFT 75 +256
#define KEY_RIGHT 77 +256
#include "sistema.h"
#include "menuUsuario.h"

/// ACA VAN TODOS LOS DEFINE, FUNCIONES Y SE DEBE CONECTAR A SU LIBRERIA.H (#include "ejemplo.h")

/// MENU USUARIO ///
int menuUsuario(int id, int cursor) /// cursor es donde esta parado el >>>> , opcion es la tecla que introduce el usuario
{

    system("cls");

    opciones arreglo[] = {"Carrito de compras", "Ver productos", "Mis datos de envio", "Saldo disponible", "Historial de compras", "Cancelar compra", "Salir"};
    int cantidadOpciones = 7;

    dibujarCuadro(0,0,79,24); //SE DIBUJA EL CUADRO PRINCIPAL
    dibujarCuadro(1,1,78,3); //SE DIBUJA EL CUADRO DEL TITULO

    centrarTexto("E-COMMERCE - MENU DEL USUARIO",2);

    gotoxy(70,2);
    printf("ID: %i", id);

    /// MUESTRA LAS OPCIONES
    mostrarOpcionesUsuario(cantidadOpciones,arreglo,cursor);

    dibujarCuadro(1,19,78,23); //SE DIBUJA EL CUADRO MENSAJE DE CONSOLA
    gotoxy(9,21);
    printf("Mensaje de consola ...");
    ocultarCursor();

    int opcion = capturarTecla();

    /// SONIDO
    if(opcion == KEY_ENTER)
    {
        Beep(400,80);
    }
    else if(opcion == KEY_ESC)
    {
        Beep(800,80);
    }
    else
    {
        Beep(600,80);
    }


    if(opcion == KEY_ESC)
    {
        return 0;
    }

    if(opcion == KEY_ENTER)
    {
        return cursor;
    }


    if(opcion == KEY_UP)
    {
        if(cursor-1 > 0)
        {
            cursor -= 1;
        }
    }

    if(opcion == KEY_DOWN)
    {
        if(cursor+1 <= cantidadOpciones)
        {
            cursor += 1;
        }
    }


    return menuUsuario(id, cursor);
}

/// MOSTRAR OPCIONES USUARIO
void mostrarOpcionesUsuario(int cantidadOpciones,opciones arreglo[], int cursor)
{
    int contador;

    for(int i = 0; i < cantidadOpciones; i++)
    {
        contador = 5 + i*2;

        gotoxy(2,contador);

        if(i+1 == cursor)
        {
            printf(" >>>> ");
        }
        else
        {
            printf("       ");
        }

        printf("%s\n", arreglo[i]);
    }
}

void switchUsuario(int id, int opcion)
{
    switch(opcion)
    {
    case 1:
        break;
    case 2:
        mostrarProductos(id,1);
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        break;
    default:
        break;
    }
}

int mostrarProductos(int id, int cursor) /// cursor es donde esta parado el >>>> , opcion es la tecla que introduce el usuario
{

    system("cls");

    nodoProductoD* lista;
    lista = NULL;



    dibujarCuadro(0,0,79,24); //SE DIBUJA EL CUADRO PRINCIPAL
    dibujarCuadro(1,1,78,3); //SE DIBUJA EL CUADRO DEL TITULO

    centrarTexto("E-COMMERCE - MENU DEL ADMINISTRADOR",2);

    gotoxy(70,2);
    printf("ID: %i", id);




    /// MUESTRA LAS OPCIONES
    int cantidadOpciones = contarOpcionesProductos(lista);
    mostrarOpcionesProductos(cantidadOpciones,lista,cursor);

    gotoxy(7,21);
    printf("Para salir presionar ESC");
    dibujarCuadro(1,19,78,23); //SE DIBUJA EL CUADRO MENSAJE DE CONSOLA
    ocultarCursor();

    int opcion = capturarTecla();

    /// SONIDO
    if(opcion == KEY_ENTER)
    {
        Beep(400,80);
    }
    else if(opcion == KEY_ESC)
    {
        Beep(800,80);
    }
    else
    {
        Beep(600,80);
    }


    if(opcion == KEY_ESC)
    {
        return 0;
    }

    if(opcion == KEY_ENTER)
    {
        return cursor;
    }


    if(opcion == KEY_UP)
    {
        if(cursor-1 > 0)
        {
            cursor -= 1;
        }
    }

    if(opcion == KEY_DOWN)
    {
        if(cursor+1 <= cantidadOpciones)
        {
            cursor += 1;
        }
    }

    if(opcion == KEY_LEFT)
    {
        if(cursor-7 > 0)
        {
            cursor -= 7;
        }
    }

    if(opcion == KEY_RIGHT)
    {
        if(cursor+7 <= cantidadOpciones)
        {
            cursor += 1;
        }
    }

    return mostrarProductos(id, cursor);
}

int contarOpcionesProductos(nodoProductoD* lista)
{
    int contador = 0;

    while(lista != NULL)
    {
        contador++;
        lista = lista->siguiente;
    }

    return contador;
}

/// MOSTRAR OPCIONES
void mostrarOpcionesProductos(int cantidadOpciones,nodoProductoD* lista, int cursor)
{
    nodoProductoD* anterior;
    int posicionY;
    int i = 0;
    int posicionX;

    /// esto ya deberia funcionar para navegar en el menu en todas las direcciones de no funcionar
    /// hay que revisar en mostrar productos los if a ver si deberiamos poner +1 -1 en condiciones = <=

    while((lista != NULL) && (i < cantidadOpciones))
    {

        posicionY = 5 + i*2;

        if(i+1 == 7)
        {
            posicionY -= 12;
        }

        if(i < 7)
        {
            posicionX = 2;

        }
        if (i+1 == 7)
        {
            posicionX = 20;
        }

        gotoxy(posicionX,posicionY);

        if(i+1 == cursor)
        {
            printf(" >>>> ");
        }
        else
        {
            printf("       ");
        }

        printf("%s", lista->dato.nombre);
        printf(" $%s\n", lista->dato.precioVenta);



        i++;
        anterior = lista;
        lista = lista->siguiente;
    }
}
