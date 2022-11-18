#include "productos.h"
#include "UserLibs.h"
#include "carritoCompras.h"
#define archivoVentas "Ventas.dat"
#define ArchivoUsuarios "ArchivoUsuario.dat"
#define ArchProductos "Stock.dat"
#include "ventas.h"

/// FUNCION 1 QUE SE INVOCA PARA GENERAR LA COMPRA
void generarCompra(int idUsuario, float gasto)
{

    usuario deseado = BuscarUsuario(idUsuario);

    if (verificarSaldo(deseado.saldo, gasto) == 0)
    {
        gotoxy(7, 21);
        printf("Saldo insuficiente, elimine un producto de su carrito. \n");
    }

    if (verificarSaldo(deseado.saldo, gasto) == 1)
    {
        /// descuenta del saldo.
        /// persiste en archivos de  usuario.
        compraConfirmada(deseado, gasto);
        descontarLoDelCarrito(deseado);
    }
}

/// FUNCION 2 QUE SE INVOCA PARA GENERAR LA COMPRA
int verificarSaldo(float saldo, float gasto)
{
    int flag = 0;

    if (saldo >= gasto)
    {
        flag = 1;
    }
    return flag;
}

/// FUNCION 3 QUE SE INVOCA PARA GENRAR LA COMPRA
void compraConfirmada(usuario deseado, float gasto)
{

    /// se descuenta el saldo del usuario.
    descontarSaldoAuxiliar(deseado, gasto);
    int idVenta = generarIdVenta();
    ;
    /// pasa la subventa a venta. pide datos de envio/// guarda en el archivo usuario. reinicia los validos de subVentas.
    // descontarLoDelCarrito(deseado);
    persistirCompraEnUsuarioyVentas(deseado, idVenta, gasto);
}

/// FUNCION 4 QUE SE INVOCA PARA GENERAR LA COMPRA
void descontarSaldoAuxiliar(usuario deseado, float gasto)
{

    usuario aux;

    FILE *bufferUsuario = fopen(ArchivoUsuarios, "r+b");

    if (bufferUsuario)
    {
        while (fread(&aux, sizeof(usuario), 1, bufferUsuario) > 0)
        {
            if (deseado.idCliente == aux.idCliente)
            {
                fseek(bufferUsuario, sizeof(usuario) * (-1), SEEK_CUR);
                aux.saldo = (aux.saldo - gasto);
                fwrite(&aux, sizeof(usuario), 1, bufferUsuario);
            }
            fclose(bufferUsuario);
        }
    }
}

void persistirCompraEnUsuarioyVentas(usuario deseado, int idVenta, float gasto)
{
    usuario aux;

    venta cursor;

    FILE *bufferVentas = fopen(archivoVentas, "ab");

    FILE *bufferUsuarios = fopen(ArchivoUsuarios, "r+b");

    float total;

    if (bufferUsuarios && bufferVentas)
    {
        while (fread(&aux, sizeof(usuario), 1, bufferUsuarios) > 0)
        {
            if (deseado.idCliente == aux.idCliente)
            {
                fseek(bufferUsuarios, sizeof(usuario) * (-1), SEEK_CUR);

                for (int i = 0; i < aux.validosCarrito; i++)
                {
                    aux.carrito[i] = aux.compras[aux.validosCompras].arreglo[i];
                    total += (aux.carrito[i].subtotal * aux.carrito[i].cantidad);
                }
                aux.compras[aux.validosCompras].estadoEnvio = 0;
                aux.compras[aux.validosCompras].estadoVenta = 0;
                aux.compras[aux.validosCompras].idCliente = deseado.idCliente;
                aux.compras[aux.validosCompras].idVenta = idVenta;
                aux.compras[aux.validosCompras].total = gasto;
                aux.saldo -= gasto;
                aux.validosCarrito = 0;
                aux.compras[aux.validosCompras].despachar = pedirDatosEnvio(aux.compras[aux.validosCompras].despachar);
                cursor = aux.compras[aux.validosCompras];
                aux.validosCompras += 1;
                fwrite(&aux, sizeof(usuario), 1, bufferUsuarios);
                fwrite(&cursor, sizeof(venta), 1, bufferVentas);
                fclose(bufferUsuarios);
                fclose(bufferVentas);
            }
        }
    }
}

void descontarLoDelCarrito(usuario A)
{

    for (int i = 0; i < A.validosCarrito; i++)
    {
        descontarStock(A.carrito[i].dato.nombre, A.carrito[i].cantidad);
    }
}

/// PRODUCTOS

void descontarStock(char aDescontar[], int cantidad)
{

    FILE *buffer = fopen(ArchProductos, "r+b");

    producto Aux;

    int flag = 0;
    if (buffer != NULL)
    {

        while (fread(&Aux, sizeof(producto), 1, buffer) > 0 && flag == 0)
        {

            if (0 == strcmpi(Aux.nombre, aDescontar))
            {
                fseek(buffer, sizeof(producto) * (-1), SEEK_CUR);
                //                Aux.cantidad = (Aux.cantidad - cantidad);
                Aux.cantidad -= cantidad;
                fwrite(&Aux, sizeof(producto), 1, buffer);
                gotoxy(10, 10);
                printf("Producto a descontar: %s cantidad: %i", Aux.nombre, Aux.cantidad);
                flag = 1;
                fclose(buffer);
            }
        }
    }
}

/// SUBVENTA

void cambiarEstadoSubVenta(char nombreProducto[], int idUsuario)
{

    FILE *bufferUsuario = fopen(ArchivoUsuarios, "r+b");
    usuario Aux;
    if (bufferUsuario)
    {

        while (fread(&Aux, sizeof(usuario), 1, bufferUsuario) > 0)
        {
            if (Aux.idCliente == idUsuario)
            {

                fseek(bufferUsuario, sizeof(usuario) * (-1), SEEK_CUR);
                Aux = BuscarProductoArraySubVenta(Aux, nombreProducto);
                fwrite(&Aux, sizeof(usuario), 1, bufferUsuario);
                fclose(bufferUsuario);
            }
        }
    }
}

void quitarProducto(char nombreProducto[], int idUsuario)
{
    char option;

    printf("Esta seguro que desea quitar este producto de su carrito? s/n ");
    fflush(stdin);
    scanf("%c", &option);

    if (option == 's')
    {
        cambiarEstadoSubVenta(nombreProducto, idUsuario);
    }
}

usuario BuscarProductoArraySubVenta(usuario A, char producto[])
{
    int i = 0;

    while (i < A.validosCarrito)
    {
        if (strcmpi(A.carrito[i].dato.nombre, producto) == 0)
        {
            A.carrito[i].flag = 0;
        }
        i++;
    }

    return A;
}

/// VENTAS

venta buscarVentaEnRegistroUsuario(int idVenta, int idUsuario)
{
    FILE *bufferUsuario = fopen(ArchivoUsuarios, "rb");

    venta Aux;

    usuario temporal;

    int flag = 0;

    int i = 0;

    if (bufferUsuario)
    {
        while (fread(&temporal, sizeof(usuario), 1, bufferUsuario) > 0 && flag == 0)
        {
            if (temporal.idCliente == idUsuario)
            {
                Aux = buscarUnaVentaEnArray(temporal, idVenta);
            }
        }
        fclose(bufferUsuario);
    }

    return Aux;
}

int generarIdVenta()
{
    FILE *bufferVentas = fopen(archivoVentas, "rb");
    venta Aux;
    int id = 1;

    if (bufferVentas)
    {

        while (fread(&Aux, sizeof(venta), 1, bufferVentas) > 0)
        {
            id++;
        }
        fclose(bufferVentas);
    }

    return id;
}

venta buscarUnaVentaEnArray(usuario A, int idVenta)
{
    int i = 0;
    int flag = 0;
    venta encontrada;

    while (i < A.validosCarrito && flag == 0)
    {
        if (A.compras[i].idVenta == idVenta)
        {
            encontrada = A.compras[i];
            flag = 1;
        }
        i++;
    }

    return encontrada;
}

/// ENVIO

destino pedirDatosEnvio(destino Aux)
{
    system("cls");
    dibujarCuadro(0, 0, 79, 24); // SE DIBUJA EL CUADRO PRINCIPAL
    dibujarCuadro(1, 1, 78, 3);  // SE DIBUJA EL CUADRO DEL TITULO

    centrarTexto("E-COMMERCE - DIRECCION DE ENVIO", 2);
    dibujarCuadro(1, 19, 78, 23); // SE DIBUJA EL CUADRO MENSAJE DE CONSOLA
    gotoxy(7, 21);
    printf("Mensaje de consola ...");

    gotoxy(7, 5);
    printf("Ingrese el pais de destino: ");
    fflush(stdin);
    gets(Aux.pais);

    gotoxy(7, 7);
    printf("Ingrese la provincia: ");
    fflush(stdin);
    gets(Aux.provincia);

    gotoxy(7, 9);
    printf("Ingrese la ciudad: ");
    fflush(stdin);
    gets(Aux.ciudad);

    gotoxy(7, 11);
    printf("Ingrese la direccion: ");
    fflush(stdin);
    gets(Aux.direccion);

    gotoxy(7, 21);
    printf("                                     ");
    gotoxy(7, 21);
    printf("Has realizado tu compra con exito!");
    sleep(1);

    return Aux;
}

/// NODO VENTA DOBLE

nodoVentaD *despersistirListaDobleVentasExitosas(nodoVentaD *lista)
{
    FILE *ptr = fopen(archivoVentas, "rb");
    venta aux;
    nodoVentaD *aux2;
    if (ptr != NULL)
    {
        while (fread(&aux, sizeof(venta), 1, ptr) > 0)
        {
            /// TESTEAR VENTA
            //        gotoxy(10,10);
            //        printf("%i ",aux.idVenta);
            //        gotoxy(10,11);
            //        system("pause");
            if (aux.estadoVenta == 0)
            {
                aux2 = crearNodoDobleVenta(aux);
                lista = agregarAlFinalDobleVenta(lista, aux2);
            }
        }
        fclose(ptr);
    }
    return lista;
}
