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
    struct nodoProductoD* siguiente;
    struct nodoProductoD* anterior;
} nodoProductoD;

/// ESTRUCTURAS
typedef struct
{
    char nombre[50];
} opciones; // OPCIONES DEL MENU

/// PROTOTIPOS DE LAS FUNCIONES
void dibujarCuadro(int x1,int y1,int x2,int y2);
void gotoxy(int x,int y);
void desactivarMaximizar();
int mostrarProductos(int id, int cursor);
int capturarTecla();
void ocultarCursor();
int contarOpcionesProductos(nodoProductoD* lista);
void suma();

/// PROTOTIPADO DE LISTAS
nodoProductoD *agregarAlFinalDobleProducto(nodoProductoD *lista, nodoProductoD *nuevoNodo);
nodoProductoD *buscarUltimoDobleProducto(nodoProductoD *lista);
nodoProductoD *crearNodoDobleProducto(producto A);
nodoProductoD *inicListaDobleProducto();
nodoProductoD *borrarnodoProductoD(nodoProductoD *lista, int idPedido);
void showListproducto(nodoProductoD *lista);
nodoProductoD* despersistirListaDobleProductos(nodoProductoD* lista);
void mostrarProductoCorto(producto nombre);
nodoProductoD* moveToList(nodoProductoD* lista);

//FUNCION PRINCIPAL MAIN
int main()
{

    /// ESTILO DE MENU (GENERICO PARA TODOS LOS MENUS)
    desactivarMaximizar();
    system("mode con: cols=80 lines=25"); //SE DEFINE LAS DIMENSIONES DE LA productoNA DEL PROGRAMA A 80 COLUMNAS Y 25 FILAS
    system("COLOR 0A"); //SE DA UN COLOR DE FONDO Y COLOR A LAS LETRAS /// E0 // 5F // B0
    int id = 1;

    int opcion = mostrarProductos(1,1);

//    system("cls");
//    printf("opcion = %i", opcion);
//    system("pause");

    /// PAUSAR EJECUCION
    printf("\n");
    gotoxy(40,40);
    system("cls");
    return 0;
}

void mostrarListaTrucho(nodoProductoD* lista)
{
    while(lista != NULL)
    {
        mostrarProductoCorto(lista->dato);
        lista = lista->siguiente;
    }

}

/// PASAR A LIBRERIA
int mostrarProductos(int id, int cursor) /// cursor es donde esta parado el >>>> , opcion es la tecla que introduce el usuario
{

    system("cls");
    nodoProductoD *lista = inicListaDobleProducto();
    lista = despersistirListaDobleProductos(lista);
    lista = despersistirListaDobleProductos(lista);
    lista = despersistirListaDobleProductos(lista);
    lista = despersistirListaDobleProductos(lista);
    lista = despersistirListaDobleProductos(lista);
    lista = despersistirListaDobleProductos(lista);

//    mostrarListaTrucho(lista);
//    system("pause");
//    system("cls");

    dibujarCuadro(0,0,79,24); //SE DIBUJA EL CUADRO PRINCIPAL
    dibujarCuadro(1,1,78,3); //SE DIBUJA EL CUADRO DEL TITULO

    centrarTexto("E-COMMERCE - PRODUCTOS",2);

    gotoxy(70,2);
    printf("ID: %i", id);




    /// MUESTRA LAS OPCIONES
    int cantidadOpciones = contarOpcionesProductos(lista);
    //printf("\ncantidadOpciones: %i", cantidadOpciones);
    //system("pause");

    mostrarOpcionesProductos(lista,cursor);

    gotoxy(7,21);
    printf("Para salir presionar ESC");
    dibujarCuadro(1,19,78,23); //SE DIBUJA EL CUADRO MENSAJE DE CONSOLA
    ocultarCursor();

    int opcion = capturarTecla();

    gotoxy(0,0);
    printf("cursor: %i", cursor);
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
            cursor += 7;
        }
    }

    return mostrarProductos(id, cursor);
}

void mostrarOpciones(int cantidadOpciones,opciones arreglo[], int cursor)
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

void centrarTexto(char *texto, int y)
{
    int longitud = strlen(texto); // mitad de ancho de pantalla - longitud de texto / 2
    gotoxy(40-(longitud/2),y);
    printf(texto);
}

int contarOpcionesProductos(nodoProductoD* lista)
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
void mostrarOpcionesProductos(nodoProductoD* lista, int cursor)
{
    nodoProductoD* anterior;
    int posicionY;
    int posicionX;
    int contPaginas = ceil(((float)cursor/14));

    int i=  1 + ((contPaginas-1)*14);

    int cantidadxColumna = 7;

    int contColumnas = 0;

    /// esto ya deberia funcionar para navegar en el menu en todas las direcciones de no funcionar
    /// hay que revisar en mostrar productos los if a ver si deberiamos poner +1 -1 en condiciones = <=

    int tope = i + 13;

    for(int i = 0; i < ((contPaginas-1)*14); i++)
    {
        lista = lista->siguiente;
    }

    while((lista != NULL)  && (i <= tope))
    {
        posicionY = 28 + 3 + i*2;

        if((i-1) % 7 == 0 && i != 0)
        {
            contColumnas++;
        }

        if(contColumnas % 2 == 0)
        {
            posicionX = 45;
        }

        if(contColumnas % 2 != 0)
        {
            posicionX = 2;
        }


        if((contColumnas % 2 != 0) )
        {
            posicionY -= (contPaginas * 28);
        }

        if(contColumnas % 2 == 0)
        {
            posicionY -=  (7 * contColumnas)  + (contPaginas * 28);
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

        printf("%s", lista->dato.nombre);

//        gotoxy(0,0);
//        //printf("Contcolumnas: %i i = %i",contColumnas, i);
//        printf("posicionY: %i",posicion);
//        system("pause");

        i++;
        anterior = lista;
        lista = lista->siguiente;
    }
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
//nodoProductoD *agregarAlFinalDobleProducto(nodoProductoD *lista, nodoProductoD *nuevoNodo);
//nodoProductoD *buscarUltimoDobleProducto(nodoProductoD *lista);
//nodoProductoD *crearNodoDobleProducto(producto A);
//nodoProductoD *inicListaDobleProducto();
//nodoProductoD *borrarnodoProductoD(nodoProductoD *lista, int idPedido);
//void showListproducto(nodoProductoD *lista)
//nodoProductoD* despersistirListaDobleProductos(nodoProductoD* lista);
//void mostrarProductoCorto(producto nombre);

//// FUNCIONES LISTA /////
nodoProductoD* despersistirListaDobleProductos(nodoProductoD* lista)
{
    FILE* ptr = fopen("Stock.dat","rb");
    producto aux;
    nodoProductoD* aux2;

    if(ptr != NULL)
    {
        while(fread(&aux,sizeof(producto),1,ptr) > 0)
        {
            aux2 = crearNodoDobleProducto(aux);
            lista = agregarAlFinalDobleProducto(lista,aux2);
        }
        fclose(ptr);
    }
    return lista;
}

nodoProductoD* moveToList(nodoProductoD* lista)
{
    producto Aux;
    nodoProductoD* Temporal;

    FILE* buffer = fopen("Stock.dat", "rb");

    if (buffer != NULL)
    {
        while (fread(&Aux, sizeof(producto), 1, buffer) > 0)
        {
            mostrarProductoCorto(Aux);
            Temporal = crearNodoDobleProducto(Aux);
            printf("TEST");
            lista = agregarAlFinalDobleProducto(lista, Temporal);
            printf("TEST");
        }
        fclose(buffer);
    }

    return lista;
}

void mostrarProductoCorto(producto aux)
{
    printf("%s\n",aux.nombre);
}

nodoProductoD *inicListaDobleProducto()
{

    return NULL;
}

nodoProductoD *crearNodoDobleProducto(producto A)
{

    nodoProductoD* aux = (nodoProductoD*) malloc(sizeof(nodoProductoD));

    aux->dato = A;

    aux->siguiente = NULL;
    aux->anterior = NULL;

    return aux;
}

nodoProductoD *buscarUltimoDobleProducto(nodoProductoD *lista)
{
    nodoProductoD *ultimo;

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
            ultimo = buscarUltimoDobleProducto(lista->siguiente);
        }
    }

    return ultimo;
}

nodoProductoD *agregarAlFinalDobleProducto(nodoProductoD *lista, nodoProductoD *nuevoNodo)
{

    if (lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nodoProductoD *ultimo = buscarUltimoDobleProducto(lista);
        ultimo->siguiente = nuevoNodo;
        nuevoNodo->anterior = ultimo;
    }

    return lista;
}

//nodoProductoD *borrarnodoProductoD(nodoProductoD *lista, int idPedido)
//{
//
//    nodoProductoD *seg;
//    nodoProductoD *ante;
//    subproducto temporal;
//
//    if ((lista != NULL) && (lista->articulo.id == idPedido))
//    {
//
//        nodoProductoD *aux = lista;
//        temporal = aux->lista = lista->siguiente;
//        free(aux);
//    }
//    else
//    {
//        seg = lista;
//    }
//    while ((seg != NULL) && (seg->articulo.articulo != idPedido))
//    {
//
//        ante = seg;
//        seg = seg->siguiente;
//    }
//    if (seg != NULL)
//    {
//        ante->siguiente = seg->siguiente;
//        temporal = seg->articulo;
//        free(seg);
//    }
//
//    return lista;
//}

