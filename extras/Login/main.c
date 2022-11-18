#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define KEY_UP 72 +256
#define KEY_DOWN 80 +256
#define KEY_ENTER 13
#define KEY_ESC 27

/// ESTRUCTURAS
typedef struct
{
    char nombre[50];
} opciones; // OPCIONES DEL MENU

/// PROTOTIPOS DE LAS FUNCIONES
void dibujarCuadro(int x1,int y1,int x2,int y2);
void gotoxy(int x,int y);
void desactivarMaximizar();
int login(int cursor);
int capturarTecla();
void ocultarCursor();
void suma();

//FUNCION PRINCIPAL MAIN
int main()
{

    /// ESTILO DE MENU (GENERICO PARA TODOS LOS MENUS)
    desactivarMaximizar();
    system("mode con: cols=80 lines=25"); //SE DEFINE LAS DIMENSIONES DE LA VENTANA DEL PROGRAMA A 80 COLUMNAS Y 25 FILAS
    system("COLOR 0A"); //SE DA UN COLOR DE FONDO Y COLOR A LAS LETRAS /// E0 // 5F // B0

    int opcion = login(1);

    printf("opcion: %i", opcion);

    /// PAUSAR EJECUCION
    printf("\n");
    gotoxy(40,40);
    system("cls");

    return 0;
}

/// PASAR A LIBRERIA
int login(int cursor) /// cursor es donde esta parado el >>>> , opcion es la tecla que introduce el usuario
{
    system("cls");

    /// ACA DATOS A CAMBIAR CUANDO TENGAMOS EL ARCHIVO DE USUARIOS <-------------------------------------------
    char TEST1[30] = "admin";
    char TEST2[30] = "admin";

    opciones arreglo[] = {"Usuario:", "password:"};
    int cantidadOpciones = 2;

    dibujarCuadro(0,0,79,24); //SE DIBUJA EL CUADRO PRINCIPAL
    dibujarCuadro(1,1,78,3); //SE DIBUJA EL CUADRO DEL TITULO
    gotoxy(33,2);

    centrarTexto("E-COMMERCE",2);

    /// MUESTRA LAS OPCIONES
    centrarTexto("INICIAR SESION",7);
    mostrarOpciones(cantidadOpciones,arreglo,cursor);
    dibujarCuadro(22,5,55,16); //SE DIBUJA EL CUADRO DEL LOGIN

    /// OBTENER DATOS
    char arrUsuario[30];
    char password[30];
    int id = 1;

    gotoxy(36,10);
    gets(&arrUsuario);
    gotoxy(37,12);
    fflush(stdin);

    /// ANIMACION PASSWORD
    animacionPassword(&password);
    ocultarCursor();

    /// ANIMACION CARGA
    animacionCarga();

    /// VERIFICACION DE USUARIO
    if(strcmp(TEST1,arrUsuario) >= 0 && strcmp(password,TEST2) >= 0) /// revisar si == o >=
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

/// CENTRAR TEXTO
void centrarTexto(char *texto, int y)
{
    int longitud = strlen(texto); // mitad de ancho de pantalla - longitud de texto / 2
    gotoxy(40-(longitud/2),y);
    printf(texto);
}

/// BARRA PROGRESO
void animacionCarga()
{
    centrarTexto("CARGANDO ...",20);

    int i = 0;

    for(i = 3; i <= 76; i++)
    {
        gotoxy(i,23);
        printf("%c",177);
    }

    for(i = 3; i <= 76; i++)
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
            password2[i] = '\n';
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




/// MOSTRAR OPCIONES
void mostrarOpciones(int cantidadOpciones,opciones arreglo[], int cursor)
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
    while((tecla != KEY_UP) && (tecla != KEY_DOWN) && (tecla != KEY_ESC) && (tecla != KEY_ENTER));


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

/// ESTAS 2 PARA CUANDO EL USUARIO INGRESE DATOS

////FUNCION SUMA
//void suma(){
//	int n1,n2,total;
//
//	gotoxy (2,6); printf("Ingrese un numero: ");
//	scanf("%i",&n1);
//
//	gotoxy (2,8); printf("Ingrese un numero: ");
//	scanf("%i",&n1);
//
//	total = n1+n2;
//	gotoxy (2,10); printf("La suma total es: %i",total);
//}


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
