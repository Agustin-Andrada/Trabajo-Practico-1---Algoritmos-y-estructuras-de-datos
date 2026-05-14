#include <stdio.h>
#include <string.h>

// 1. ESTRUCTURA COMPLETA PARA GUARDAR EL HISTORIAL CON PRECIOS
struct ItemComprado {
    char nombre[50];
    int cantidad;
    float precioUnitario;
    float totalItemSinDesc;
    float totalItemConDesc;
};

int main() {

    char producto[50] = ""; // Inicializado vacío para controlar el resumen
    int cantidad;
    int opcion;
    int metodopago;
    float precio;
    
    // ARREGLO PARA ALMACENAR HASTA 100 PRODUCTOS
    struct ItemComprado listaProductos[100];
    int totalProductosCargados = 0;

    // Acumuladores solicitados    
    float subtotalSindescuento = 0;
    float totalCondescuento = 0;
    float multiplicador;
    int contadorVentas = 0;

    do {
        printf("\n");
        printf("=================================================\n");
        printf("             SISTEMA DE VENTAS 2026              \n");
        printf("=================================================\n");
        printf("1 - Registrar producto\n");
        printf("2 - Ver resumen actual\n");
        printf("3 - Terminar compra\n");
        printf("=================================================\n");
        printf("Seleccione una opcion: ");
        
        // VALIDACION MENU
        if (scanf("%d", &opcion) != 1) {
            printf(">> ERROR: Debe ingresar un numero.\n");
            while(getchar() != '\n'); // limpia el buffer
            opcion = 0;
            continue;
        }

        switch(opcion) {

            case (1):
                printf("\n-----------------------------------------\n");
                printf("         REGISTRO DE PRODUCTOS\n");
                printf("-----------------------------------------\n");

                printf("Ingrese nombre del producto: ");
                scanf("%s", producto);

                // VALIDACION DEL NOMBRE
                if(strlen(producto) < 2) {
                    printf(">> ERROR: Nombre demasiado corto.\n");
                    producto[0] = '\0'; // Resetea la cadena para el resumen actual
                    break;
                }

                // condicion de salida por nombre
                if(strcmp(producto, "FIN") == 0) {
                    opcion = 3;
                    break;
                }

                printf("Ingrese precio unitario: $");
                if (scanf("%f", &precio) != 1 || precio <= 0) {
                	printf (">> ERROR: Precio invalido\n");
                	while (getchar () != '\n');
                    producto[0] = '\0';
                	break;
				}	

                printf("Ingrese cantidad: ");
                if (scanf("%d", &cantidad) != 1 || cantidad <= 0) {
                    printf(">> ERROR: Cantidad invalida. El producto no fue registrado.\n");
                    while (getchar() != '\n'); 
                    producto[0] = '\0';
                    break; 
                }

                printf ("\n Seleccione metodo de pago: \n");
                printf("1 - Efectivo (10%% descuento)\n");
                printf("2 - Tarjeta (Sin descuento)\n");
                printf ("Opcion: ");
                scanf("%d", &metodopago);
            
                // Evaluar multiplicador de descuento 
                multiplicador = 1.0;
                switch(metodopago) {
                    case 1:
                        printf(">> Descuento aplicado correctamente.\n");
                        multiplicador = 0.90;
                        break;
                    case 2:
                        printf(">> Pago con tarjeta seleccionado.\n");
                        multiplicador = 1.0;
                        break;
                    default:
                        printf(">> Metodo invalido. Sin descuento.\n");
                }
                
                // GUARDAR EN LA LISTA HISTÓRICA CON TODOS LOS DETALLES
                if (totalProductosCargados < 100) {
                    strcpy(listaProductos[totalProductosCargados].nombre, producto);
                    listaProductos[totalProductosCargados].cantidad = cantidad;
                    listaProductos[totalProductosCargados].precioUnitario = precio;
                    listaProductos[totalProductosCargados].totalItemSinDesc = precio * cantidad;
                    listaProductos[totalProductosCargados].totalItemConDesc = (precio * cantidad) * multiplicador;
                    totalProductosCargados++;
                }

                // Calculo de acumuladores generales
                subtotalSindescuento += (precio * cantidad);
                totalCondescuento += (precio * cantidad) * multiplicador;
                contadorVentas++;
                
                // RESULTADO DE REGISTRO CON REQUERIMIENTOS NUEVOS
                printf("\n-----------------------------------------\n");
                printf("PRODUCTO REGISTRADO CORRECTAMENTE\n");
                printf("-----------------------------------------\n");
                printf("Producto:        %s\n", producto);
                printf("Cantidad:        %d\n", cantidad);
                printf("Precio Unitario: $%.2f\n", precio);
                printf("Total Sin Desc:  $%.2f\n", precio * cantidad);
                printf("Total Con Desc:  $%.2f\n", (precio * cantidad) * multiplicador);
                printf("-----------------------------------------\n");
                break;

            case 2:
                printf("\n");
                printf("================================================================================\n");
                printf("                                RESUMEN ACTUAL\n");
                printf("================================================================================\n");
                
                // Validación de datos vacíos según requerimiento
                if (contadorVentas == 0) {
                    printf("Ultimo producto: \n"); // Cadena vacía (no muestra nada)
                } else {
                    printf("Ultimo producto: %s\n", producto);
                }
                
                printf("Productos registrados: %d\n", contadorVentas);
                printf("Subtotal bruto (Sin desc): $%.2f\n", subtotalSindescuento);
                printf("Total Neto (Con desc):     $%.2f\n", totalCondescuento);
                printf("--------------------------------------------------------------------------------\n");
                
                // Detalle extendido por cada ítem individual cargado
                if (totalProductosCargados > 0) {
                    printf("%-20s %-7s %-12s %-15s %-15s\n", "Producto", "Cant.", "P. Unit.", "Total S/Desc", "Total C/Desc");
                    printf("--------------------------------------------------------------------------------\n");
                    for (int i = 0; i < totalProductosCargados; i++) {
                        printf("%-20s %-7d $%-11.2f $%-14.2f $%-14.2f\n", 
                               listaProductos[i].nombre, 
                               listaProductos[i].cantidad, 
                               listaProductos[i].precioUnitario,
                               listaProductos[i].totalItemSinDesc,
                               listaProductos[i].totalItemConDesc);
                    }
                } else {
                    printf("No hay items individuales registrados todavia.\n");
                }
                printf("================================================================================\n");
                break;

            case 3:
                printf("\n");
                printf("================================================================================\n");
                printf("                               COMPRA FINALIZADA\n");
                printf("================================================================================\n");
                
                // Muestra de todos los productos en formato ticket tabular completo
                printf("DETALLE DE TICKET:\n");
                printf("%-20s %-7s %-12s %-15s %-15s\n", "Producto", "Cant.", "P. Unit.", "Total S/Desc", "Total C/Desc");
                printf("--------------------------------------------------------------------------------\n");
                for (int i = 0; i < totalProductosCargados; i++) {
                    printf("%-20s %-7d $%-11.2f $%-14.2f $%-14.2f\n", 
                           listaProductos[i].nombre, 
                           listaProductos[i].cantidad, 
                           listaProductos[i].precioUnitario,
                           listaProductos[i].totalItemSinDesc,
                           listaProductos[i].totalItemConDesc);
                }
                printf("--------------------------------------------------------------------------------\n");
                
                // Cierre matemático final
				printf("TOTAL PRODUCTOS CARGADOS:  %d\n", totalProductosCargados);
                printf("SUBTOTAL COMPRA (S/Desc): $%.2f\n", subtotalSindescuento);
                printf("PRECIO FINAL TOTAL(C/Desc):$%.2f\n", totalCondescuento);
                printf("================================================================================\n");
                printf("                         GRACIAS POR SU COMPRA\n");
                printf("================================================================================\n");
                break;

            default:
               printf("\n>> ERROR: Opcion no valida. \n");
               break;
        }

    } while(opcion != 3);

    return 0;
}
