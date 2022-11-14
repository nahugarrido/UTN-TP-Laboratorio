#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define KEY_UP 72 +256
#define KEY_DOWN 80 +256
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_LEFT 75 +256
#define KEY_RIGHT 77 +256
#include "estructuras.h"
#include "sistema.h"
#include "productos.h"
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
    int mostrar = 1;
    int categoria = 0;

    switch(opcion)
    {
    case 1:
        /// CARRITO DE COMPRAS
        // muestra el carrito de compras si se quiere confirmar la compra se presiona SHIFT, si se quiere salir se presiona ESC,
        // si se quiere remover una subVenta se presiona enter, preguntara si esta seguro de querer eliminarlo.
        break;
    case 2:
        /// VER PRODUCTOS

        // categoria = mostrarCategoriasProductos()
        // tendriamos que pasar categoria por parametro en mostrar productos
        do
        {
        mostrar = mostrarProductos(id,1);
        if(mostrar != 0)
        {
             mostrarUnProductoUsuario(id, mostrar);
            /// (mostrar producto pregunta si quiere añadirlo al carrito, de no querer vuelve al menu de productos ed querer pregunta cantidad y se agrega.
            /// funcion de mostrar el producto y añadir a carrito
        }
        } while(mostrar != 0);
        break;
    case 3:
        /// MIS DATOS DE ENVIO
        // esta funcion printea los datos de envio del usuario en la consola que aparece debajo en el menu usuario
        mostrarDatosEnvio(id);
        break;
    case 4:
        /// SALDO DISPONIBLE
        // esta funcion printea el saldo del usuario en la consola que aparece debajo en el menu usuario
        saldoDisponible(id);
        break;
    case 5:
        do
        {
        mostrar = historialComprasId(id,1);
        if(mostrar != 0)
        {
             break;
            /// (mostrar producto pregunta si quiere añadirlo al carrito, de no querer vuelve al menu de productos ed querer pregunta cantidad y se agrega.
            /// funcion de mostrar el producto y añadir a carrito
        }
        } while(mostrar != 0);
        break;
    case 6:
        break;
    case 7:
        return 0;
        break;
    default:
        break;
    }
}


