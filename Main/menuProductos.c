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
#include "menuProductos.h"

/// ACA VAN TODOS LOS DEFINE, FUNCIONES Y SE DEBE CONECTAR A SU LIBRERIA.H (#include "ejemplo.h")

/// MENU ADMIN
int menuProductos2(int id, int cursor) /// cursor es donde esta parado el >>>> , opcion es la tecla que introduce el usuario
{

    system("cls");

    opciones arreglo[] = {"Stock disponible", "Buscar producto por nombre", "Agregar producto", "Modificar un producto", "Salir"};
    int cantidadOpciones = 5;

    dibujarCuadro(0,0,79,24); //SE DIBUJA EL CUADRO PRINCIPAL
    dibujarCuadro(1,1,78,3); //SE DIBUJA EL CUADRO DEL TITULO

    centrarTexto("E-COMMERCE - MENU PRODUCTOS",2);

    gotoxy(70,2);
    printf("ID: %i", id);

    /// MUESTRA LAS OPCIONES
    mostrarOpcionesProductos2(cantidadOpciones,arreglo,cursor);

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


    return menuProductos2(id, cursor);
}

/// MOSTRAR OPCIONES ADMIN
void mostrarOpcionesProductos2(int cantidadOpciones,opciones arreglo[], int cursor)
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

void switchProductos(int id, int opcion)
{
    int mostrar = 1;
    int categoria = 0;

    switch(opcion)
    {
    case 1:
        do
        {
        mostrar = mostrarStock(id,1);
        if(mostrar != 0)
        {
             mostrarUnProductoUsuario(id, mostrar);
            /// (mostrar producto pregunta si quiere añadirlo al carrito, de no querer vuelve al menu de productos ed querer pregunta cantidad y se agrega.
            /// funcion de mostrar el producto y añadir a carrito
        }
        } while(mostrar != 0);
        break;
    case 2:
        buscarProductoFuncion();
        break;
    case 3:
        cargarProductoNuevoFuncion();
        break;
    case 4:
        break;
    case 5:
        return 0;
        break;
    default:
        break;
    }
}


//BUSCAR PRODUCTO
void buscarProductoFuncion()
{
    system("cls");
    dibujarCuadro(0,0,79,24); //SE DIBUJA EL CUADRO PRINCIPAL
    dibujarCuadro(1,1,78,3); //SE DIBUJA EL CUADRO DEL TITULO
    dibujarCuadro(0,0,79,24); //SE DIBUJA EL CUADRO PRINCIPAL
    dibujarCuadro(1,1,78,3); //SE DIBUJA EL CUADRO DEL TITULO

    centrarTexto("E-COMMERCE - BUSCAR PRODUCTOS",2);
    int id = 3;
    gotoxy(70,2);
    nodoProductoD* listaProductos;
    listaProductos = NULL;
    listaProductos = despersistirListaDobleProductos(listaProductos);
    gotoxy(3,5);
    char productoBuscado[50];
    ingresarProductoAbuscar(productoBuscado);
    gotoxy(3,5);
    buscarProducto(listaProductos,productoBuscado);

    return 0;
}
//

void ingresarProductoAbuscar(char productoBuscado[50])
{
    printf("BUSCAR PRODUCTO: ");
    gets(productoBuscado);
    gotoxy(3,6);
}

void buscarProducto(nodoProductoD* listaProductos,char productoBuscado[])
{
    nodoProductoD * seg = listaProductos;
    producto produAux;
    printf("PRODUCTO BUSCADO: %s\n", productoBuscado);
    if(seg != NULL)
    {
        while((seg != NULL)&& strcmpi(seg->dato.nombre, productoBuscado) != 0)
        {
            seg = seg->siguiente;
        }
            if(strcmpi(seg->dato.nombre, productoBuscado) >= 0)
            {
                gotoxy(3,6);
                sleep(1);
                printf("Producto encontrado\n");
                produAux = seg->dato;
                sleep(2);
                mostrarProductoAdmin(produAux);
                seg = seg->siguiente;
            }
    }
    else{
        gotoxy(3,8);
        printf("No se encontro el producto buscado!\n");
    }
    gotoxy(20,20);system("pause");
}

void mostrarProductoAdmin(producto produ) //FUNCION MOSTRAR LISTA CARGADA
{
        gotoxy(3,8);
        printf("NOMBRE: %s \n", produ.nombre);
        gotoxy(3,9);
        printf("DESCRIPCION: %s \n", produ.descripcion);
        gotoxy(3,10);
        printf("PRECIO VENTA: %c%.2f \n",36, produ.precioVenta);
        gotoxy(3,11);
        printf("PRECIO COSTO: %c%.2f \n",36, produ.precioCosto);
        gotoxy(3,12);
        printf("CANTIDAD: %d \n", produ.cantidad);
        gotoxy(3,13);
        //printf("STOCK: %i  ( 0 en stock // 1 fuera de stock ) \n", produ.flagStock);
        printf("\n");
}

//AGREGAR UN PRODUCTO
void cargarProductoNuevoFuncion()
{
    system("cls");
    dibujarCuadro(0,0,79,24); //SE DIBUJA EL CUADRO PRINCIPAL
    dibujarCuadro(1,1,78,3); //SE DIBUJA EL CUADRO DEL TITULO
    dibujarCuadro(0,0,79,24); //SE DIBUJA EL CUADRO PRINCIPAL
    dibujarCuadro(1,1,78,3); //SE DIBUJA EL CUADRO DEL TITULO

    centrarTexto("E-COMMERCE - AGREGAR PRODUCTOS",2);
    gotoxy(70,2);
    gotoxy(3,5);
    agregarProductoAdmin();
    int opcion = capturarTeclaSiNo();
    if(opcion == KEY_ESC)
    {
        return 0;
    }
    return 0;
}
//

void showCategoriasAdmin()
{
    gotoxy(3,5);printf("Ingrese 1.1 Smartphones Samsung.");
    gotoxy(3,6);printf("Ingrese 1.2 Smartphones Apple.");
    gotoxy(3,7);printf("Ingrese 1.3 Smartphones.");
    gotoxy(3,8);printf("Ingrese 2.1 Tablets Samsung.");
    gotoxy(3,9);printf("Ingrese 2.2 Tablets Apple.");
    gotoxy(43,5);printf("Ingrese 2.3 Otros Tablets.");
    gotoxy(43,6);printf("Ingrese 3.1 Notebooks Samsung.");
    gotoxy(43,7);printf("Ingrese 3.2 Notebooks Apple.");
    gotoxy(43,8);printf("Ingrese 3.3 Otras Notebooks.");
}

producto cargarProductoAdmin()
{
    producto nuevo;

    gotoxy(3,5);borrarPantallaCorto();
    gotoxy(3,5);printf("Ingrese el nombre del producto:         \n");
    fflush(stdin);
    gotoxy(3,6);gets(nuevo.nombre);
    darFormatoHoja();
    gotoxy(3,8);showCategoriasAdmin();
    gotoxy(3,11);printf("Ingrese una categoria: \n");
    fflush(stdin);
    gotoxy(3,12);gets(nuevo.categoria);
    gotoxy(3,5);borrarPantallaCorto();
    gotoxy(3,5);printf("Ingrese una descripcion: (280 caracteres) \n");
    fflush(stdin);
    gotoxy(3,6);gets(nuevo.descripcion);
    gotoxy(3,7);printf("Ingrese el precio venta: \n");
    fflush(stdin);
    gotoxy(3,8);scanf("%f", &nuevo.precioVenta);
    gotoxy(3,9);printf("Ingrese precio de compra: \n");
    fflush(stdin);
    gotoxy(3,10);scanf("%f", &nuevo.precioCosto);
    fflush(stdin);
    gotoxy(3,11);printf("Ingrese la cantidad de stock: \n");
    gotoxy(3,12);scanf("%i", &nuevo.cantidad);
    gotoxy(3,13);
    nuevo.flagStock = 0;
    mostrarProductoCargado(nuevo);

    return nuevo;
}

void agregarProductoAdmin()
{
    FILE *buffer = fopen("Stock.dat", "ab");
    producto Aux;

    printf("Desea agregar un producto a la lista?\n");
    //gotoxy(30,7);
    int respuesta;
    gotoxy(3,8);
    respuesta = seleccionarSiNoMenuProducto(1);
    borrarPantallaLargo();
    darFormatoHoja();
    if(respuesta == 1)
    {
        if (buffer != NULL)
        {
            gotoxy(40,20);
            Aux = cargarProductoAdmin();
            fwrite(&Aux, sizeof(producto), 1, buffer);
            fclose(buffer);
        }
        else
        {
            printf("\nNo se pudo abrir el archivo.\n");
        }
    }
    else
    {
        return 0;
    }
}

void darFormatoHoja()
{
    dibujarCuadro(0,0,79,24); //SE DIBUJA EL CUADRO PRINCIPAL
    dibujarCuadro(1,1,78,3); //SE DIBUJA EL CUADRO DEL TITULO
    dibujarCuadro(0,0,79,24); //SE DIBUJA EL CUADRO PRINCIPAL
    dibujarCuadro(1,1,78,3); //SE DIBUJA EL CUADRO DEL TITULO
    centrarTexto("E-COMMERCE - AGREGAR PRODUCTOS",2);
    gotoxy(70,2);
    gotoxy(3,5);
    dibujarCuadro(1,21,78,23); //SE DIBUJA EL CUADRO MENSAJE DE CONSOLA
    gotoxy(33,22);
    printf("MENU PRODUCTOS");

}

void borrarPantallaLargo()
{
    gotoxy(3,5);printf("                                                                          ");
    gotoxy(3,6);printf("                                                                          ");
    gotoxy(3,7);printf("                                                                          ");
    gotoxy(3,8);printf("                                                                          ");
    gotoxy(3,9);printf("                                                                          ");
    gotoxy(3,10);printf("                                                                         ");
    gotoxy(3,11);printf("                                                                         ");
    gotoxy(3,12);printf("                                                                         ");
    gotoxy(3,13);printf("                                                                         ");
    gotoxy(3,14);printf("                                                                         ");
    gotoxy(3,15);printf("                                                                         ");
    gotoxy(3,16);printf("                                                                         ");
    gotoxy(3,17);printf("                                                                         ");
    gotoxy(3,18);printf("                                                                         ");
    gotoxy(3,19);printf("                                                                         ");
    gotoxy(3,20);printf("                                                                         ");
    gotoxy(3,21);printf("                                                                         ");
    gotoxy(3,22);printf("                                                                         ");
}

void borrarPantallaCorto()
{
    gotoxy(3,5);printf("                                                                          ");
    gotoxy(3,6);printf("                                                                          ");
    gotoxy(3,7);printf("                                                                          ");
    gotoxy(3,8);printf("                                                                          ");
    gotoxy(3,9);printf("                                                                          ");
    gotoxy(3,10);printf("                                                                         ");
    gotoxy(3,11);printf("                                                                         ");
    gotoxy(3,12);printf("                                                                         ");
    gotoxy(3,13);printf("                                                                         ");
    gotoxy(3,14);printf("                                                                         ");
    gotoxy(3,15);printf("                                                                         ");
}

void mostrarProductoCargado(producto nuevo)
{
    gotoxy(3,5);borrarPantallaCorto();
    gotoxy(3,5);printf("PRODUCTO NUEVO\n");
    gotoxy(3,6);printf("Producto: %s\n",nuevo.nombre);
    gotoxy(3,7);printf("Categoria: %s \n",nuevo.categoria);
    gotoxy(3,8);printf("Descripcion: %s \n",nuevo.descripcion);
    gotoxy(3,9);printf("Precio de venta: %c%.2f \n",36,nuevo.precioVenta);
    gotoxy(3,10);printf("Precio de compra: %c%.2f \n",36,nuevo.precioCosto);
    gotoxy(3,11);printf("Cantidad de stock: %i \n",nuevo.cantidad);
}


// FUNCIONES EXCLUSIVAS DE SELECTOR MENU PRODUCTO
int seleccionarSiNoMenuProducto(int cursor) /// 1 ES SI 2 ES NO
{
    mostrarSiNoMenuProducto(cursor);

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

    return seleccionarSiNoMenuProducto(cursor);
}

void mostrarSiNoMenuProducto(int cursor)
{
    gotoxy(28,20);
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


