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

            if (strcmpi(Aux.userName, User) == 0)
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
    strcpy(temporal.userName, user);
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
    puts(A.userName);
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
        gets(Admin.userName);
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
    puts(A.userName);
    printf("\n---------------------------------------\n");
}