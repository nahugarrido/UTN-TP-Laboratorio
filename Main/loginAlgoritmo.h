#pragma once
/// ACA VAN LAS ESTRUCTURAS Y PROTOTIPADOS

/// ESTRUCTURAS LOGIN ALGORTIMO
typedef struct
{
    usuario dato;
    struct nodoArbolUsuario* izq;
    struct nodoArbolUsuario* der;
} nodoArbolUsuario;


/// FUNCIONES
void animacionCarga();
void animacionPassword(char *password[]);
int login(int cursor);
void mostrarOpcionesLogin(int cantidadOpciones,opciones arreglo[], int cursor);
int verificacionLogin(char usuario[], char password[]);
int buscarPorUsuario(nodoArbolUsuario* arbol, char usuario[], char password[]);
int buscarPorIdUsuario(nodoArbolUsuario* arbol, int id);
void inOrderMostrar(nodoArbolUsuario* arbol);
void mostrarnodoArbolUsuario(nodoArbolUsuario* arbol);
nodoArbolUsuario* leerArchivo(nodoArbolUsuario* arbol);
nodoArbolUsuario* inicArbol();
nodoArbolUsuario* crearnodoArbolUsuario(usuario dato);
nodoArbolUsuario* insertar(nodoArbolUsuario* arbol, usuario dato);

