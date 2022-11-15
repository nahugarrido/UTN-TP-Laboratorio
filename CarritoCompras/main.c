#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#define KEY_UP 72 +256
#define KEY_DOWN 80 +256
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_LEFT 75 +256
#define KEY_RIGHT 77 +256
#define KEY_S 83
#define KEY_s 115

typedef struct
{
    char nombre[30];
    char descripcion[280];
    char categoria[3];
    float precioVenta;
    float precioCosto;
    int cantidad;
    int flagStock; // 0 en stock // 1 fuera de stock
} producto;

typedef struct
{
    producto dato;
    int cantidad;
    float subtotal;
} subVenta;

typedef struct
{
    subVenta dato;
    struct nodoListaDSubVenta* siguiente;
    struct nodoListaDSubVenta* anterior;
} nodoListaDSubVenta;

/// ESTRUCTURAS
typedef struct
{
    char nombre[50];
} opciones; // OPCIONES DEL MENU

/// PROTOTIPOS DE LAS FUNCIONES
void dibujarCuadro(int x1,int y1,int x2,int y2);
void gotoxy(int x,int y);
void desactivarMaximizar();
int mostrarsubVentas(int id, int cursor);
int capturarTecla2();
void ocultarCursor();
int contarOpcionessubVentas(nodoListaDSubVenta* lista);
void suma();

/// PROTOTIPADO DE LISTAS
nodoListaDSubVenta *agregarAlFinalDSubVenta(nodoListaDSubVenta *lista, nodoListaDSubVenta *nuevoNodo);
nodoListaDSubVenta *buscarUltimoDSubVenta(nodoListaDSubVenta *lista);
nodoListaDSubVenta *crearNodoDoblesubVenta(subVenta A);
nodoListaDSubVenta *inicListaDoblesubVenta();
nodoListaDSubVenta *borrarnodoListaDSubVenta(nodoListaDSubVenta *lista, int idPedido);
void showListsubVenta(nodoListaDSubVenta *lista);
nodoListaDSubVenta* obtenerListaDSubVentas(nodoListaDSubVenta* lista);
void mostrarsubVentaCorto(subVenta nombre);
int mostrarsubVentas(int id, int cursor);
void mostrarOpcionesCarrito(nodoListaDSubVenta* lista, int cursor);

//FUNCION PRINCIPAL MAIN
int main()
{

    /// ESTILO DE MENU (GENERICO PARA TODOS LOS MENUS)
    desactivarMaximizar();
    system("mode con: cols=80 lines=25"); //SE DEFINE LAS DIMENSIONES DE LA subVentaNA DEL PROGRAMA A 80 COLUMNAS Y 25 FILAS
    system("COLOR 0A"); //SE DA UN COLOR DE FONDO Y COLOR A LAS LETRAS /// E0 // 5F // B0
    int id = 1;

    int opcion = mostrarsubVentas(1,1);

//    system("cls");
//    printf("opcion = %i", opcion);
//    system("pause");

    /// PAUSAR EJECUCION
    printf("\n");
    gotoxy(40,40);
    system("cls");
    return 0;
}


/// PASAR A LIBRERIA
int mostrarsubVentas(int id, int cursor) /// cursor es donde esta parado el >>>> , opcion es la tecla que introduce el usuario
{

    system("cls");
    nodoListaDSubVenta *lista = inicListaDoblesubVenta();
    lista = obtenerListaDSubVentas(lista);

    dibujarCuadro(0,0,79,24); //SE DIBUJA EL CUADRO PRINCIPAL
    dibujarCuadro(1,1,78,3); //SE DIBUJA EL CUADRO DEL TITULO

    centrarTexto("E-COMMERCE - CARRITO DE COMPRAS",2);

    gotoxy(70,2);
    printf("ID: %i", id);

    /// TABLA HEADERS DE E-COMMERCE CARRITO
    gotoxy(9,4);
    printf("PRODUCTO");
    gotoxy(33,4);
    printf("PRECIO");
    gotoxy(50,4);
    printf("CANTIDAD");
    gotoxy(68,4);
    printf("SUBTOTAL");



    gotoxy(62,20);
    printf("TOTAL A PAGAR: ");


    /// MUESTRA LAS OPCIONES
    int cantidadOpciones = contarOpcionessubVentas(lista);
    //printf("\ncantidadOpciones: %i", cantidadOpciones);
    //system("pause");

    mostrarOpcionesCarrito(lista,cursor);

    gotoxy(65,21);
    /// ACA SE DEBERIA PRINTEAR LA SUMA TOTAL DEL CARRITO
    printf("$9999,99");

    gotoxy(7,21);
    printf("Para confirmar la compra presionar 'S'"); /// 115 codigo ascii s minuscula // 83 mayuscula
    dibujarCuadro(1,19,78,23); //SE DIBUJA EL CUADRO MENSAJE DE CONSOLA
    ocultarCursor();

    int opcion = capturarTecla2();

    gotoxy(0,0);
    printf("cursor: %i", cursor); //// PARA VER EL CURSOR  --------------------------------------------------------------------------->
    //system("pause");

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
        /// TERMINA LA EJECUCION
        return 0;
    }

    if(opcion == KEY_ENTER)
    {
        /// ACA RETORNA EL CURSOR EN LA POSICION A EDITAR DE LA SUBVENTA EN LA LISTA
        return cursor;
    }

    if((opcion == KEY_S) || (opcion == KEY_s))
    {
        /// ACA VA FUNCION DE COMPRAR
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
        if(cursor-6 > 0)
        {
            cursor -= 6;
        }
    }

    if(opcion == KEY_RIGHT)
    {
        if(cursor+6 <= cantidadOpciones)
        {
            cursor += 6;
        }
    }

    return mostrarsubVentas(id, cursor);
}

void centrarTexto(char *texto, int y)
{
    int longitud = strlen(texto); // mitad de ancho de pantalla - longitud de texto / 2
    gotoxy(40-(longitud/2),y);
    printf(texto);
}

int contarOpcionessubVentas(nodoListaDSubVenta* lista)
{
    int contador = 0;

    if(lista == NULL)
    {
        printf("lista vacia");
    }

    while(lista != NULL)
    {
        contador++;
        lista = lista->siguiente;
    }

    return contador;
}

/// MOSTRAR OPCIONES
void mostrarOpcionesCarrito(nodoListaDSubVenta* lista, int cursor)
{
    nodoListaDSubVenta* anterior;
    int posicionY;
    int posicionX;
    int contPaginas = ceil(((float)cursor/6));

    int i=  1 + ((contPaginas-1)*6);

    int cantidadxColumna = 6;

    int cantColumnas = 0;

    /// esto ya deberia funcionar para navegar en el menu en todas las direcciones de no funcionar
    /// hay que revisar en mostrar subVentas los if a ver si deberiamos poner +1 -1 en condiciones = <=

    int tope = i + 5;

    for(int i = 0; i < ((contPaginas-1)*6); i++)
    {
        lista = lista->siguiente;
    }

    while((lista != NULL)  && (i <= tope))
    {
        posicionY = 14 + 3 + i*2;

        if((i-1) % 6 == 0 && i != 0)
        {
            cantColumnas++;
        }

        posicionX = 2;

        if((cantColumnas % 2 != 0) )
        {
            posicionY -= (contPaginas * 12);
        }

        gotoxy(posicionX,posicionY);

        if(i == cursor)
        {
            printf(" >>>> ");
        }
        else
        {
            printf("       ");
        }
        /// LA FUNCION QUE CREA LA LISTA NO ESTA IMPLEMENTADA
        /// SI NO LLEGA AFUNCIONAR PUEDE QUE HAYA UN PROBLEMA EN ESTE PRINTF
        /// NO TE PREOCUPES SI APARECEN TORCIDOS, LO SOLUCIONO DESPUES
        printf("%s   %f   %i   %f", lista->dato.dato.nombre,lista->dato.dato.precioVenta,lista->dato.cantidad, lista->dato.subtotal);

//        gotoxy(0,0);
//        //printf("cantColumnas: %i i = %i",cantColumnas, i);
//        printf("posicionY: %i",posicion);
//        system("pause");

        i++;
        anterior = lista;
        lista = lista->siguiente;
    }
}

int capturarTecla2()
/// CAPTURAR INFORMACION TECLA PRESIONADA
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
    while((tecla != KEY_UP) && (tecla != KEY_DOWN) && (tecla != KEY_ESC) && (tecla != KEY_ENTER) && (tecla != KEY_LEFT) && (tecla != KEY_RIGHT));


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
    case KEY_LEFT:
        opcion = KEY_LEFT;
        break;
    case KEY_RIGHT:
        opcion = KEY_RIGHT;
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

/// DESACTIVAR MAXIMIZAR
void desactivarMaximizar()
{
    HWND consoleWindow;
    consoleWindow = GetConsoleWindow();
    SetWindowLong(consoleWindow, GWL_STYLE,GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
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


/// FUNCIONES LISTAS DOBLES
//nodoListaDSubVenta *agregarAlFinalDSubVenta(nodoListaDSubVenta *lista, nodoListaDSubVenta *nuevoNodo);
//nodoListaDSubVenta *buscarUltimoDSubVenta(nodoListaDSubVenta *lista);
//nodoListaDSubVenta *crearNodoDoblesubVenta(subVenta A);
//nodoListaDSubVenta *inicListaDoblesubVenta();
//nodoListaDSubVenta *borrarnodoListaDSubVenta(nodoListaDSubVenta *lista, int idPedido);
//void showListsubVenta(nodoListaDSubVenta *lista)
//nodoListaDSubVenta* obtenerListaDSubVentas(nodoListaDSubVenta* lista);
//void mostrarsubVentaCorto(subVenta nombre);

//// FUNCIONES LISTA /////
nodoListaDSubVenta* obtenerListaDSubVentas(nodoListaDSubVenta* lista, int id)
{
    FILE* ptr = fopen("ArchivoUsuario.dat","rb");
     /// ACA HABRIA QUE BUSCAR EL USUARIO POR SU ID EN EL ARCHIVO, TRAER ESE USUARIO, y convertir su arreglo de subventas en lista

}

void mostrarsubVentaCorto(subVenta aux)
{
    printf("%s\n",aux.dato);
}

nodoListaDSubVenta *inicListaDoblesubVenta()
{

    return NULL;
}

nodoListaDSubVenta *crearNodoDoblesubVenta(subVenta A)
{

    nodoListaDSubVenta* aux = (nodoListaDSubVenta*) malloc(sizeof(nodoListaDSubVenta));

    aux->dato = A;

    aux->siguiente = NULL;
    aux->anterior = NULL;

    return aux;
}

nodoListaDSubVenta *buscarUltimoDSubVenta(nodoListaDSubVenta *lista)
{
    nodoListaDSubVenta *ultimo;

    if (lista == NULL)
    {

        ultimo = NULL;
    }
    else
    {
        if (lista->siguiente == NULL)
        {
            ultimo = lista;
        }
        else
        {
            ultimo = buscarUltimoDSubVenta(lista->siguiente);
        }
    }

    return ultimo;
}

nodoListaDSubVenta *agregarAlFinalDSubVenta(nodoListaDSubVenta *lista, nodoListaDSubVenta *nuevoNodo)
{

    if (lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nodoListaDSubVenta *ultimo = buscarUltimoDSubVenta(lista);
        ultimo->siguiente = nuevoNodo;
        nuevoNodo->anterior = ultimo;
    }

    return lista;
}


