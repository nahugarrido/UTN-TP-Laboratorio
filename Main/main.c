#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "sistema.h"
#include "menuUsuario.h"
#include "menuAdmin.h"
#include "menuEnvios.h"
#include "menuProductos.h"
#include "menuUsuariosAdmin.h"
#include "productos.h"
#include "UserLibs.h"



int main()
{
    /// ESTILO DE MENU (GENERICO PARA TODOS LOS MENUS)
    desactivarMaximizar();
    system("mode con: cols=80 lines=25"); // SE DEFINE LAS DIMENSIONES DE LA VENTANA DEL PROGRAMA A 80 COLUMNAS Y 25 FILAS
    system("COLOR 0A");                   // SE DA UN COLOR DE FONDO Y COLOR A LAS LETRAS /// E0 // 5F // B0 // 0A
    //int id;

    do
    {
        int id = NULL;
        id = login(1);

        int opcion, opcion2;

        system("cls");
        printf("Ingresa 1 o 2: ");

        scanf("%i", &opcion2);

        if (opcion2 == 1)
        {
            do
            {
                opcion = menuUsuario(id,1);
                switchUsuario(id,opcion);
            }
            while( opcion != 0 && opcion != 7);
        }
        else if (opcion2 == 2)
        {
            do
            {
                opcion = menuAdmin(id,1);
                switchAdmin(id,opcion);
            }
            while( opcion != 0 && opcion != 6);
        }

    }
    while(1 == 1);

    /// TERMINAR EJECUCION
    system("cls");
    return 0;
}
