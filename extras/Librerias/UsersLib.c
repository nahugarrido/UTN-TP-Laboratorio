#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include "UsersLib.h"
#define ARCHIVOUSUARIOS "ARCHIVOUSUARIOS.DAT"

void AltaUsuario()
{
    FILE *buffer = fopen(ARCHIVOUSUARIOS, "ab");
    char control = 's';
    usuario Aux;
    char User[30];

    if (buffer != NULL)
    {
        int flag = 0;

        do
        {
            printf("\nIngrese Nombre de usuario: ");
            fflush(stdin);
            gets(User);
            if (verificarPorUserName(User) == 0)
            {
                flag = 1;
                Aux = pedirDatos(User);
                Aux.estadoCliente = 1;
                Aux.saldo = 0;
                Aux.admin = 0;
                fwrite(&Aux, sizeof(usuario), 1, buffer);
                printf("\nAlta de cliente exitosa\n");

                fclose(buffer);
            }
            else
            {
                printf("\nEl Cliente ya existe. Intente de nuevo..\n");
            }

        } while (flag == 0);
    }
    else
    {
        printf("\nNo se pudo abrir el archivo.\n");
    }
}

int verificarPorUserName(char User[])
{

    FILE *buffer = fopen(ARCHIVOUSUARIOS, "rb");
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
        return flag;
    }
    else
    {
        printf("No se puede abrir el archivo. \n");
    }
}

usuario pedirDatos(char user[])
{
    usuario temporal;
    strcpy(temporal.username, user);
    printf("Ingrese una contrasenia: \n");
    fflush(stdin);
    gets(temporal.password);
    temporal.idCliente = (contadorRegistros() + 1);
    return temporal;
}

int contadorRegistros()
{
    FILE *buffer = fopen(ARCHIVOUSUARIOS, "rb");
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
    printf("\nNombre:");
    fflush(stdin);
    puts(A.username);
    printf("\nSaldo: %i  \n", A.saldo);
    printf("\nID Cliente: %i  \n", A.idCliente);
    printf("\n---------------------------------------\n");
}

void showArchive()
{
    FILE *buffer = fopen(ARCHIVOUSUARIOS, "rb");
    usuario Aux;
    if (buffer != NULL)
    {

        while (fread(&Aux, sizeof(usuario), 1, buffer) > 0)
        {
            if (Aux.admin == 0)
            {
                mostrarCliente(Aux);
            }
        }
        fclose(buffer);
    }
    else
    {
        printf("\nNo se puede abrir el archivo.\n");
    }
}

void AltaAdmin()
{
    FILE *buffer = fopen(ARCHIVOUSUARIOS, "ab");
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

void BajaCliente(char nombreUsuario[])
{
    FILE *buffer = fopen(ARCHIVOUSUARIOS, "r+b");
    char control = 's';
    usuario Aux;
    usuario aux2;
    int flag = 0;

    if (verificarPorUserName(nombreUsuario) == 1)
    {
        Aux = BuscarUnClientePorUserName(nombreUsuario);
        MostrarCliente(Aux);
        printf("\nEsta seguro que desea dar de baja el cliente?: s/n \n");
        fflush(stdin);
        scanf("%c", &control);
        if (control == 's' || control == 'S')
        {

            while (fread(&aux2, sizeof(usuario), 1, buffer) > 0 && flag == 0)
            {
                if (strcmpi(aux2.username, nombreUsuario) == 0)
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
        printf("\nNo se encontro un cliente con el DNI ingresado.\n");
    }
}

usuario BuscarUnClientePorUserName(char nombreUsuario[])
{
    FILE *buffer = fopen(ARCHIVOUSUARIOS, "rb");
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
    FILE *buffer = fopen(ARCHIVOUSUARIOS, "r+b");
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
                MostrarCliente(A);
                flag = 1;
            }
        }
    }
}

usuario modificarDatosCliente(usuario A)
{
    char option;
    printf("\nDatos actuales del cliente:");
    MostrarCliente(A);
    printf("\nDesea modificar el nombre de usuario? s/n: ");
    fflush(stdin);
    scanf("%c", &option);
    if (option == 's')
    {
        printf("\nIngrese nuevo nombre de usuario: ");
        fflush(stdin);
        gets(A.username);
    }
    printf("\nDesea cambiar la contraseña? s/n: ");
    fflush(stdin);
    scanf("%c", &option);
    if (option == 's')
    {
        printf("\nIngrese la nueva contraseña: \n");
        fflush(stdin);
        gets(A.password);
    }

    printf("\nDatos modificados del cliente:\n");
    MostrarCliente(A);

    return A;
}

usuario BuscarUnClientePorID(int IdUsuario)
{
    FILE *buffer = fopen(ARCHIVOUSUARIOS, "rb");
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
    FILE *buffer = fopen(ARCHIVOUSUARIOS, "rb");
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