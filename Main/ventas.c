#include "productos.h"
#include "UserLibs.h"
#include "carritoCompras.h"
#define archivoVentas "Ventas.dat"
#define ArchivoUsuarios "ArchivoUsuario.dat"
#define ArchProductos "Stock.dat"
#include "ventas.h"


void descontarSaldoAuxiliar(int idUsuario, float gasto)
{

    FILE *bufferUsuario = fopen(ArchivoUsuarios, "r+b");
    usuario aux;
    usuario deseado = BuscarUsuario(idUsuario);

    if (bufferUsuario)
    {
        while (fread(&aux, sizeof(usuario), 1, bufferUsuario) > 0)
        {
            if (deseado.idCliente == aux.idCliente)
            {

                fseek(bufferUsuario, sizeof(usuario) * (-1), SEEK_CUR);
                aux.saldo = (aux.saldo - gasto);
                fwrite(&aux, sizeof(usuario), 1, bufferUsuario);
                fclose(bufferUsuario);
            }
        }
    }
}

int verificarSaldo(float saldo, float gasto)
{
    int flag = 0;

    if (saldo >= gasto)
    {
        flag = 1;
    }
    return flag;
}

void generarCompra(int idUsuario, float gasto)
{
    usuario deseado = BuscarUsuario(idUsuario);

    do
    {
        gotoxy(7, 21);
        printf("Saldo insuficiente, elimine un producto de su carrito. \n");

    } while (verificarSaldo(deseado.saldo, gasto) == 0);

    if (verificarSaldo(deseado.saldo, gasto) == 1)
    {
        /// descuenta del saldo.
        /// descuenta del stock de los productos.
        /// persiste en archivos de  usuario.
        compraConfirmada(idUsuario, gasto);
    }
}

void compraConfirmada(int id, float gasto)
{

    usuario deseado = BuscarUsuario(id);

    descontarSaldoAuxiliar(id, gasto); /// se descuenta el saldo del usuario.

    descontarLoDelCarrito(deseado); /// se descuenta el stock del archivo productos.

    int idVenta = generarIdVenta();

    persistirCompraEnUsuarioyVentas(id, idVenta); /// pasa la subventa a venta. pide datos de envio/// guarda en el archivo usuario. reinicia los validos de subVentas.
}

void persistirCompraEnUsuarioyVentas(int idUsuario, int idVenta)
{

    usuario deseado = BuscarUsuario(idUsuario);

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
                    total += aux.carrito[i].subtotal;
                }
                aux.compras[aux.validosCompras].estadoEnvio = 0;
                aux.compras[aux.validosCompras].estadoVenta = 0;
                aux.compras[aux.validosCompras].idCliente = idUsuario;
                aux.compras[aux.validosCompras].idVenta = idVenta;
                aux.compras[aux.validosCompras].total = total;
                aux.validosCarrito = 0;

                pedirDatosEnvio(aux.compras[aux.validosCompras].despachar);

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
                Aux.cantidad = (Aux.cantidad - cantidad);
                mostrarProducto(Aux);
                fwrite(&Aux, sizeof(producto), 1, buffer);
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
    int id = 0;

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

    while (i < A.validosCarrito)
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

    printf("\nIngrese el pais de destino: \n");
    fflush(stdin);
    gets(Aux.pais);

    printf("\nIngrese la provincia: \n");
    fflush(stdin);
    gets(Aux.provincia);

    printf("\nIngrese la ciudad: \n");
    fflush(stdin);
    gets(Aux.ciudad);

    printf("\nIngrese la direccion: \n");
    fflush(stdin);
    gets(Aux.direccion);

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
