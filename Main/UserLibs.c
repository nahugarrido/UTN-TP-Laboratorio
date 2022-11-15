#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include "carritoCompras.h"
#include "UserLibs.h"
#define archivoUsuarios "ArchivoUsuario.dat"
#define ArchivoUsuarios "ArchivoUsuario.dat"
#define KEY_UP 72 + 256
#define KEY_DOWN 80 + 256
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_LEFT 75 + 256
#define KEY_RIGHT 77 + 256

void AltaUsuario()
{
    FILE *buffer = fopen(archivoUsuarios, "ab");
    usuario Aux;
    char User[30];

    if (buffer != NULL)
    {
        int flag = 0;

        do
        {
            system("cls");

            dibujarCuadro(0, 0, 79, 24); // SE DIBUJA EL CUADRO PRINCIPAL
            dibujarCuadro(1, 1, 78, 3);  // SE DIBUJA EL CUADRO DEL TITULO
            centrarTexto("E-COMMERCE - USUARIOS", 2);

            dibujarCuadro(1, 19, 78, 23); // SE DIBUJA EL CUADRO MENSAJE DE CONSOLA
            gotoxy(7, 21);
            printf("Mensaje de consola ...");

            gotoxy(7,5);
            printf("Ingrese Nombre de usuario: ");
            fflush(stdin);
            gets(User);
            if (verificarPorUserName(User) == 0)
            {
                flag = 1;
                Aux = pedirDatos(User);
                Aux.estadoCliente = 1;
                Aux.saldo = 0;
                Aux.admin = 0;
                Aux.validosCarrito = 0; /// AGREGO LINEAS DE LOS VALIDOS
                Aux.validosCompras = 0;
                gotoxy(7,9);
                printf("Ingrese el saldo: $ ");
                scanf("%f", &Aux.saldo);
                fwrite(&Aux, sizeof(usuario), 1, buffer);
                gotoxy(7, 21);
                printf("Usuario creado con exito!");
                sleep(3);

                fclose(buffer);
            }
            else
            {
                gotoxy(7, 21);
                printf("El Cliente ya existe. Intente de nuevo..");
                sleep(3);
            }
        }
        while (flag == 0);
    }
    else
    {
        printf("\nNo se pudo abrir el archivo.\n");
    }
}

int verificarPorUserName(char User[])
{

    FILE *buffer = fopen(archivoUsuarios, "rb");
    usuario Aux;
    int flag = 0;

    if (buffer != NULL)
    {
        while ((fread(&Aux, sizeof(usuario), 1, buffer) > 0) && flag == 0)
        {

            if (strcmpi(Aux.username, User) == 0)
            {
                flag = 1;
                fclose(buffer);
            }
        }
    }
    else
    {
        printf("No se puede abrir el archivo. \n");
    }

    return flag;
}

usuario pedirDatos(char user[])
{
    usuario temporal;
    strcpy(temporal.username, user);
    gotoxy(7,7);
    printf("Ingrese una contrasenia: ");
    fflush(stdin);
    gets(temporal.password);
    temporal.idCliente = (contadorRegistros() + 1);
    return temporal;
}

int contadorRegistros()
{
    FILE *buffer = fopen(archivoUsuarios, "rb");
    int cant = 0;
    usuario Aux;

    if (buffer != NULL)
    {
        while (fread(&Aux, sizeof(usuario), 1, buffer) > 0)
        {

            if (Aux.admin == 0)
            {
                cant++;
            }
        }
        fclose(buffer);
    }

    return cant;
}

void mostrarCliente(usuario A)
{
    printf("\n---------------------------------------\n");
    printf("\n Usuario:");
    fflush(stdin);
    puts(A.username);
    printf("\n Contrasenia: %s ", A.password);
    printf("\nSaldo: %f  \n", A.saldo);
    printf("\nID Cliente: %i  \n", A.idCliente);
    printf("\n---------------------------------------\n");
}



void showArchiveClientes()
{
    system("cls");
    FILE *buffer = fopen(archivoUsuarios, "rb");
    usuario Aux;
    if (buffer != NULL)
    {

        while (fread(&Aux, sizeof(usuario), 1, buffer) > 0)
        {
            if (Aux.admin == 0 && Aux.estadoCliente == 1)
            {
                mostrarCliente(Aux);
            }
        }
        system("pause");
        fclose(buffer);
    }
    else
    {
        printf("\nNo se puede abrir el archivo.\n");
    }
}

void AltaAdmin()
{
    FILE *buffer = fopen(archivoUsuarios, "ab");
    usuario Aux;

    if (buffer != NULL)
    {
        usuario Admin;
        printf("\nIngrese Nombre del Admin: \n");
        fflush(stdin);
        gets(Admin.username);
        printf("Ingrese una contrasenia: \n");
        fflush(stdin);
        gets(Admin.password);
        Admin.admin = 1;
        Admin.estadoCliente = 0;
        fwrite(&Aux, sizeof(usuario), 1, buffer);
        fclose(buffer);
        mostrarAdmin(Admin);
        printf("\nAlta de Admin Exitosa!\n");
    }
    else
    {
        printf("\nNo se pudo abrir el archivo.\n");
    }
}

void mostrarAdmin(usuario A)
{
    printf("\n---------------------------------------\n");
    printf("\nNombre:");
    fflush(stdin);
    puts(A.username);
    printf("\n---------------------------------------\n");
}

void BajaCliente(usuario A)
{
    FILE *buffer = fopen(archivoUsuarios, "r+b");
    char control = 's';
    usuario Aux;
    usuario aux2;
    int flag = 0;

    if (verificarPorUserName(A.username) == 1)
    {
        Aux = BuscarUnClientePorUserName(A.username);
        printf("\nEsta seguro que desea dar de baja el cliente?: s/n \n");
        fflush(stdin);
        scanf("%c", &control);
        if (control == 's' || control == 'S')
        {

            while (fread(&aux2, sizeof(usuario), 1, buffer) > 0 && flag == 0)
            {
                if (strcmpi(aux2.username, A.username) == 0)
                {
                    if (aux2.estadoCliente == 0)
                    {
                        printf("\nEl cliente ya esta dado de baja.\n");
                    }
                    else
                    {
                        fseek(buffer, sizeof(usuario) * (-1), SEEK_CUR);
                        Aux.estadoCliente = 0;
                        fwrite(&Aux, sizeof(usuario), 1, buffer);
                        fclose(buffer);
                        flag = 1;
                        printf("\nCliente ha sido dado de baja satisfactoriamente.\n");
                    }
                }
            }
        }
    }
    else
    {
        printf("\nHa ingresado un nombre de usuario incorrecto.\n");
    }
}

usuario BuscarUnClientePorUserName(char nombreUsuario[])
{
    FILE *buffer = fopen(archivoUsuarios, "rb");
    usuario Aux;

    int flag = verificarPorUserName(nombreUsuario);

    if (buffer != NULL)
    {
        while ((fread(&Aux, sizeof(usuario), 1, buffer) > 0) && flag == 1)
        {
            if (strcmpi(Aux.username, nombreUsuario) == 0)
            {
                flag = 0;
                fclose(buffer);
            }
        }
    }
    return Aux;
}

void modificarUnCliente(usuario A)
{
    FILE *buffer = fopen(archivoUsuarios, "r+b");
    usuario aux2;
    int flag = 0;

    if (buffer == NULL)
    {
        printf("\nNo se pudo abrir el archivo\n");
    }
    else
    {
        while ((fread(&aux2, sizeof(usuario), 1, buffer) > 0) && flag == 0)
        {
            if (strcmpi(aux2.username, A.username) == 0)
            {
                A = modificarDatosCliente(A);
                fseek(buffer, sizeof(usuario) * (-1), SEEK_CUR);
                fwrite(&A, sizeof(usuario), 1, buffer);
                fclose(buffer);
                printf("\nCliente modificado:\n");
                mostrarCliente(A);
                flag = 1;
            }
        }
    }
}

usuario modificarDatosCliente(usuario A)
{
    char option;
    gotoxy(7,7);
    printf("Datos actuales del cliente:");

    gotoxy(7,9);
    printf("IdCliente: %i", A.idCliente);
    gotoxy(7,11);
    printf("Usuario: %s", A.username);
    gotoxy(7,13);
    printf("Password: %s", A.password);
    gotoxy(7,15);
    printf("Saldo: $%.2f", A.saldo);

    gotoxy(7, 21);
    printf("                                                            ");
    gotoxy(7, 21);
    printf("Desea modificar el nombre de usuario? s/n: ");
    fflush(stdin);
    scanf("%c", &option);
    if (option == 's')
    {
        gotoxy(7, 21);
        printf("                                                            ");
        gotoxy(7, 21);
        printf("Ingrese nuevo nombre de usuario: ");
        fflush(stdin);
        gets(A.username);
    }
    gotoxy(7, 21);
    printf("                                                            ");
    gotoxy(7, 21);
    printf("Desea cambiar la contrasenia? s/n: ");
    fflush(stdin);
    scanf("%c", &option);
    if (option == 's')
    {
        gotoxy(7, 21);
        printf("                                                            ");
        gotoxy(7, 21);
        printf("Ingrese la nueva contrasenia: ");
        fflush(stdin);
        gets(A.password);
    }
    gotoxy(7, 21);
    printf("                                                            ");
    gotoxy(7, 21);
    printf("Cambios realizados con exito!");
    sleep(3);


    return A;
}

usuario BuscarUnClientePorID(int IdUsuario)
{
    FILE *buffer = fopen(archivoUsuarios, "rb");
    usuario Aux;
    int flag = VerificarPorID(IdUsuario);

    while ((fread(&Aux, sizeof(usuario), 1, buffer) > 0) && flag == 1)
    {
        if (Aux.idCliente == IdUsuario)
        {

            flag = 0;
            fclose(buffer);
        }
    }

    return Aux;
}

int VerificarPorID(int IdCliente)
{
    FILE *buffer = fopen(archivoUsuarios, "rb");
    usuario Aux;
    int flag = 0;
    while ((fread(&Aux, sizeof(usuario), 1, buffer) > 0) && flag == 0)
    {
        if (Aux.idCliente == IdCliente)
        {

            flag = 1;
            fclose(buffer);
        }
    }

    return flag;
}

void verInformacionUsuarioID()
{
    system("cls");


    dibujarCuadro(0, 0, 79, 24); // SE DIBUJA EL CUADRO PRINCIPAL
    dibujarCuadro(1, 1, 78, 3);  // SE DIBUJA EL CUADRO DEL TITULO
    centrarTexto("E-COMMERCE - USUARIOS", 2);

    int id;
    dibujarCuadro(1, 19, 78, 23); // SE DIBUJA EL CUADRO MENSAJE DE CONSOLA
    gotoxy(7, 21);
    printf("Mensaje de consola ...");
    gotoxy(7, 5);
    printf("Ingrese el id del usuario que desea buscar: ");
    fflush(stdin);
    scanf("%i", &id);
    int flag;
    flag = VerificarPorID(id);
    if (flag == 1)
    {
        mostrarUnUsuario(id);
    }
    else
    {
        gotoxy(7, 21);
        printf("                                                  ");
        gotoxy(7, 21);
        printf("Debes ingresar un id valido. ");
        sleep(2);
    }
}

void modificarClienteMenu()
{
    char aux[99];
    usuario temporal;
    system("cls");


    dibujarCuadro(0, 0, 79, 24); // SE DIBUJA EL CUADRO PRINCIPAL
    dibujarCuadro(1, 1, 78, 3);  // SE DIBUJA EL CUADRO DEL TITULO
    centrarTexto("E-COMMERCE - USUARIOS", 2);

    gotoxy(7, 21);
    printf("Mensaje de consola ...");
    dibujarCuadro(1, 19, 78, 23); // SE DIBUJA EL CUADRO MENSAJE DE CONSOLA

    gotoxy(7,5);
    printf("Ingrese el nombre de usuario: ");
    fflush(stdin);
    gets(aux);
    int flag = verificarPorUserName(aux);


    if (flag == 1)
    {
        temporal = BuscarUnClientePorUserName(aux);
        modificarUnCliente(temporal);
    }
    else
    {
        gotoxy(7, 21);
        printf("Debes ingresar un usuario valido! \n");
        sleep(3);
    }


}

void modificarEstadoClienteMenu()
{
    char aux[99];
    usuario temporal;
    system("cls");

    dibujarCuadro(0, 0, 79, 24); // SE DIBUJA EL CUADRO PRINCIPAL
    dibujarCuadro(1, 1, 78, 3);  // SE DIBUJA EL CUADRO DEL TITULO
    centrarTexto("E-COMMERCE - USUARIOS", 2);

    gotoxy(7, 21);
    printf("Mensaje de consola ...");
    dibujarCuadro(1, 19, 78, 23); // SE DIBUJA EL CUADRO MENSAJE DE CONSOLA

    gotoxy(7,5);
    printf("Ingrese el nombre de usuario: ");
    fflush(stdin);
    gets(aux);
    int flag = verificarPorUserName(aux);

    if (flag == 1)
    {
        temporal = BuscarUnClientePorUserName(aux);
        modificarEstadoCliente(temporal);

        gotoxy(7, 21);
        printf("                                                            ");
        gotoxy(7, 21);
        printf("Cambios realizados con exito!");
        sleep(3);
    }
    else
    {
        gotoxy(7, 21);
        printf("Debes ingresar un usuario valido! \n");
        sleep(3);
    }
}

void modificarEstadoCliente(usuario A)
{
    FILE *buffer = fopen(archivoUsuarios, "r+b");
    usuario aux2;
    int flag = 0;

    if (buffer == NULL)
    {
        printf("\nNo se pudo abrir el archivo\n");
    }
    else
    {
        while ((fread(&aux2, sizeof(usuario), 1, buffer) > 0) && flag == 0)
        {
            if (strcmpi(aux2.username, A.username) == 0)
            {
                fseek(buffer, sizeof(usuario) * (-1), SEEK_CUR);
                A = modificarEstadoContable(A);
                fwrite(&A, sizeof(usuario), 1, buffer);
                flag = 1;
            }
        }
        fclose(buffer);
    }
}

usuario modificarEstadoContable(usuario A)
{
    char option;
    fflush(stdin);
    gotoxy(7,7);
    printf("Datos actuales del cliente:");
    gotoxy(7,9);
    printf("IdCliente: %i", A.idCliente);
    gotoxy(7,11);
    printf("Usuario: %s", A.username);
    gotoxy(7,13);
    printf("Password: %s", A.password);
    gotoxy(7,15);
    printf("Saldo: $%.2f", A.saldo);

    gotoxy(7, 21);
    printf("                                                            ");
    gotoxy(7, 21);
    printf("Desea modificar el saldo? s/n: ");
    fflush(stdin);
    scanf("%c", &option);
    if (option == 's')
    {
        gotoxy(7, 21);
        printf("                                                            ");
        gotoxy(7, 21);
        printf("Ingrese nuevo saldo: ");
        fflush(stdin);
        scanf("%f", &A.saldo);
    }
    gotoxy(7, 21);
    printf("                                                            ");
    gotoxy(7, 21);
    printf("Desea dar de baja el usuario? s/n: ");
    fflush(stdin);
    scanf("%c", &option);
    if (option == 's')
    {
        BajaCliente(A);
    }

    return A;
}

/// FUNCIONES MENU USUARIO
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int mostrarUsuarios(int id, int cursor) /// cursor es donde esta parado el >>>> , opcion es la tecla que introduce el usuario
{
    system("cls");
    nodoUsuarioD *lista = inicListaDobleusuario();
    lista = despersistirListaDobleusuarios(lista);

    dibujarCuadro(0, 0, 79, 24); // SE DIBUJA EL CUADRO PRINCIPAL
    dibujarCuadro(1, 1, 78, 3);  // SE DIBUJA EL CUADRO DEL TITULO

    centrarTexto("E-COMMERCE - USUARIOS", 2);

    gotoxy(70, 2);
    printf("ID: %i", id);

    /// MUESTRA LAS OPCIONES
    int cantidadOpciones = contarOpcionesusuarios(lista);
    // printf("\ncantidadOpciones: %i", cantidadOpciones);
    // system("pause");

    mostrarOpcionesUsuarios(lista, cursor);

    gotoxy(7, 21);
    printf("Para salir presionar ESC");
    dibujarCuadro(1, 19, 78, 23); // SE DIBUJA EL CUADRO MENSAJE DE CONSOLA
    ocultarCursor();

    int opcion = capturarTecla3();

    gotoxy(0, 0);
    // printf("cursor: %i", cursor); //// PARA VER EL CURSOR  --------------------------------------------------------------------------->
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
        return 0;
    }

    if (opcion == KEY_ENTER)
    {
        int idRetorno = obtenerIdUsuarioList(lista,cursor);
        return idRetorno;
    }

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
        if (cursor - 7 > 0)
        {
            cursor -= 7;
        }
    }

    if (opcion == KEY_RIGHT)
    {
        if (cursor + 7 <= cantidadOpciones)
        {
            cursor += 7;
        }
    }

    return mostrarUsuarios(id, cursor);
}

nodoUsuarioD *despersistirListaDobleusuarios(nodoUsuarioD *lista)
{
    FILE *ptr = fopen(ArchivoUsuarios, "rb");
    usuario aux;
    nodoUsuarioD *aux2;

    if (ptr != NULL)
    {
        while (fread(&aux, sizeof(usuario), 1, ptr) > 0)
        {
            if(aux.estadoCliente == 1)
            {
                aux2 = crearNodoDobleusuario(aux);
                lista = agregarAlFinalDobleusuario(lista, aux2);
            }
        }
        fclose(ptr);
    }
    return lista;
}

nodoUsuarioD *inicListaDobleusuario()
{

    return NULL;
}

nodoUsuarioD *crearNodoDobleusuario(usuario A)
{

    nodoUsuarioD *aux = (nodoUsuarioD*) malloc(sizeof(nodoUsuarioD));

    aux->dato = A;
    aux->siguiente = NULL;
    aux->anterior = NULL;
    return aux;
}

nodoUsuarioD *buscarUltimoDobleusuario(nodoUsuarioD *lista)
{
    nodoUsuarioD *ultimo;

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
            ultimo = buscarUltimoDobleusuario(lista->siguiente);
        }
    }

    return ultimo;
}

nodoUsuarioD *agregarAlFinalDobleusuario(nodoUsuarioD *lista, nodoUsuarioD *nuevoNodo)
{

    if (lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nodoUsuarioD *ultimo = buscarUltimoDobleusuario(lista);
        ultimo->siguiente = nuevoNodo;
        nuevoNodo->anterior = ultimo;
    }

    return lista;
}

int contarOpcionesusuarios(nodoUsuarioD *lista)
{
    int contador = 0;

    if (lista == NULL)
    {
        printf("lista vacia");
    }

    while (lista != NULL)
    {
        contador++;
        lista = lista->siguiente;
    }

    return contador;
}

int obtenerIdUsuarioList(nodoUsuarioD *lista, int cursor)
{
    int contador = 1;
    int id = -1;

    if (lista == NULL)
    {
        printf("lista vacia");
    }

    while (contador < cursor)
    {
        contador++;
        lista = lista->siguiente;
    }

    id = lista->dato.idCliente;

    return id;
}

/// MOSTRAR OPCIONES
void mostrarOpcionesUsuarios(nodoUsuarioD *lista, int cursor)
{
    nodoUsuarioD *anterior;
    int posicionY;
    int posicionX;
    int contPaginas = ceil(((float)cursor / 14));

    int i = 1 + ((contPaginas - 1) * 14);

    int cantidadxColumna = 7;

    int cantColumnas = 0;

    /// esto ya deberia funcionar para navegar en el menu en todas las direcciones de no funcionar
    /// hay que revisar en mostrar usuarios los if a ver si deberiamos poner +1 -1 en condiciones = <=

    int tope = i + 13;

    for (int i = 0; i < ((contPaginas - 1) * 14); i++)
    {
        lista = lista->siguiente;
    }

    while ((lista != NULL) && (i <= tope))
    {
        posicionY = 28 + 3 + i * 2;

        if ((i - 1) % 7 == 0 && i != 0)
        {
            cantColumnas++;
        }

        if (cantColumnas % 2 == 0)
        {
            posicionX = 45;
        }

        if (cantColumnas % 2 != 0)
        {
            posicionX = 2;
        }

        if ((cantColumnas % 2 != 0))
        {
            posicionY -= (contPaginas * 28);
        }

        if (cantColumnas % 2 == 0)
        {
            posicionY -= (7 * cantColumnas) + (contPaginas * 28);
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

        printf("%s", lista->dato.username);

        //        gotoxy(0,0);
        //        //printf("cantColumnas: %i i = %i",cantColumnas, i);
        //        printf("posicionY: %i",posicion);
        //        system("pause");

        i++;
        anterior = lista;
        lista = lista->siguiente;
    }
}

int capturarTecla3()
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
    while ((tecla != KEY_UP) && (tecla != KEY_DOWN) && (tecla != KEY_ESC) && (tecla != KEY_ENTER) && (tecla != KEY_LEFT) && (tecla != KEY_RIGHT));

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
    default:
        printf("\nDEFAULT!");
        system("pause");
        break;
    }

    return opcion;
}

void mostrarUnUsuario(int mostrar)
{
    system("cls");
    usuario aux = BuscarUnClientePorID(mostrar);

    dibujarCuadro(0, 0, 79, 24); // SE DIBUJA EL CUADRO PRINCIPAL
    dibujarCuadro(1, 1, 78, 3);  // SE DIBUJA EL CUADRO DEL TITULO
    centrarTexto("E-COMMERCE - USUARIOS", 2);
    gotoxy(70, 2);

    gotoxy(7,5);
    printf("IdCliente: %i", aux.idCliente);
    gotoxy(7,7);
    printf("Usuario: %s", aux.username);
    gotoxy(7,9);
    printf("Password: %s", aux.password);
    gotoxy(7,11);
    printf("Saldo: $%.2f", aux.saldo);


    dibujarCuadro(1, 19, 78, 23); // SE DIBUJA EL CUADRO MENSAJE DE CONSOLA
    gotoxy(7, 21);
    system("pause");
}


void saldoDisponible(int id)
{
    usuario aux = BuscarUnClientePorID(id);
    gotoxy(9, 21);
    printf("                                                     ");
    gotoxy(9, 21);
    printf("Su saldo disponible es de: $%.0f", aux.saldo);
    sleep(3);
}

void mostrarDatosEnvio(int id)
{
    usuario aux = BuscarUnClientePorID(id);

    destino ultimoEnvio = aux.compras[aux.validosCompras-1].despachar;

    if(aux.validosCompras == 0)
    {
        gotoxy(9, 21);
        printf("                                                            ");
        gotoxy(9, 21);
        printf("Todavia no tienes una direccion de envio!");
        sleep(3);
    }
    else
    {
        gotoxy(9, 21);
        printf("                                                            ");
        gotoxy(9, 21);
        printf("%s, %s, %s, %s.", ultimoEnvio.pais, ultimoEnvio.provincia,ultimoEnvio.ciudad, ultimoEnvio.direccion);
        sleep(3);

    }
}

/// FUNCIONES LISTA SIMPLE PARA PILAS subVenta
nodoVentaS* inicLista()
{
    return NULL;
}

nodoVentaS* crear(venta dato)
{
    nodoVentaS* temp = (nodoVentaS*) malloc(sizeof(nodoVentaS));
    temp->dato = dato;
    temp->siguiente = NULL;

    return temp;
}

nodoVentaS* agregarPrincipio(nodoVentaS* lista, nodoVentaS* nuevonodoVentaS)
{

    if(lista == NULL)
    {
        lista = nuevonodoVentaS;
    }
    else
    {
        nuevonodoVentaS->siguiente = lista;
        lista = nuevonodoVentaS;
    }

    return lista;
}

nodoVentaS * buscarUltimo(nodoVentaS * lista)
{
    nodoVentaS * seg = lista;
    if(seg != NULL)
        while(seg->siguiente != NULL)
        {
            seg = seg->siguiente;
        }
    return seg;
}

nodoVentaS * agregar(nodoVentaS * lista, nodoVentaS * nuevonodoVentaS)
{
    if(lista == NULL)
    {
        lista = nuevonodoVentaS;
    }
    else
    {
        nodoVentaS * ultimo = buscarUltimo(lista);
        ultimo->siguiente = nuevonodoVentaS;
    }
    return lista;
}

void mostrarLista(nodoVentaS* lista)
{
    while(lista->siguiente != NULL)
    {
        printf("ID VENTA: [%i]  ", lista->dato.idVenta);
        lista = lista->siguiente;
    }

    if(lista->siguiente == NULL)
    {
        printf("[%i]  ", lista->dato.idVenta);
        printf("END");
    }

}

/// PILAS
void inicPila(Pila *p)
{
    p->lista = inicLista();
}

void apilar(Pila* p,venta dato)
{
    nodoVentaS* nuevo = crear(dato);

    p->lista = agregarPrincipio(p->lista,nuevo);
}

venta desapilar(Pila *p)
{
    nodoVentaS* anterior =  p->lista;
    p->lista = p->lista->siguiente;

    return anterior->dato;
}

venta tope(Pila *p)
{
    return p->lista->dato;
}

int pilavacia(Pila *p)
{
    return p->lista == NULL;
}

void mostrar(Pila *p)
{
    printf("\n----------------------------------------------------------------------------\n\n");
    mostrarLista(p->lista);
    printf("\n\n----------------------------------------------------------------------------\n");
}



/// FUNCIONES LISTAS DOBLES VENTA
nodoVentaD *inicListaDobleVenta()
{

    return NULL;
}

nodoVentaD *crearNodoDobleVenta(venta A)
{

    nodoVentaD *aux = (nodoVentaD *)malloc(sizeof(nodoVentaD));

    aux->dato = A;

    aux->siguiente = NULL;
    aux->anterior = NULL;

    return aux;
}

nodoVentaD *buscarUltimoDobleVenta(nodoVentaD *lista)
{
    nodoVentaD *ultimo;

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
            ultimo = buscarUltimoDobleVenta(lista->siguiente);
        }
    }

    return ultimo;
}

nodoVentaD *agregarAlFinalDobleVenta(nodoVentaD *lista, nodoVentaD *nuevoNodo)
{

    if (lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nodoVentaD *ultimo = buscarUltimoDobleVenta(lista);
        ultimo->siguiente = nuevoNodo;
        nuevoNodo->anterior = ultimo;
    }

    return lista;
}

int contarOpcionesVentas(nodoVentaD *lista)
{
    int contador = 0;

    if (lista == NULL)
    {
        printf("lista vacia");
    }

    while (lista != NULL)
    {
        contador++;
        lista = lista->siguiente;
    }

    return contador;
}

/// MOSTRAR HISTORIAL DE VENTAS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int historialComprasId(int id, int cursor) /// cursor es donde esta parado el >>>> , opcion es la tecla que introduce el usuario
{

    system("cls");
    usuario aux = BuscarUnClientePorID(id);
    Pila PILITA;
    inicPila(&PILITA);
    venta aux3;

    for(int i = 0; i < aux.validosCompras; i++)
    {
        apilar(&PILITA,aux.compras[i]);
    }

    nodoVentaD *lista = inicListaDobleVenta();

    while(!pilavacia(&PILITA))
    {
        aux3 = desapilar(&PILITA);
        nodoVentaD* aux2 = crearNodoDobleVenta(aux3);
        lista = agregarAlFinalDobleVenta(lista,aux2);
    }


    dibujarCuadro(0, 0, 79, 24); // SE DIBUJA EL CUADRO PRINCIPAL
    dibujarCuadro(1, 1, 78, 3);  // SE DIBUJA EL CUADRO DEL TITULO

    centrarTexto("E-COMMERCE - HISTORIAL DE COMPRAS", 2);

    gotoxy(70, 2);
    printf("ID: %i", id);

    /// TABLA HEADERS DE E-COMMERCE STOCK
    gotoxy(9,5);
    printf("ID VENTA");
    gotoxy(27,5);
    printf("TOTAL");
    gotoxy(41,5);
    printf("DIRECCION ENVIO");
    gotoxy(60,5);
    printf("ESTADO ENVIO");

    /// MUESTRA LAS OPCIONES
    gotoxy(9,7);
    int cantidadOpciones = contarOpcionesVentas(lista);
    // printf("\ncantidadOpciones: %i", cantidadOpciones);
    // system("pause");

    mostrarOpcionesVenta(lista, cursor);

    gotoxy(7, 21);
    printf("Para salir presionar ESC");
    dibujarCuadro(1, 19, 78, 23); // SE DIBUJA EL CUADRO MENSAJE DE CONSOLA
    ocultarCursor();

    int opcion = capturarTecla2();

    gotoxy(0, 0);
    // printf("cursor: %i", cursor); //// PARA VER EL CURSOR  --------------------------------------------------------------------------->
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
        return 0;
    }

    if (opcion == KEY_ENTER)
    {
        return 0;
    }

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

    return historialComprasId(id, cursor);
}

void mostrarOpcionesVenta(nodoVentaD *lista, int cursor)
{
    nodoVentaD *anterior;
    int posicionY;
    int posicionX;
    int contPaginas = ceil(((float)cursor/6));

    int i=  1 + ((contPaginas-1)*6);

    int cantidadxColumna = 6;

    int cantColumnas = 0;

    /// esto ya deberia funcionar para navegar en el menu en todas las direcciones de no funcionar
    /// hay que revisar en mostrar productos los if a ver si deberiamos poner +1 -1 en condiciones = <=

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

        printf("%-21i %-15i %-15.0f %.0f", lista->dato.idVenta, lista->dato.estadoEnvio, lista->dato.total, lista->dato.despachar.direccion);

        //        gotoxy(0,0);
        //        //printf("cantColumnas: %i i = %i",cantColumnas, i);
        //        printf("posicionY: %i",posicion);
        //        system("pause");

        i++;
        anterior = lista;
        lista = lista->siguiente;
    }
}

