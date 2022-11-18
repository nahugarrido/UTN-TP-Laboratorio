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
#include "loginAlgoritmo.h"

int main()
{
    /// ESTILO DE MENU (GENERICO PARA TODOS LOS MENUS)
    desactivarMaximizar();
    system("mode con: cols=80 lines=25"); // SE DEFINE LAS DIMENSIONES DE LA VENTANA DEL PROGRAMA A 80 COLUMNAS Y 25 FILAS
    system("COLOR 0B");                   // SE DA UN COLOR DE FONDO Y COLOR A LAS LETRAS // 0B // 0A
    do
    {
        int id = 0;
        id = login(1);

        /// TESTEAR SIN PASAR POR EL LOGIN
        //id = 3;

        int opcion;

        nodoArbolUsuario* arbol;

        arbol = inicArbol();
        arbol = leerArchivo(arbol);

        int flagAdmin = buscarPorIdUsuario(arbol, id);

        /// TESTEAR ADMIN /// CON ESTO SE PUEDE ACCEDER AL MENU DE ADMIN SIN PASAR POR EL LOGIN 1 ES ADMIN
        //flagAdmin = 1;

        if (flagAdmin == 0)
        {
            do
            {
                opcion = menuUsuario(id, 1);
                switchUsuario(id, opcion);
            } while (opcion != 0 && opcion != 7);
        }
        else if (flagAdmin == 1)
        {
            do
            {
                opcion = menuAdmin(id, 1);
                switchAdmin(id, opcion);
            } while (opcion != 0 && opcion != 6);
        }

    } while (1 == 1);

    /// TERMINAR EJECUCION
    system("cls");
    return 0;
}
