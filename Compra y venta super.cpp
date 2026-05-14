#include <stdio.h>
#include <string.h>

// 1. AGREGADO: ESTRUCTURA PARA GUARDAR HISTORIAL
struct ItemComprado {
    char nombre[50];
    int cantidad;
    float precioUnitario;
    
	};

int main() {

    char producto[50];
    int cantidad;
    int opcion;
    int metodopago;
    float precio;
    
      // 2. AGREGADO: ARREGLO PARA ALMACENAR HASTA 100 PRODUCTOS
    struct ItemComprado listaProductos[100];
    int totalProductosCargados = 0;

//Acumuladores solicitados    
    float totalAcumulado;
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

            while(getchar() != '\n'); //limpia el buffer
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
                    break;
                }

                // condicion de salida por nombre
                if(strcmp(producto, "FIN") == 0) {

                    opcion = 3;
                    break;
                }

                printf("Ingrese precio unitario: $");
                if (scanf("%f", &precio) !=1 || precio <= 0) {
                	printf (">>ERROR: Precio invalida\n");
                	while (getchar () != '\n');
                	break;
                
				}	

                printf("Ingrese cantidad: ");
                // Valida que sea un número Y que ese número sea mayor a 0
                if (scanf("%d", &cantidad) != 1 || cantidad <= 0) {
                    printf(">> ERROR: Cantidad invalida. El producto no fue registrado.\n");
                    while (getchar() != '\n'); // Limpia el buffer para eliminar letras si las hubiera
                    break; // Salta al final del switch de forma segura sin sumar nada
                }


            printf ("\n Seleccione metodo de pago: \n");
            printf("1 - Efectivo (10%% descuento)\n");
            printf("2 - Tarjeta (Sin descuento)\n");
            printf ("Opcion: ");
            scanf("%d", &metodopago);
            
            //Evaluar multiplicador de descuento 
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
                
                 
                // 3. AGREGADO: GUARDAR EN LA LISTA ANTES DE SUMAR
                if (totalProductosCargados < 100) {
                    strcpy(listaProductos[totalProductosCargados].nombre, producto);
                    listaProductos[totalProductosCargados].cantidad = cantidad;
                    listaProductos[totalProductosCargados].precioUnitario = precio; // Conserva el precio individual
                    totalProductosCargados++;
                }


                //Calculo de acumuladores

                subtotalSindescuento += (precio * cantidad);
                totalCondescuento += (precio*cantidad) * multiplicador;
                contadorVentas++;
                
                //resultado del item

                // RESULTADO
                printf("\n-----------------------------------------\n");
                printf("PRODUCTO REGISTRADO CORRECTAMENTE\n");
                printf("-----------------------------------------\n");
                printf("Producto: %s\n", producto);
                printf("Cantidad: %d\n", cantidad);
                printf("Subtotal item con desc: $%.2f\n", (precio*cantidad)*multiplicador);
                printf("-----------------------------------------\n");

                break;

            case 2:

                printf("\n");
                printf("=================================================\n");
                printf("                RESUMEN ACTUAL\n");
                printf("=================================================\n");
                printf("Ultimo productos: %s\n", producto);
                printf("Productos registrados: %d\n", contadorVentas);
                printf("Subtotal bruto (Sin desc): $%.2f\n", subtotalSindescuento);
                printf("Total Neto (Con desc):       $%.2f\n", totalCondescuento);
                printf("=================================================\n");

                break;

            case 3:

                printf("\n");
                printf("=================================================\n");
                printf("              COMPRA FINALIZADA\n");
                printf("=================================================\n");
                // 4. AGREGADO: MOSTRAR LISTA DE PRODUCTOS SOLO NOMBRE Y CANTIDAD
                printf("LISTA DE PRODUCTOS:\n");
                printf("%-30s %-10s\n", "Producto", "Cantidad");
                printf("-------------------------------------------------\n");
                for (int i = 0; i < totalProductosCargados; i++) {
                    printf("%-30s %-10d\n", 
                           listaProductos[i].nombre, 
                           listaProductos[i].cantidad);
                }
				printf("Productos comprados: %d\n", contadorVentas);
                printf("SUBTOTAL GENERAL:      $%.2f\n", totalAcumulado);
                printf("TOTAL A PAGAR:      $%.2f\n", totalCondescuento);
                printf("=================================================\n");
                printf("        GRACIAS POR SU COMPRA\n");
                printf("=================================================\n");

                break;

            default:
               printf("\n>> ERROR: Opcion no valida. \n");

       break;
        }

    } while(opcion != 3);

    return 0;
}

