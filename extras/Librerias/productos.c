#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#define ArchProductos "Stock.Dat"
#include "productos.h"

#define KEY_UP 72 +256
#define KEY_DOWN 80 +256
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_LEFT 75 +256
#define KEY_RIGHT 77 +256

int main()
{

    showArchive();



return 0;

}

/// CARGAR UN PRODUCTO A LOS ARCHIVOS.
void AltaProducto()
{
    FILE *buffer = fopen(ArchProductos, "ab");
    producto Aux;
    if (buffer != NULL)
    {

        Aux = cargarProducto();
        fwrite(&Aux, sizeof(producto), 1, buffer);
        fclose(buffer);
    }
    else
    {
        printf("\nNo se pudo abrir el archivo.\n");
    }
}

/// FUNCION AUXILIAR DE CARGA.
producto cargarProducto()
{

    producto nuevo;
    printf("Ingrese el nombre del producto: \n");
    fflush(stdin);
    gets(nuevo.nombre);
    printf("Ingrese una categoria: \n");
    showCategorias();
    fflush(stdin);
    gets(nuevo.categoria);
    printf("Ingrese una descripcion: (280 caracteres) \n");
    fflush(stdin);
    gets(nuevo.descripcion);
    printf("Ingrese el precio venta: \n");
    fflush(stdin);
    scanf("%f", &nuevo.precioVenta);
    printf("Ingrese precio de compra: \n");
    fflush(stdin);
    scanf("%f", &nuevo.precioCosto);
    fflush(stdin);
    printf("Ingrese la cantidad de stock: \n");
    scanf("%i", &nuevo.cantidad);
    nuevo.flagStock = 0;

    return nuevo;
}

/// Para descontar stock. Necesita modificacion. De momento descuenta de a 1.
void descontarStock(char aDescontar[100], char categoria[])
{

    FILE *buffer = fopen(ArchProductos, "r+b");
    producto Aux;
    int flag = 0;
    if (buffer != NULL)
    {

        while (fread(&Aux, sizeof(producto), 1, buffer) > 0 && flag == 0)
        {
            if (strcmpi(Aux.categoria, categoria) == 0)
            {

                if (0 == strcmpi(Aux.nombre, aDescontar))
                {
                    fseek(buffer, sizeof(producto) * (-1), SEEK_CUR);
                    Aux.cantidad = (Aux.cantidad - 1);
                    mostrarProducto(Aux);
                    fwrite(&Aux, sizeof(producto), 1, buffer);
                    flag = 1;
                    fclose(buffer);
                }
            }
        }
    }
}

/// MOSTRAR EL ARCHIVO

void showArchive()
{
    FILE *buffer = fopen(ArchProductos, "rb");
    producto Aux;
    if (buffer != NULL)
    {
        while (fread(&Aux, sizeof(producto), 1, buffer) > 0)
        {

            mostrarProducto(Aux);
        }
        fclose(buffer);
    }
}

/// MOSTRAR CATEGORIAS (PARA ELEGIR DONDE ASISGNAR EL PRODUCTO)
void showCategorias()
{
    printf("\nIngrese 1.1 para Smartphones Samsung. \n");
    printf("\nIngrese 1.2 para Smartphones Apple. \n");
    printf("\nIngrese 1.3 para Smartphones. \n");
    printf("\nIngrese 2.1 para Tablets Samsung. \n");
    printf("\nIngrese 2.2 para Tablets Apple. \n");
    printf("\nIngrese 2.3 para Otros Tablets. \n");
    printf("\nIngrese 3.1 para Notebooks Samsung. \n");
    printf("\nIngrese 3.2 para Notebooks Apple. \n");
    printf("\nIngrese 3.3 para Otras Notebooks. \n");
}

/// MUESTRA 1 SOLO PRODUCTO.
void mostrarProducto(producto A)
{
    printf("---------------------------------------------");
    printf("\nProducto: %s \n", A.nombre);
    printf("\nDescripcion: %s \n", A.descripcion);
    printf("\nValor Final: $ %.2f \n", A.precioVenta);
    printf("\nCosto: $ %.2f \n", A.precioCosto);
    printf("\nCantidad de stock: %i \n", A.cantidad);
    printf("---------------------------------------------");
    if (A.flagStock == 0)
    {
        printf("\nStock Disponible \n");
    }
    else
    {
        printf("\n Sin stock disponible. \n");
    }
}

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

    int cantColumnas = 0;

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
            cantColumnas++;
        }

        if(cantColumnas % 2 == 0)
        {
            posicionX = 45;
        }

        if(cantColumnas % 2 != 0)
        {
            posicionX = 2;
        }


        if((cantColumnas % 2 != 0) )
        {
            posicionY -= (contPaginas * 28);
        }

        if(cantColumnas % 2 == 0)
        {
            posicionY -=  (7 * cantColumnas)  + (contPaginas * 28);
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

int mostrarProductos(int id, int cursor) /// cursor es donde esta parado el >>>> , opcion es la tecla que introduce el usuario
{

    system("cls");
    nodoProductoD *lista = inicListaDobleProducto();
    lista = despersistirListaDobleProductos(lista);

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

    int opcion = capturarTecla2();

    gotoxy(0,0);
    //printf("cursor: %i", cursor); //// PARA VER EL CURSOR  --------------------------------------------------------------------------->
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
