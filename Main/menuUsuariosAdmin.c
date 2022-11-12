#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define KEY_UP 72 +256
#define KEY_DOWN 80 +256
#define KEY_ENTER 13
#define KEY_ESC 27
#include "sistema.h"
#include "menuUsuariosAdmin.h"
#include "UserLibs.h"

/// ACA VAN TODOS LOS DEFINE, FUNCIONES Y SE DEBE CONECTAR A SU LIBRERIA.H (#include "ejemplo.h")

/// MENU ADMIN
int menuUsuariosAdmin(int id, int cursor) /// cursor es donde esta parado el >>>> , opcion es la tecla que introduce el usuario
{

    system("cls");

    opciones arreglo[] = {"Ver usuarios", "Ver informacion usuario id", "Crear usuario", "Modificar  datos usuario", "Modificar estado de un usuario", "Salir"};
    int cantidadOpciones = 6;

    dibujarCuadro(0,0,79,24); //SE DIBUJA EL CUADRO PRINCIPAL
    dibujarCuadro(1,1,78,3); //SE DIBUJA EL CUADRO DEL TITULO

    centrarTexto("E-COMMERCE - MENU USUARIOS",2);

    gotoxy(70,2);
    printf("ID: %i", id);

    /// MUESTRA LAS OPCIONES
    mostrarOpcionesUsuariosAdmin(cantidadOpciones,arreglo,cursor);

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


    return menuUsuariosAdmin(id, cursor);
}

/// MOSTRAR OPCIONES ADMIN
void mostrarOpcionesUsuariosAdmin(int cantidadOpciones,opciones arreglo[], int cursor)
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

void switchUsuariosAdmin(int id, int opcion)
{
    int mostrar = 1;
    int categoria = 0;

    switch(opcion)
    {
    case 1:
           showArchiveClientes();
        break;
    case 2:
            verInformacionUsuarioID();
        break;
    case 3:
            AltaUsuario();
        break;
    case 4:
            modificarClienteMenu();
        break;
    case 5:

        modificarEstadoClienteMenu();
        break;
    case 6:
        return 0;
        break;
    default:
        break;
    }
}
