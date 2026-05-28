#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Necesario para la funcion system()

// 1. ESTRUCTURA PARA GUARDAR EL HISTORIAL DE PRODUCTOS
struct ItemComprado {
    char nombre[50];
    int cantidad;
    float precioUnitario;
    float totalItemSinDesc;
    float totalItemConDesc;
    char formaPago[15]; 
    char tieneDescuento[10]; // Almacena "10%" o "" (vacio)
};

// Funcion para limpiar la pantalla de forma multiplataforma
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {

    char producto[50] = ""; 
    int cantidad;
    int opcion;
    int metodopago;
    float precio;
    char metodoTexto[15]; 
    char descTexto[10]; 
    
    // Banderas de control de las validaciones (Movidas aqui para evitar errores en el switch)
    int precioValido;
    int cantidadValida;
    int pagoValido;
    int i; // Variable para los ciclos for
    
    // ARREGLO PARA ALMACENAR HASTA 100 PRODUCTOS
    struct ItemComprado listaProductos[100];
    int totalProductosCargados = 0;

    // Acumuladores solicitados    
    float subtotalSindescuento = 0;
    float totalCondescuento = 0;
    float multiplicador;
    int contadorVentas = 0;

    // Limpieza inicial al arrancar el programa
    limpiarPantalla();

    do {
        printf("\n");
        printf("=================================================\n");
        printf("               SISTEMA DE VENTAS 2026              \n");
        printf("=================================================\n");
        printf("1 - Registrar producto\n");
        printf("2 - Ver resumen actual\n");
        printf("3 - Terminar compra\n");
        printf("4 - Salir\n");
        printf("=================================================\n");
        printf("Seleccione una opcion: ");
        
        // VALIDACION MENU PRINCIPAL
        if (scanf("%d", &opcion) != 1) {
            printf(">> ERROR: Debe ingresar un numero valido.\n");
            while(getchar() != '\n'); 
            opcion = 0;
            
            printf("\nPresione Enter para continuar...");
            getchar();
            limpiarPantalla();
            continue;
        }

        switch(opcion) {

            case 1:
                limpiarPantalla(); 
                printf("\n-----------------------------------------\n");
                printf("          REGISTRO DE PRODUCTOS\n");
                printf("-----------------------------------------\n");

                // 1. VALIDACION LOCAL: INGRESO DEL NOMBRE
                do {
                    printf("Ingrese el nombre del producto: ");
                    scanf("%s", producto);

                    if(strlen(producto) < 2) {
                        printf(">> ERROR: Nombre demasiado corto (minimo 2 caracteres).\n\n");
                        while(getchar() != '\n');
                        producto[0] = '\0';
                    }
                } while(strlen(producto) < 2 && strcmp(producto, "FIN") != 0);

                // Condicion especial de salida por comando FIN
                if(strcmp(producto, "FIN") == 0) {
                    opcion = 3; 
                    printf("\n>> Finalizando registro por comando FIN...\n");
                    printf("\nPresione Enter para procesar el Ticket...");
                    while (getchar() != '\n'); getchar();
                    limpiarPantalla(); 
                    break;
                }

                // 2. VALIDACION LOCAL: INGRESO DEL PRECIO
                precioValido = 0;
                do {
                    printf("Ingrese precio unitario: $");
                    if (scanf("%f", &precio) != 1 || precio <= 0) {
                        printf(">> ERROR: Precio invalido (debe ser un numero mayor a 0).\n\n");
                        while (getchar() != '\n'); 
                    } else {
                        precioValido = 1; 
                    }
                } while (!precioValido);

                // 3. VALIDACION LOCAL: INGRESO DE LA CANTIDAD
                cantidadValida = 0;
                do {
                    printf("Ingrese cantidad: ");
                    if (scanf("%d", &cantidad) != 1 || cantidad <= 0) {
                        printf(">> ERROR: Cantidad invalida (debe ser un numero entero mayor a 0).\n\n");
                        while (getchar() != '\n'); 
                    } else {
                        cantidadValida = 1;
                    }
                } while (!cantidadValida);

                // 4. VALIDACION LOCAL: INGRESO DEL METODO DE PAGO
                pagoValido = 0;
                do {
                    printf("\nSeleccione un metodo de pago:\n");
                    printf("1 - Efectivo (10%% descuento)\n");
                    printf("2 - Tarjeta (Sin descuento)\n");
                    printf("Opcion: ");
                    
                    if (scanf("%d", &metodopago) != 1 || (metodopago != 1 && metodopago != 2)) {
                        printf(">> ERROR: Opcion invalida. Elija 1 o 2.\n");
                        while (getchar() != '\n'); 
                    } else {
                        pagoValido = 1;
                    }
                } while (!pagoValido);
            
                // ASIGNACION DE VALORES POST-VALIDACIONES
                if (metodopago == 1) {
                    printf("\n>> Pago en efectivo seleccionado. Descuento aplicado.\n");
                    multiplicador = 0.90;
                    strcpy(metodoTexto, "Efectivo");
                    strcpy(descTexto, "10%"); 
                } else {
                    printf("\n>> Pago con tarjeta seleccionado.\n");
                    multiplicador = 1.0;
                    strcpy(metodoTexto, "Tarjeta");
                    strcpy(descTexto, ""); 
                }
                
                // GUARDAR EN LA LISTA HISTORICA
                if (totalProductosCargados < 100) {
                    strcpy(listaProductos[totalProductosCargados].nombre, producto);
                    listaProductos[totalProductosCargados].cantidad = cantidad;
                    listaProductos[totalProductosCargados].precioUnitario = precio;
                    listaProductos[totalProductosCargados].totalItemSinDesc = precio * cantidad;
                    listaProductos[totalProductosCargados].totalItemConDesc = (precio * cantidad) * multiplicador;
                    strcpy(listaProductos[totalProductosCargados].formaPago, metodoTexto); 
                    strcpy(listaProductos[totalProductosCargados].tieneDescuento, descTexto); 
                    totalProductosCargados++;
                }

                // Calculo de acumuladores generales
                subtotalSindescuento += (precio * cantidad);
                totalCondescuento += (precio * cantidad) * multiplicador;
                contadorVentas++;
                
                printf("\n-----------------------------------------\n");
                printf("PRODUCTO REGISTRADO CORRECTAMENTE\n");
                printf("-----------------------------------------\n");
                
                printf("\nPresione Enter para continuar...");
                while (getchar() != '\n'); 
                getchar();                 
                limpiarPantalla(); 
                break;

            case 2:
                limpiarPantalla(); 
                printf("\n");
                printf("=========================================================================\n");
                printf("                                RESUMEN ACTUAL\n");
                printf("=========================================================================\n");
                
                if (contadorVentas == 0) {
                    printf("Ultimo producto registrado: \n"); 
                } else {
                    printf("Ultimo producto registrado: %s (%s)\n", producto, metodoTexto); 
                }
                printf("-------------------------------------------------------------------------\n");
                
                if (totalProductosCargados > 0) {
                    printf("%-20s %-7s %-12s %-12s %-12s %-12s\n", "Producto", "Cant.", "P. Unit.", "M. Pago", "Total Item", "Descuento");
                    printf("-------------------------------------------------------------------------\n");
                    for (i = 0; i < totalProductosCargados; i++) {
                        printf("%-20s %-7d $%-11.2f %-12s $%-11.2f %-12s\n", 
                               listaProductos[i].nombre, 
                               listaProductos[i].cantidad, 
                               listaProductos[i].precioUnitario,
                               listaProductos[i].formaPago, 
                               listaProductos[i].totalItemConDesc, 
                               listaProductos[i].tieneDescuento);
                    }
                    printf("-------------------------------------------------------------------------\n");
                    
                    printf("%-52s %d\n", "CANTIDAD DE PRODUCTOS REGISTRADOS:", contadorVentas);
                    printf("%-52s $%.2f\n", "TOTAL NETO ACUMULADO:", totalCondescuento);
                } else {
                    printf("No hay items individuales registrados todavia.\n");
                }
                printf("=========================================================================\n");
                
                printf("\nPresione Enter para continuar...");
                while (getchar() != '\n'); 
                getchar();                 
                limpiarPantalla(); 
                break;

            case 3:
                limpiarPantalla(); 
                printf("\n");
                printf("=========================================================================\n");
                printf("                            COMPRA FINALIZADA\n");
                printf("=========================================================================\n");
                
                printf("DETALLE DE TICKET:\n");
                printf("%-20s %-7s %-12s %-12s %-12s %-12s\n", "Producto", "Cant.", "P. Unit.", "M. Pago", "Total Item", "Descuento");
                printf("-------------------------------------------------------------------------\n");
                for (i = 0; i < totalProductosCargados; i++) {
                    printf("%-20s %-7d $%-11.2f %-12s $%-11.2f %-12s\n", 
                           listaProductos[i].nombre, 
                           listaProductos[i].cantidad, 
                           listaProductos[i].precioUnitario,
                           listaProductos[i].formaPago, 
                           listaProductos[i].totalItemConDesc, 
                           listaProductos[i].tieneDescuento);         
                }
                printf("-------------------------------------------------------------------------\n");
                
                printf("%-52s %d\n", "TOTAL PRODUCTOS COMPRADOS:", totalProductosCargados);
                printf("%-52s $%.2f\n", "TOTAL DE TODA LA CUENTA:", totalCondescuento); 
                printf("=========================================================================\n");
                printf("                       GRACIAS POR SU COMPRA\n");
                printf("=========================================================================\n");
                
                printf("\nPresione Enter para continuar...");
                while (getchar() != '\n'); 
                getchar();                 
                limpiarPantalla();
                break;
                
            case 4:
                limpiarPantalla();
                printf("\n=================================================\n");
                printf("          SALIENDO DEL SISTEMA.... \n");
                printf("          ¡Tenga un buen dia!\n");
                printf("=================================================\n\n");
                break;
                
            default:
                printf("\n>> ERROR: Opcion no valida. \n");
                printf("\nPresione Enter para continuar...");
                while (getchar() != '\n'); getchar();
                limpiarPantalla();
                break;
        }

    } while(opcion != 4); 

    return 0;
}
