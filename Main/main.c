#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "sistema.h"

int main()
{

    /// ESTILO DE MENU (GENERICO PARA TODOS LOS MENUS)
    desactivarMaximizar();
    system("mode con: cols=80 lines=25"); // SE DEFINE LAS DIMENSIONES DE LA VENTANA DEL PROGRAMA A 80 COLUMNAS Y 25 FILAS
    system("COLOR 0A");                   // SE DA UN COLOR DE FONDO Y COLOR A LAS LETRAS /// E0 // 5F // B0 // 0A

    int id = login(1);

    int opcion, opcion2;

    system("cls");
    printf("Ingresa 1 o 2: ");a
    scanf("%i", &opcion2);

    if(opcion2 == 1)
    {
        opcion = menuUsuario(1,1);
    }
    else if(opcion2 == 2)
    {
        opcion = menuAdmin(1,1);
    }

    /// PAUSAR EJECUCION
    printf("\n");
    gotoxy(40, 40);
    system("cls");

    return 0;
}

