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

/// DESACTIVAR MAXIMIZAR
void desactivarMaximizar()
{
    HWND consoleWindow;
    consoleWindow = GetConsoleWindow();
    SetWindowLong(consoleWindow, GWL_STYLE,GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

/// CENTRAR TEXTO
void centrarTexto(char *texto, int y)
{
    int longitud = strlen(texto); // mitad de ancho de pantalla - longitud de texto / 2
    gotoxy(40-(longitud/2),y);
    printf(texto);
}

/// CAPTURAR INFORMACION TECLA PRESIONADA
int capturarTecla()
{
    int tecla;
    int opcion;

    do
    {
        tecla = getch();
        if(tecla == 0 || tecla == 224)
        {
            tecla = 256 + getch();
        }

    }
    while((tecla != KEY_UP) && (tecla != KEY_DOWN) && (tecla != KEY_ESC) && (tecla != KEY_ENTER));


    switch(tecla)
    {
    case KEY_UP:
        opcion = KEY_UP;
        break;
    case KEY_DOWN:
        opcion = KEY_DOWN;
        break;
    case KEY_ENTER:
        opcion = KEY_ENTER;
        break;
    case KEY_ESC:
        opcion = KEY_ESC;
        break;
    default:
        printf("\nDEFAULT!");
        system("pause");
        break;
    }

    return opcion;
}

void ocultarCursor()
{
    printf("\e[?25l");
}

///FUNCION GOTOXY
void gotoxy(int x,int y)
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y= y;
    SetConsoleCursorPosition(hcon,dwPos);
}


///FUNCION QUE DIBUJA EL CUADRO
void dibujarCuadro(int x1,int y1,int x2,int y2)
{
    int i;

    for (i=x1; i<x2; i++)
    {
        gotoxy(i,y1);
        printf("\304"); //linea horizontal superior
        gotoxy(i,y2);
        printf("\304"); //linea horizontal inferior
    }

    for (i=y1; i<y2; i++)
    {
        gotoxy(x1,i);
        printf("\263"); //linea vertical izquierda
        gotoxy(x2,i);
        printf("\263"); //linea vertical derecha
    }

    gotoxy(x1,y1);
    printf("\332");
    gotoxy(x1,y2);
    printf("\300");
    gotoxy(x2,y1);
    printf("\277");
    gotoxy(x2,y2);
    printf("\331");
}

/// COLORES
void black()
{
    printf("\033[1;30m");
}

void red()
{
    printf("\033[1;31m");
}

void green()
{
    printf("\033[1;32m");
}
void yellow()
{
    printf("\033[1;33m");
}

void blue()
{
    printf("\033[1;34m");
}

void purple()
{
    printf("\033[1;35m");
}

void cyan()
{
    printf("\033[1;36m");
}

void white()
{
    printf("\033[1;37m");
}

void reset()
{
    printf("\033[0m");
}

void limpiarConsola()
{
    gotoxy(2,20);
    printf("                                                                      ");
    gotoxy(2,21);
    printf("                                                                      ");
    gotoxy(2,22);
    printf("                                                                      ");

}

int seleccionarSiNo(int cursor) /// 1 ES SI 2 ES NO
{
    mostrarSiNo(cursor);

    int opcion = capturarTeclaSiNo();

    if(opcion == KEY_ESC)
    {
        return 0;
    }

    if(opcion == KEY_ENTER)
    {
        return cursor;
    }

    if(opcion == KEY_LEFT)
    {
        if(cursor-1 > 0)
        {
            cursor -= 1;
        }
    }

    if(opcion == KEY_RIGHT)
    {
        if(cursor+1 <= 2)
        {
            cursor += 1;
        }
    }

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

    return seleccionarSiNo(cursor);
}

void mostrarSiNo(int cursor)
{
    gotoxy(7,22);
    if(cursor == 1)
    {
        printf(">>>   ");
    }
    else
    {
        printf("      ");
    }

    printf("Si");
    printf("        ");

    if(cursor == 2)
    {
        printf(">>>   ");
    }
    else
    {
        printf("      ");
    }

    printf("No");
}

int capturarTeclaSiNo()
{
    int tecla;
    int opcion;

    do
    {
        tecla = getch();
        if(tecla == 0 || tecla == 224)
        {
            tecla = 256 + getch();
        }

    }
    while((tecla != KEY_LEFT) && (tecla != KEY_RIGHT) && (tecla != KEY_ESC) && (tecla != KEY_ENTER));


    switch(tecla)
    {
    case KEY_LEFT:
        opcion = KEY_LEFT;
        break;
    case KEY_RIGHT:
        opcion = KEY_RIGHT;
        break;
    case KEY_ENTER:
        opcion = KEY_ENTER;
        break;
    case KEY_ESC:
        opcion = KEY_ESC;
        break;
    default:
        printf("\nDEFAULT!");
        system("pause");
        break;
    }

    return opcion;
}
