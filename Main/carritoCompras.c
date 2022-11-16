#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define KEY_UP 72 + 256
#define KEY_DOWN 80 + 256
#define KEY_ENTER 13
#define KEY_ESC 27
#include "UserLibs.h"
#include "carritoCompras.h"
#define  ArchivoUsuarios "ArchivoUsuario.dat"
#include "ventas.h"

/// ACA VAN TODOS LOS DEFINE, FUNCIONES Y SE DEBE CONECTAR A SU LIBRERIA.H (#include "ejemplo.h")

/// FUNCIONES DEL CARRITO SUBVENTA
void agregarAlCarrito(int idCliente, int cantidadProductos, producto Dato)
{

    FILE *bufferUsuarios = fopen(ArchivoUsuarios, "r+b");

    usuario Aux;

    usuario temporal = BuscarUsuario(idCliente);

    producto deseado = ObtenerProducto(Dato);

    float subtotal = (deseado.precioVenta * cantidadProductos);

//    printf("\nAux username: %s     Temporal username: %s\n", Aux.username, temporal.username);
//    system("pause");
    if (bufferUsuarios)
    {
        while (fread(&Aux, sizeof(usuario), 1, bufferUsuarios) > 0)
        {
            if (strcmpi(Aux.username, temporal.username) >= 0)
            {

                fseek(bufferUsuarios, sizeof(usuario) * (-1), SEEK_CUR);
                Aux.carrito[Aux.validosCarrito].dato = Dato;
                Aux.carrito[Aux.validosCarrito].cantidad = cantidadProductos;
                Aux.carrito[Aux.validosCarrito].subtotal = subtotal;
//                gotoxy(10,14);
//                printf("AUX USUARIO: %s VALIDOS CARRITO: %i\n", Aux.username, Aux.validosCarrito);
//                printf("DATOS DEL AUX: PRODUCTO: %s CANTIDAD: %i SUBTOTAL: %f", Aux.carrito[Aux.validosCarrito].dato.nombre,Aux.carrito[Aux.validosCarrito].cantidad, Aux.carrito[Aux.validosCarrito].subtotal);
                Aux.validosCarrito = (Aux.validosCarrito + 1);
                fwrite(&Aux, sizeof(usuario), 1, bufferUsuarios);
                fclose(bufferUsuarios);
            }
        }
    }
}

producto ObtenerProducto(producto dato)
{
    FILE *bufferStock = fopen("Stock.dat", "rb");

    producto temporal;

    int flagProductos = 0;

    if (bufferStock)
    {
        while (fread(&temporal, sizeof(producto), 1, bufferStock) > 0 && flagProductos == 0)
        {
            if (strcmpi(temporal.nombre, dato.nombre) == 0)
            {

                flagProductos = 1;
                fclose(bufferStock);
            }
        }
    }
    return temporal;
}

usuario BuscarUsuario(int idCliente)
{
    int flagUsuarios = 0;

    usuario Aux;

    usuario Deseado;

    FILE *bufferUsuarios = fopen(ArchivoUsuarios, "rb");
    if (bufferUsuarios != NULL)
    {
        while ((fread(&Aux, sizeof(usuario), 1, bufferUsuarios) > 0) && flagUsuarios == 0)
        {
            if (Aux.idCliente == idCliente)
            {
                Deseado = Aux;
                flagUsuarios = 1;
            }
        }
        fclose(bufferUsuarios);
    }

    return Deseado;
}

/*void MostrarArregloCarrito(int id)
{
    FILE *buffer = fopen("Usuarios.dat", "rb");
    int flag = 0;
    usuario Aux;
    if (buffer)
    {
        while (fread(&Aux, sizeof(usuario), 1, buffer) > 0 && flag == 0)
        {
            if (A.idCliente == id)
            {
                showArray(A);
                flag = 1;
            }
        }
    }
}

void showArray(usuario A)
{
    for (int i = 0; i < A.validosCarrito; i++)
    {
        printf("\nValidos Carrito: %i ", A.validosCarrito);
        printf("\nProducto: %s ", A.carrito[i].dato.nombre);
        printf("\nCantidad deseada: %i ", A.carrito[i].cantidad);
        printf("\nSubtotal: $%.2f ", A.carrito[i].subtotal);
        i++;
    }
}*/

/// NODOCARRITO

nodoListaDSubVenta *despersistirListaDSubVenta(nodoListaDSubVenta *lista)
{
    FILE *ptr = fopen(ArchivoUsuarios, "rb");

    usuario aux;

    nodoListaDSubVenta *aux2;

    if (ptr != NULL)
    {
        while (fread(&aux, sizeof(usuario), 1, ptr) > 0)
        {
            lista = obtenerSubVenta(aux, lista);
        }
        fclose(ptr);
    }
    return lista;
}

nodoListaDSubVenta *obtenerSubVenta(usuario A, nodoListaDSubVenta *lista)
{
    int i = 0;
    subVenta aux;
    nodoListaDSubVenta *nuevo;

    for (int i = 0; i < A.validosCarrito; i++)
    {
        nuevo = crearNodoDSubVenta(A.carrito[i]);
        lista = agregarAlFinalDSubVenta(lista, nuevo);
    }

    return lista;
}

nodoListaDSubVenta *inicListaDSubVenta()
{

    return NULL;
}

nodoListaDSubVenta *crearNodoDSubVenta(subVenta A)
{

    nodoListaDSubVenta *nuevo = (nodoListaDSubVenta *)malloc(sizeof(nodoListaDSubVenta));
    nuevo->dato = A;
    nuevo->sig = NULL;
    nuevo->ant = NULL;

    return nuevo;
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
        if (lista->sig == NULL)
        {
            ultimo = lista;
        }
        else
        {
            ultimo = buscarUltimoDSubVenta(lista->sig);
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
        ultimo->sig = nuevoNodo;
        nuevoNodo->ant = ultimo;
    }

    return lista;
}

int mostrarsubVentas(int id, int cursor) /// cursor es donde esta parado el >>>> , opcion es la tecla que introduce el usuario
{

    system("cls");
    nodoListaDSubVenta *lista = inicListaDSubVenta();
    lista = despersistirListaDSubVenta(lista);

    dibujarCuadro(0, 0, 79, 24); // SE DIBUJA EL CUADRO PRINCIPAL
    dibujarCuadro(1, 1, 78, 3);  // SE DIBUJA EL CUADRO DEL TITULO

    centrarTexto("E-COMMERCE - CARRITO DE COMPRAS", 2);

    gotoxy(70, 2);
    printf("ID: %i", id);

    /// TABLA HEADERS DE E-COMMERCE CARRITO
    gotoxy(9, 4);
    printf("PRODUCTO");
    gotoxy(33, 4);
    printf("PRECIO");
    gotoxy(50, 4);
    printf("CANTIDAD");
    gotoxy(68, 4);
    printf("SUBTOTAL");

    gotoxy(62, 20);
    printf("TOTAL A PAGAR: ");

    /// MUESTRA LAS OPCIONES
    gotoxy(9,7);
    int cantidadOpciones = contarOpcionessubVentas(lista);
    // printf("\ncantidadOpciones: %i", cantidadOpciones);
    // system("pause");

    mostrarOpcionesCarrito(lista, cursor);

    gotoxy(65, 21);
    /// ACA SE DEBERIA PRINTEAR LA SUMA TOTAL DEL CARRITO
    printf("$9999,99");
    char option;
    gotoxy(7, 21);
    printf("Para confirmar la compra presionar 'S'"); /// 115 codigo ascii s minuscula // 83 mayuscula
    dibujarCuadro(1, 19, 78, 23);                     // SE DIBUJA EL CUADRO MENSAJE DE CONSOLA
    ocultarCursor();
    int opcion = capturarTeclaCarrito();
    gotoxy(0, 0);
    printf("cursor: %i", cursor); //// PARA VER EL CURSOR  --------------------------------------------------------------------------->
    // system("pause");

    /// SONIDO
    if (opcion == KEY_ENTER)
    {
        Beep(400, 80);
    }
    else if (opcion == KEY_ESC)
    {
        Beep(800, 80);
    }
    else
    {
        Beep(600, 80);
    }

    if (opcion == KEY_ESC)
    {
        /// TERMINA LA EJECUCION
        return 0;
    }

    if (opcion == KEY_ENTER)
    {
        /// ACA RETORNA EL CURSOR EN LA POSICION A EDITAR DE LA SUBVENTA EN LA LISTA
        return cursor;
    }

    if ((opcion == KEY_S) || (opcion == KEY_s))
    {
        generarCompra(id,888); /// en el numero iria el total de gasto de la factura.

    if (opcion == KEY_UP)
    {
        if (cursor - 1 > 0)
        {
            cursor -= 1;
        }
    }

    if (opcion == KEY_DOWN)
    {
        if (cursor + 1 <= cantidadOpciones)
        {
            cursor += 1;
        }
    }

    if (opcion == KEY_LEFT)
    {
        if (cursor - 6 > 0)
        {
            cursor -= 6;
        }
    }

    if (opcion == KEY_RIGHT)
    {
        if (cursor + 6 <= cantidadOpciones)
        {
            cursor += 6;
        }
    }

    return mostrarsubVentas(id, cursor);
}


int contarOpcionessubVentas(nodoListaDSubVenta *lista)
{
    int contador = 0;

    if (lista == NULL)
    {
        printf("lista vacia");
    }

    while (lista != NULL)
    {
        contador++;
        lista = lista->sig;
    }

    return contador;
}

/// MOSTRAR OPCIONES
void mostrarOpcionesCarrito(nodoListaDSubVenta *lista, int cursor)
{
    nodoListaDSubVenta *anterior;
    int posicionY;
    int posicionX;
    int contPaginas = ceil(((float)cursor / 6));

    int i = 1 + ((contPaginas - 1) * 6);

    int cantidadxColumna = 6;

    int cantColumnas = 0;

    /// esto ya deberia funcionar para navegar en el menu en todas las direcciones de no funcionar
    /// hay que revisar en mostrar subVentas los if a ver si deberiamos poner +1 -1 en condiciones = <=

    int tope = i + 5;

    for (int i = 0; i < ((contPaginas - 1) * 6); i++)
    {
        lista = lista->sig;
    }

    while ((lista != NULL) && (i <= tope))
    {
        posicionY = 14 + 3 + i * 2;

        if ((i - 1) % 6 == 0 && i != 0)
        {
            cantColumnas++;
        }

        posicionX = 2;

        if ((cantColumnas % 2 != 0))
        {
            posicionY -= (contPaginas * 12);
        }

        gotoxy(posicionX, posicionY);

        if (i == cursor)
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
        printf("%-21s   %-15.0f   %-15i   %.0f", lista->dato.dato.nombre, lista->dato.dato.precioVenta, lista->dato.cantidad, lista->dato.subtotal);
        //        gotoxy(0,0);
        //        //printf("cantColumnas: %i i = %i",cantColumnas, i);
        //        printf("posicionY: %i",posicion);
        //        system("pause");

        i++;
        anterior = lista;
        lista = lista->sig;
    }
}

int capturarTeclaCarrito()
/// CAPTURAR INFORMACION TECLA PRESIONADA
{
    int tecla;
    int opcion;

    do
    {
        tecla = getch();
        if (tecla == 0 || tecla == 224)
        {
            tecla = 256 + getch();
        }

    }
    while ((tecla != KEY_UP) && (tecla != KEY_DOWN) && (tecla != KEY_ESC) && (tecla != KEY_ENTER) && (tecla != KEY_LEFT) && (tecla != KEY_RIGHT) && (tecla !=KEY_S) && (tecla!=KEY_s));

    switch (tecla)
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
    case KEY_S:
        opcion = KEY_S;
        break;
    case KEY_s:
        opcion = KEY_s;
        break;
    default:
        printf("\nDEFAULT!");
        system("pause");
        break;
    }

    return opcion;
}
