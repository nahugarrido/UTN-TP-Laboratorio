#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define KEY_UP 72 +256
#define KEY_DOWN 80 +256
#define KEY_ENTER 13
#define KEY_ESC 27
#include "sistema.h"
#include "UserLibs.h"
#include "loginAlgoritmo.h"
#define ArchivoUsuarios "ArchivoUsuario.dat"

int login(int cursor) /// cursor es donde esta parado el >>>> , opcion es la tecla que introduce el usuario
{
    system("cls");
    ocultarCursor();

    opciones arreglo[] = {"Usuario:", "password:"};
    int cantidadOpciones = 2;

    dibujarCuadro(0,0,79,24); //SE DIBUJA EL CUADRO PRINCIPAL
    dibujarCuadro(1,1,78,3); //SE DIBUJA EL CUADRO DEL TITULO
    gotoxy(33,2);

    centrarTexto("E-COMMERCE",2);

    /// MUESTRA LAS OPCIONES
    centrarTexto("INICIAR SESION",7);
    mostrarOpcionesLogin(cantidadOpciones,arreglo,cursor);
    dibujarCuadro(22,5,55,16); //SE DIBUJA EL CUADRO DEL LOGIN

    /// OBTENER DATOS
    char arrUsuario[30];
    char password[30];
    int id = -1;
    gotoxy(36,10);
    fflush(stdin);
    gets(&arrUsuario);
    gotoxy(37,12);
    fflush(stdin);


    /// ANIMACION PASSWORD
    animacionPassword(&password);

    id = verificacionLogin(arrUsuario, password);

//    /// TESTEO
//    printf("\nID: %i", id);
//    system("pause");


    /// ANIMACION CARGA
    animacionCarga();

    /// VERIFICACION DE USUARIO
    if(id != -1) /// revisar si == o >=
    {
        centrarTexto("Login Exitoso!\n",20);
        gotoxy(23,21);
        system("pause");
        return id;
        /// return id del usuario
    }
    else
    {
        centrarTexto("Usuario o password no valido!\n",20);
        gotoxy(23,21);
        system("pause");
        return login(cursor);
    }
}


/// MOSTRAR OPCIONES LOGIN
void mostrarOpcionesLogin(int cantidadOpciones,opciones arreglo[], int cursor)
{
    int contador;

    for(int i = 0; i < cantidadOpciones; i++)
    {
        contador = 10 + i*2;

        gotoxy(20,contador);

        if(i+1 == cursor)
        {
            printf("       ");
        }
        else
        {
            printf("       ");
        }

        printf("%s\n", arreglo[i]);
    }
}

/// BARRA PROGRESO
void animacionCarga()
{
    centrarTexto("CARGANDO ...",20);

    for(int i = 3; i <= 76; i++)
    {
        gotoxy(i,23);
        printf("%c",177);
    }

    for(int i = 3; i <= 76; i++)
    {
        gotoxy(i,23);
        printf("%c",219);
        Sleep(3);
    }
}

/// ANIMACION PASSWORD
void animacionPassword(char* password[])
{
    char password2[30];
    char caracter;
    int i=0;

    while(caracter = getch())
    {
        if(caracter == KEY_ENTER)
        {
            strcpy(password,password2);
            break;
        }
        else if(caracter == 8)
        {
            if(i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            printf("*");
            password2[i] = caracter;
            i++;
        }
    }
}


int verificacionLogin(char usuario[], char password[])
{
    int id = 0;
    nodoArbolUsuario* arbol;
    arbol = inicArbol();
    arbol = leerArchivo(arbol);

    id = buscarPorUsuario(arbol,usuario, password);
    return id;
}

int buscarPorUsuario(nodoArbolUsuario* arbol, char usuario[], char password[])
{

    int respuesta = -1;
    if(arbol != NULL)
    {
        if((strcmpi(arbol->dato.username, usuario) == 0) && (strcmpi(arbol->dato.password, password) == 0))
        {
                respuesta = arbol->dato.idCliente;
        }
        else
        {
            respuesta = buscarPorUsuario(arbol->izq, usuario, password);

            if(respuesta == -1)
            {
                respuesta = buscarPorUsuario(arbol->der, usuario, password);
            }

        }
    }

    return respuesta;
}

int buscarPorIdUsuario(nodoArbolUsuario* arbol, int id)
{
    int respuesta = -1;
    if(arbol != NULL)
    {
        if(arbol->dato.idCliente == id)
        {
            respuesta = arbol->dato.admin;
        }
        else
        {
            respuesta = buscarPorIdUsuario(arbol->izq, id);

            if(respuesta == -1)
            {
                respuesta = buscarPorIdUsuario(arbol->der, id);
            }

        }
    }

    return respuesta;
}


void inOrderMostrar(nodoArbolUsuario* arbol)
{
    if(arbol == NULL)
    {
        printf("\nARBOL VACIO");
    }

    if(arbol != NULL)
    {
        inOrderMostrar(arbol->izq);
        mostrarnodoArbolUsuario(arbol);
        inOrderMostrar(arbol->der);
    }
}

void mostrarnodoArbolUsuario(nodoArbolUsuario* arbol)
{
    printf("usuario: %s password: %s \n", arbol->dato.username, arbol->dato.password);
}

nodoArbolUsuario* leerArchivo(nodoArbolUsuario* arbol)
{
    FILE* ptr = fopen(ArchivoUsuarios,"rb");
    usuario aux;
    if(ptr != NULL)
    {
        while(fread(&aux,sizeof(usuario),1,ptr) > 0)
        {
            arbol = insertar(arbol,aux);
        }
        fclose(ptr);
    }
    return arbol;
}

nodoArbolUsuario* inicArbol()
{
    return NULL;
}

nodoArbolUsuario* crearnodoArbolUsuario(usuario dato)
{
    nodoArbolUsuario* aux = (nodoArbolUsuario*) malloc(sizeof(nodoArbolUsuario));
    aux->dato = dato;
    aux->der= NULL;
    aux->izq = NULL;

    return aux;
}

nodoArbolUsuario* insertar(nodoArbolUsuario* arbol, usuario dato)
{
    if(arbol == NULL)
    {
        arbol = crearnodoArbolUsuario(dato);
    }
    else
    {
        if(dato.idCliente > arbol->dato.idCliente)
        {
            arbol->der = insertar(arbol->der, dato);
        }
        else
        {
            arbol->izq = insertar(arbol->izq, dato);
        }
    }
    return arbol;
}

