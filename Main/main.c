#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "sistema.h"
#include "menuUsuario.h"
#include "menuAdmin.h"

int main()
{
    //// PROBANDO GIT !! ////
    /// ESTILO DE MENU (GENERICO PARA TODOS LOS MENUS)
    desactivarMaximizar();
    system("mode con: cols=80 lines=25"); // SE DEFINE LAS DIMENSIONES DE LA VENTANA DEL PROGRAMA A 80 COLUMNAS Y 25 FILAS
    system("COLOR 0A");                   // SE DA UN COLOR DE FONDO Y COLOR A LAS LETRAS /// E0 // 5F // B0 // 0A

    int id = login(1);

    int opcion, opcion2;

    system("cls");
    printf("Ingresa 1 o 2: ");
<<<<<<< HEAD
    scanf("%i", &opcion2);
=======
    a
        scanf("%i", &opcion2);
>>>>>>> 8bd3aeacff0be89a0cb6bdcd2bc60bc8bf46e534

    if (opcion2 == 1)
    {
<<<<<<< HEAD
        do
        {
        opcion = menuUsuario(id,1);
        switchUsuario(id,opcion);
        } while( 1 == 1); /// bucle infinito de momento
=======
        opcion = menuUsuario(1, 1);
>>>>>>> 8bd3aeacff0be89a0cb6bdcd2bc60bc8bf46e534
    }
    else if (opcion2 == 2)
    {
<<<<<<< HEAD
        opcion = menuAdmin(id,1);
=======
        opcion = menuAdmin(1, 1);
>>>>>>> 8bd3aeacff0be89a0cb6bdcd2bc60bc8bf46e534
    }

    /// TERMINAR EJECUCION
    system("cls");
    return 0;
}
<<<<<<< HEAD


///// TESTEANDO
//int mostrarProductos(int id, int cursor) /// cursor es donde esta parado el >>>> , opcion es la tecla que introduce el usuario
//{
//
//    system("cls");
//
//    nodoProductoD* lista;
//    lista = NULL;
//
//
//
//    dibujarCuadro(0,0,79,24); //SE DIBUJA EL CUADRO PRINCIPAL
//    dibujarCuadro(1,1,78,3); //SE DIBUJA EL CUADRO DEL TITULO
//
//    centrarTexto("E-COMMERCE - MENU DEL ADMINISTRADOR",2);
//
//    gotoxy(70,2);
//    printf("ID: %i", id);
//
//
//
//
//    / MUESTRA LAS OPCIONES
//    int cantidadOpciones = contarOpcionesProductos(lista);
//    mostrarOpcionesProductos(cantidadOpciones,lista,cursor);
//
//    gotoxy(7,21);
//    printf("Para salir presionar ESC");
//    dibujarCuadro(1,19,78,23); //SE DIBUJA EL CUADRO MENSAJE DE CONSOLA
//    ocultarCursor();
//
//    int opcion = capturarTecla();
//
//    / SONIDO
//    if(opcion == KEY_ENTER)
//    {
//        Beep(400,80);
//    }
//    else if(opcion == KEY_ESC)
//    {
//        Beep(800,80);
//    }
//    else
//    {
//        Beep(600,80);
//    }
//
//
//    if(opcion == KEY_ESC)
//    {
//        return 0;
//    }
//
//    if(opcion == KEY_ENTER)
//    {
//        return cursor;
//    }
//
//
//    if(opcion == KEY_UP)
//    {
//        if(cursor-1 > 0)
//        {
//            cursor -= 1;
//        }
//    }
//
//    if(opcion == KEY_DOWN)
//    {
//        if(cursor+1 <= cantidadOpciones)
//        {
//            cursor += 1;
//        }
//    }
//
//    if(opcion == KEY_LEFT)
//    {
//        if(cursor-7 > 0)
//        {
//            cursor -= 7;
//        }
//    }
//
//    if(opcion == KEY_RIGHT)
//    {
//        if(cursor+7 <= cantidadOpciones)
//        {
//            cursor += 1;
//        }
//    }
//
//    return mostrarProductos(id, cursor);
//}
=======
>>>>>>> 8bd3aeacff0be89a0cb6bdcd2bc60bc8bf46e534
