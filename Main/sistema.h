#pragma once
/// ESTRUCTURAS
typedef struct
{
    char nombre[50];
} opciones; // OPCIONES DEL MENU

void dibujarCuadro(int x1, int y1, int x2, int y2);
void gotoxy(int x, int y);
void desactivarMaximizar();
void ocultarCursor();
int capturarTecla();
void dibujarCuadro(int x1, int y1, int x2, int y2);
void centrarTexto(char *texto, int y);
void animacionCarga();
void animacionPassword(char *password[]);
int login(int cursor);
int seleccionarSiNo(cursor); /// 1 ES SI 2 ES NO
void mostrarSiNo(cursor);
int capturarTeclaSiNo();

/// COLORES
void black();
void red();
void green();
void yellow();
void blue();
void purple();
void cyan();
void white();
void reset();

