#include <stdio.h>
#include "simulador.h"
#include "validaciones.h"

int main(void) {
    Configuracion config;
    Mision historial[MAX_HISTORIAL], ultima;
    int cantidad = 0, hayUltima = 0;
    int opcion, i;

    establecerValoresIniciales(&config);
    while (1) {
        printf("\n========================================\n");
        printf("       SIMULADOR ARTEMIS - SLS\n");
        printf("========================================\n");
        printf("1. Configurar parametros de la mision\n");
        printf("2. Iniciar simulacion por eventos\n");
        printf("3. Ver reporte de la ultima mision\n");
        printf("4. Ver historial de simulaciones\n");
        printf("5. Restaurar parametros iniciales\n");
        printf("0. Salir\n");
        if (!leerEntero("Seleccione una opcion: ", 0, 5, &opcion)) {
            printf("\nFin de entrada. Saliendo.\n");
            break;
        }
        if (opcion == 0) {
            printf("Gracias por usar el simulador.\n");
            break;
        } else if (opcion == 1) {
            configurarMision(&config);
        } else if (opcion == 2) {
            if (!calcularMision(&config, &ultima)) {
                printf("ERROR: No se puede simular con estos parametros.\n");
            } else {
                hayUltima = 1;
                if (cantidad == MAX_HISTORIAL) {
                    for (i = 1; i < MAX_HISTORIAL; i++)
                        historial[i - 1] = historial[i];
                    cantidad--;
                }
                historial[cantidad] = ultima;
                cantidad++;
                ejecutarEventos(&ultima);
                mostrarReporte(&ultima);
            }
        } else if (opcion == 3) {
            if (hayUltima) mostrarReporte(&ultima);
            else printf("Primero debe ejecutar una simulacion.\n");
        } else if (opcion == 4) {
            mostrarHistorial(historial, cantidad);
        } else if (opcion == 5) {
            establecerValoresIniciales(&config);
            printf("Parametros originales restaurados.\n");
        }
    }
    return 0;
}
