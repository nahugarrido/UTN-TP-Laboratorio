#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define KEY_UP 72 +256
#define KEY_DOWN 80 +256
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_LEFT 75 +256
#define KEY_RIGHT 77 +256
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
    int cursor = 1;

//    nodoCategoria *lista = inicListaDobleProducto();
//    lista = cargarListaDeListas(lista);

    switch(opcion)
    {
    case 1:
        do
        {
            nodoCategoria *lista = inicListaDobleProducto();
            lista = cargarListaDeListas(lista);

            categoria = mostrarCategorias(id,cursor);

            if(categoria != 0 && lista != NULL)
            {
                for(int i = 1; i < categoria; i++)
                {
                    lista = lista->siguiente;
                }
                /// ACA SE HACE EL DO WHILE DE PRODUCTOS QUE ANTES SE HACIA SOLO
                do
                {
                    mostrar = mostrarStock(id,1,lista->Categoria.nroCategoria);
                    if(mostrar != 0)
                    {
                        mostrarUnProductoUsuario(id, mostrar, lista->Categoria.nroCategoria);
                        /// (mostrar producto pregunta si quiere añadirlo al carrito, de no querer vuelve al menu de productos ed querer pregunta cantidad y se agrega.
                        /// funcion de mostrar el producto y añadir a carrito
                    }
                }
                while(mostrar != 0);
                cursor = categoria;
            }

        }
        while(categoria != 0);
        break;
    case 2:
        buscarProductoFuncion();
        break;
    case 3:
        cargarProductoNuevoFuncion();
        break;
    case 4:
        modificarUnProducto();
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

    centrarTexto("E-COMMERCE - BUSCAR PRODUCTOS",2);

    dibujarCuadro(1,19,78,23); //SE DIBUJA EL CUADRO MENSAJE DE CONSOLA
    gotoxy(9,21);
    printf("Mensaje de consola ...");

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
        if(strcmpi(seg->dato.nombre, productoBuscado) == 0)
        {
            gotoxy(3,7);
            sleep(1);
            printf("Producto encontrado\n");
            produAux = seg->dato;
            sleep(2);
            mostrarProductoAdmin(produAux);
            seg = seg->siguiente;
        }
        else
        {
            gotoxy(3,7);
            printf("Producto no encontrado\n");
        }
    }
    else
    {
        gotoxy(3,8);
        printf("No se encontro el producto buscado!\n");
    }
    gotoxy(7,21);
    printf("Para salir presionar ESC");


    int opcion = capturarTecla2();


    if(opcion == KEY_ESC)
    {
        Beep(800,80);
    }

    if (opcion == KEY_ESC)
    {
        return 0;
    }
}

void mostrarProductoAdmin(producto produ) //FUNCION MOSTRAR LISTA CARGADA
{
    gotoxy(3,9);
    printf("NOMBRE: %s \n", produ.nombre);
    gotoxy(3,10);
    printf("DESCRIPCION: %s \n", produ.descripcion);
    gotoxy(3,11);
    printf("PRECIO VENTA: %c%.2f \n",36, produ.precioVenta);
    gotoxy(3,12);
    printf("PRECIO COSTO: %c%.2f \n",36, produ.precioCosto);
    gotoxy(3,13);
    printf("CANTIDAD: %d \n", produ.cantidad);
    gotoxy(3,14);
    //printf("STOCK: %i  ( 0 en stock // 1 fuera de stock ) \n", produ.flagStock);
    printf("\n");
}

//AGREGAR UN PRODUCTO
void cargarProductoNuevoFuncion()
{
    system("cls");
    dibujarCuadro(0,0,79,24); //SE DIBUJA EL CUADRO PRINCIPAL
    dibujarCuadro(1,1,78,3); //SE DIBUJA EL CUADRO DEL TITULO

    centrarTexto("E-COMMERCE - AGREGAR PRODUCTOS",2);
    dibujarCuadro(1,19,78,23); //SE DIBUJA EL CUADRO MENSAJE DE CONSOLA

//    gotoxy(9,21);
//    printf("Mensaje de consola ...");

    gotoxy(70,2);
    gotoxy(3,5);
    agregarProductoAdmin();

    sleep(1);
    return 0;
}
//

void showCategoriasAdmin()
{
    gotoxy(3,5);
    printf("Ingrese 1.1 Samsung.                        ");
    gotoxy(3,6);
    printf("Ingrese 1.2 Apple.                          ");
    gotoxy(3,7);
    printf("Ingrese 1.3 LG.                             ");
    gotoxy(3,8);
    printf("Ingrese 1.4 Sony.                           ");
    gotoxy(3,9);
    printf("Ingrese 1.5 Otros.                          ");
//    gotoxy(43,5);printf("Ingrese 2.3 Otros Tablets.");
//    gotoxy(43,6);printf("Ingrese 3.1 Notebooks Samsung.");
//    gotoxy(43,7);printf("Ingrese 3.2 Notebooks Apple.");
//    gotoxy(43,8);printf("Ingrese 3.3 Otras Notebooks.");
}

producto cargarProductoAdmin()
{
    producto nuevo;

    gotoxy(3,5);
    borrarPantallaCorto();
    dibujarCuadro(1,19,78,23); //SE DIBUJA EL CUADRO MENSAJE DE CONSOLA
    gotoxy(9,21);
    printf("                                    ");
    gotoxy(9,21);
    printf("Mensaje de consola ...");
    gotoxy(3,5);
    printf("Ingrese el nombre del producto: \n");
    fflush(stdin);
    gotoxy(3,6);
    gets(nuevo.nombre);
    darFormatoHoja();
    gotoxy(3,8);
    showCategoriasAdmin();
    gotoxy(3,11);
    printf("Ingrese una categoria (nombre): \n");
    fflush(stdin);
    gotoxy(3,12);
    gets(nuevo.nombreCategoria);
    gotoxy(3,13);
    printf("Ingrese el nro de la categoria (numero): \n");
    gotoxy(3,14);
    scanf("%i", &nuevo.nroCategoria);
    gotoxy(3,5);
    borrarPantallaCorto();
    gotoxy(3,5);
    printf("Ingrese una descripcion: (280 caracteres) \n");
    fflush(stdin);
    gotoxy(3,6);
    gets(nuevo.descripcion);
    gotoxy(3,7);
    printf("Ingrese el precio venta: \n");
    fflush(stdin);
    gotoxy(3,8);
    scanf("%f", &nuevo.precioVenta);
    gotoxy(3,9);
    printf("Ingrese precio de compra: \n");
    fflush(stdin);
    gotoxy(3,10);
    scanf("%f", &nuevo.precioCosto);
    fflush(stdin);
    gotoxy(3,11);
    printf("Ingrese la cantidad de stock: \n");
    gotoxy(3,12);
    scanf("%i", &nuevo.cantidad);
    gotoxy(3,13);
    nuevo.flagStock = 0;
    mostrarProductoCargado(nuevo);

    return nuevo;
}

void agregarProductoAdmin()
{
    FILE *buffer = fopen("Stock.dat", "ab");
    producto Aux;
    char respuestaC;

    printf("Desea agregar un producto a la lista?(s/n) ");
//    fflush(stdin);
//    scanf("%c", &respuestaC);

    int respuesta;

//    if(respuestaC == 's' || respuestaC == 'S')
//    {
//        respuesta = 1;
//    }
//
//    if(respuestaC == 'n' || respuestaC == 'N')
//    {
//        respuesta = 2;
//    }

    gotoxy(3,8);
    respuesta = seleccionarSiNoMenuProducto(1);
    //respuesta = seleccionarSiNo(1);

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
    centrarTexto("E-COMMERCE - AGREGAR PRODUCTOS",2);
    gotoxy(70,2);
    gotoxy(3,5);
    dibujarCuadro(1,19,78,23); //SE DIBUJA EL CUADRO MENSAJE DE CONSOLA
    gotoxy(9,21);
    printf("Cancelando operacion ...");

}

void borrarPantallaLargo()
{
    gotoxy(3,5);
    printf("                                                                          ");
    gotoxy(3,6);
    printf("                                                                          ");
    gotoxy(3,7);
    printf("                                                                          ");
    gotoxy(3,8);
    printf("                                                                          ");
    gotoxy(3,9);
    printf("                                                                          ");
    gotoxy(3,10);
    printf("                                                                         ");
    gotoxy(3,11);
    printf("                                                                         ");
    gotoxy(3,12);
    printf("                                                                         ");
    gotoxy(3,13);
    printf("                                                                         ");
    gotoxy(3,14);
    printf("                                                                         ");
    gotoxy(3,15);
    printf("                                                                         ");
    gotoxy(3,16);
    printf("                                                                         ");
    gotoxy(3,17);
    printf("                                                                         ");
    gotoxy(1,18);
    printf("                                                                              ");
    gotoxy(1,19);
    printf("                                                                              ");
    gotoxy(1,20);
    printf("                                                                              ");
    gotoxy(3,21);
    printf("                                                                         ");
    gotoxy(3,22);
    printf("                                                                         ");
}

void borrarPantallaCorto()
{
    gotoxy(3,5);
    printf("                                                                          ");
    gotoxy(3,6);
    printf("                                                                          ");
    gotoxy(3,7);
    printf("                                                                          ");
    gotoxy(3,8);
    printf("                                                                          ");
    gotoxy(3,9);
    printf("                                                                          ");
    gotoxy(3,10);
    printf("                                                                         ");
    gotoxy(3,11);
    printf("                                                                         ");
    gotoxy(3,12);
    printf("                                                                         ");
    gotoxy(3,13);
    printf("                                                                         ");
    gotoxy(3,14);
    printf("                                                                         ");
    gotoxy(3,15);
    printf("                                                                         ");
    /////
    gotoxy(3,16);
    printf("                                                                         ");
    gotoxy(3,17);
    printf("                                                                         ");
    gotoxy(1,18);
    printf("                                                                              ");
    gotoxy(1,19);
    printf("                                                                              ");
    gotoxy(1,20);
    printf("                                                                              ");

}

void mostrarProductoCargado(producto nuevo)
{
    gotoxy(3,5);
    borrarPantallaCorto();
    gotoxy(3,5);
    printf("PRODUCTO NUEVO\n");
    gotoxy(3,6);
    printf("Producto: %s\n",nuevo.nombre);
//    gotoxy(3,7);printf("Categoria: %s \n",nuevo.categoria);
    gotoxy(3,8);
    printf("Descripcion: %s \n",nuevo.descripcion);
    gotoxy(3,9);
    printf("Precio de venta: %c%.2f \n",36,nuevo.precioVenta);
    gotoxy(3,10);
    printf("Precio de compra: %c%.2f \n",36,nuevo.precioCosto);
    gotoxy(3,11);
    printf("Cantidad de stock: %i \n",nuevo.cantidad);
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
    gotoxy(7,21);
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

/// FUNCIONES MODIFICAR UN PRODUCTO

void formatoHojaModificar()
{
    dibujarCuadro(0,0,79,24); //SE DIBUJA EL CUADRO PRINCIPAL
    dibujarCuadro(1,1,78,3); //SE DIBUJA EL CUADRO DEL TITULO
    dibujarCuadro(0,0,79,24); //SE DIBUJA EL CUADRO PRINCIPAL
    dibujarCuadro(1,1,78,3); //SE DIBUJA EL CUADRO DEL TITULO

    centrarTexto("E-COMMERCE - MODIFICAR PRODUCTOS",2);
    dibujarCuadro(1,19,78,23); //SE DIBUJA EL CUADRO MENSAJE DE CONSOLA
    gotoxy(27,21);
    centrarTexto("Mensaje de consola ...", 21);
}

void formatoHojaModificarSinCuadroInferior()
{
    dibujarCuadro(0,0,79,24); //SE DIBUJA EL CUADRO PRINCIPAL
    dibujarCuadro(1,1,78,3); //SE DIBUJA EL CUADRO DEL TITULO
    dibujarCuadro(0,0,79,24); //SE DIBUJA EL CUADRO PRINCIPAL
    dibujarCuadro(1,1,78,3); //SE DIBUJA EL CUADRO DEL TITULO

    centrarTexto("E-COMMERCE - MODIFICAR PRODUCTOS",2);
}

void modificarUnProducto()
{
    system("cls");
    formatoHojaModificarSinCuadroInferior();
    gotoxy(3,5);
    printf("Desea modificar un producto?\n");
    int respuesta;
    int opcion;
    respuesta = seleccionarSiNo(1); // 1 PREGUNTO SI DESEA MODIFICAR EL PRODUCTO.
    system("cls");
    char nombreProducto[20];
    char campoAModificar[20];
    producto aux;
    int flag = 0;

    FILE *buffer = fopen("Stock.dat", "r+b");

    if ((buffer != NULL) && (respuesta == 1))
    {
        gotoxy(3,5);
        borrarPantallaCorto();
        formatoHojaModificarSinCuadroInferior();
        gotoxy(3,5);
        ingresarNombreProducto(nombreProducto);

//        printf("\nPRODUCTO A MODIFICAR:%s\n",nombreProducto);

        while ((fread(&aux, sizeof(producto), 1, buffer) > 0) && flag == 0) //4 LEO EL ARCHIVO
        {
            if (strcmpi(aux.nombre, nombreProducto) == 0) // Y BUSCO EL PRODUCTO A MODIFICAR
            {
                system("cls");
                formatoHojaModificar();
                gotoxy(3,5);
                mostrarProductoEncontrado(aux);
                system("cls");
                formatoHojaModificar();
                gotoxy(3,5);
                mostrarCampos();

                do
                {
                    gotoxy(7,14);
                    printf("                                                    ");
                    gotoxy(7,14);
                    printf("Ingrese una opcion por favor: ");
                    fflush(stdin);
                    scanf("%i",&opcion);
                    switch(opcion)
                    {
                    case 1:
                        strcpy(campoAModificar,"nombre");
                        break;
                    case 2:
                        strcpy(campoAModificar,"nombreCategoria");
                        break;
                    case 3:
                        strcpy(campoAModificar,"nroCategoria");
                        break;
                    case 4:
                        strcpy(campoAModificar,"descripcion");
                        break;
                    case 5:
                        strcpy(campoAModificar,"precioVenta");
                        break;
                    case 6:
                        strcpy(campoAModificar,"precioCosto");
                        break;
                    case 7:
                        strcpy(campoAModificar,"cantidad");
                        break;
                    default:
                        printf("Seleciona una opcion valida!");
                        break;
                    }

                }
                while(opcion > 7 || opcion < 1);

                gotoxy(3,5);
                borrarPantallaLargo();

                aux = modificarCampoProducto(aux,campoAModificar);
                fseek(buffer, sizeof(producto) * (-1), SEEK_CUR);
                fwrite(&aux, sizeof(producto), 1, buffer);// 5 SOBRE ESCRIBO EL PRODUCTO DEL ARCHIVO
                fclose(buffer);
                gotoxy(3,5);
                system("cls");
                formatoHojaModificar();
                gotoxy(30,5);
                printf("Producto modificado!");
                sleep(3);
                gotoxy(3,5);
                system("cls");
                formatoHojaModificar();
                mostrarProductoActualizado(aux);// 6 MUESTRO EL PRODUCTO MODIFICADO
                //gotoxy(3,16);system("pause");
                flag = 1;
            }

        }
        if(flag != 1)
        {
            system("cls");
            formatoHojaModificar();
            gotoxy(3,15);
            printf("No se encontro el producto");
            gotoxy(3,16);
            system("pause");
            gotoxy(3,15);
            system("cls");
            return modificarUnProducto();
        }
    }
    else
    {
        if(buffer == NULL)
        {
            printf("\nNo se pudo abrir el archivo\n");
            return 0;
        }
    }
}

producto modificarCampoProducto(producto aModificar, char modificarCampo[])
{
    gotoxy(3,5);
    borrarPantallaLargo();
    formatoHojaModificarSinCuadroInferior();
    producto aux = aModificar;
    int respuesta = 0;

    if(strcmpi("nombre",modificarCampo) == 0)
    {
        system("cls");
        formatoHojaModificarSinCuadroInferior();
        gotoxy(3,5);
        printf("Desea modificar el nombre del producto?\n");
        respuesta = seleccionarSiNo(1);
        if(respuesta == 1)
        {
            gotoxy(3,5);
            borrarPantallaLargo();
            gotoxy(3,5);
            formatoHojaModificar();
            gotoxy(3,5);
            printf("Ingrese el nuevo nombre del producto\n");
            fflush(stdin);
            gotoxy(3,6);
            gets(aux.nombre);
        }
    }

    if(strcmpi("nombreCategoria",modificarCampo) == 0)
    {
        system("cls");
        formatoHojaModificarSinCuadroInferior();
        gotoxy(3,5);
        printf("Desea modificar la categoria del producto?\n");
        respuesta = seleccionarSiNo(1);
        if(respuesta == 1)
        {
            gotoxy(3,5);
            borrarPantallaLargo();
            gotoxy(3,5);
            formatoHojaModificar();
            gotoxy(3,5);
            printf("Modifique la categoria\n");
            fflush(stdin);
            gotoxy(3,6);
            gets(aux.nombreCategoria);
        }
    }

    if(strcmpi("nroCategoria",modificarCampo) == 0)
    {
        system("cls");
        formatoHojaModificarSinCuadroInferior();
        gotoxy(3,5);
        printf("Desea modificar el numero de la categoria del producto?\n");
        respuesta = seleccionarSiNo(1);
        if(respuesta == 1)
        {
            gotoxy(3,5);
            borrarPantallaLargo();
            gotoxy(3,5);
            formatoHojaModificar();
            gotoxy(3,5);
            showCategoriasAdmin();
            gotoxy(3,12);
            printf("Modifique el numero de la categoria\n");
            fflush(stdin);
            gotoxy(3,13);
            gets(aux.nroCategoria);
        }
    }

    if(strcmpi("descripcion",modificarCampo) == 0)
    {
        system("cls");
        formatoHojaModificarSinCuadroInferior();
        gotoxy(3,5);
        printf("Desea modificar la descripcion del producto?\n");
        respuesta = seleccionarSiNo(1);
        if(respuesta == 1)
        {
            gotoxy(3,5);
            borrarPantallaLargo();
            gotoxy(3,5);
            formatoHojaModificar();
            gotoxy(3,5);
            printf("Modifique la descripcion (max 280 caracteres)\n");
            fflush(stdin);
            gotoxy(3,6);
            gets(aux.descripcion);
        }
    }

    if(strcmpi("precioVenta",modificarCampo) == 0)
    {
        system("cls");
        formatoHojaModificarSinCuadroInferior();
        gotoxy(3,5);
        printf("Desea modificar el precio venta del producto?\n");
        respuesta = seleccionarSiNo(1);
        if(respuesta == 1)
        {
            gotoxy(3,5);
            borrarPantallaLargo();
            gotoxy(3,5);
            formatoHojaModificar();
            gotoxy(3,5);
            printf("Modifique el precio de venta\n");
            fflush(stdin);
            gotoxy(3,6);
            scanf("%f", &aux.precioVenta);
        }
    }

    if(strcmpi("precioCosto",modificarCampo) == 0)
    {
        system("cls");
        formatoHojaModificarSinCuadroInferior();
        gotoxy(3,5);
        printf("Desea modificar el costo del producto?\n");
        respuesta = seleccionarSiNo(1);
        if(respuesta == 1)
        {
            gotoxy(3,5);
            borrarPantallaLargo();
            gotoxy(3,5);
            formatoHojaModificar();
            gotoxy(3,5);
            printf("Modifique el costo del producto\n");
            fflush(stdin);
            gotoxy(3,6);
            scanf("%f", &aux.precioCosto);
        }
    }

    if(strcmpi("cantidad",modificarCampo) >= 0)
    {
        system("cls");
        formatoHojaModificarSinCuadroInferior();
        gotoxy(3,5);
        printf("Desea modificar el stock del producto?\n");
        respuesta = seleccionarSiNo(1);
        if(respuesta == 1)
        {
            gotoxy(3,5);
            borrarPantallaLargo();
            gotoxy(3,5);
            formatoHojaModificar();
            gotoxy(3,5);
            printf("Modifique el stock del producto\n");
            gotoxy(3,6);
            scanf("%i", &aux.cantidad);
        }
        if(aux.cantidad == 0)
        {
            aux.flagStock = 1;
        }
    }

    if((modificarCampo != "nombre") && (modificarCampo != "nombrecategoria") && (modificarCampo != "descripcion") && (modificarCampo != "precioVenta") && (modificarCampo != "precioCosto") && (modificarCampo != "cantidad")&& (modificarCampo != "nrocategoria"))
    {
        gotoxy(3,15);
        printf("\nNo se encontro tal campo\n");
    }

    return aux;
}

char ingresarCampo(char busqueda[])
{
    formatoHojaModificar();
    gotoxy(3,15);
    printf("Ingrese campo a modificar\n");
    gotoxy(3,16);
    gets(busqueda);

    return busqueda;
}

char ingresarNombreProducto(char nombreProducto[])
{
    formatoHojaModificar();
    gotoxy(3,5);
    printf("Ingrese el nombre del producto a modificar: ");
    fflush(stdin);
    gets(nombreProducto);

    return nombreProducto;
}

void mostrarProductoActualizado(producto nuevo)
{
    gotoxy(30,5);
    printf("PRODUCTO ACTUALIZADO       ");
    gotoxy(3,8);
    printf("Producto: %s",nuevo.nombre);
    gotoxy(3,9);
    printf("Nombre categoria: %s ",nuevo.nombreCategoria);
    gotoxy(3,10);
    printf("Descripcion: %s ",nuevo.descripcion);
    gotoxy(3,11);
    printf("Precio de venta: %c%.2f ",36,nuevo.precioVenta);
    gotoxy(3,12);
    printf("Precio de costo: %c%.2f ",36,nuevo.precioCosto);
    gotoxy(3,13);
    printf("Numero de categoria: %i ",nuevo.nroCategoria);
    gotoxy(3,14);
    printf("Cantidad de stock: %i ",nuevo.cantidad);
    sleep(5);
}

void mostrarProductoEncontrado(producto nuevo)
{
    gotoxy(30,5);
    printf("PRODUCTO ENCONTRADO       ");
    gotoxy(3,7);
    printf("Producto: %s",nuevo.nombre);
    gotoxy(3,8);
    printf("Nombre categoria: %s ",nuevo.nombreCategoria);
    gotoxy(3,9);
    printf("Descripcion: %s ",nuevo.descripcion);
    gotoxy(3,10);
    printf("Precio de venta: %c%.2f ",36,nuevo.precioVenta);
    gotoxy(3,11);
    printf("Precio de costo: %c%.2f ",36,nuevo.precioCosto);
    gotoxy(3,12);
    printf("Numero de categoria: %i ",nuevo.nroCategoria);
    gotoxy(3,13);
    printf("Cantidad de stock: %i",nuevo.cantidad);
    sleep(5);
}

void mostrarCampos()
{
    gotoxy(7,5);
    printf("CAMPOS DE PRODUCTO:");
    gotoxy(7,6);
    printf("1-Nombre del Producto");
    gotoxy(7,7);
    printf("2-Nombre de la Categoria");
    gotoxy(7,8);
    printf("3-Numero de categoria");
    gotoxy(7,9);
    printf("4-Descripcion del producto");
    gotoxy(7,10);
    printf("5-Precio de venta");
    gotoxy(7,11);
    printf("6-Precio de costo");
    gotoxy(7,12);
    printf("7-Cambiar stock disponible");
}

