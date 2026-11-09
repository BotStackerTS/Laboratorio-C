#include <stdio.h>
#include "validaciones.h"

int leerLinea(char entrada[], int capacidad) {
    int i = 0, c;
    if (fgets(entrada, capacidad, stdin) == NULL) return 0;
    while (entrada[i] != '\0' && entrada[i] != '\n') i++;
    if (entrada[i] == '\n' || feof(stdin)) return 1;
    while ((c = getchar()) != '\n' && c != EOF) { }
    return -1;
}

int leerNumero(const char mensaje[], double defecto,
               double minimo, double maximo, double *valor) {
    char entrada[100], extra;
    double numero;
    int i, vacia, estado;
    while (1) {
        printf("%s [Defecto: %.2f]: ", mensaje, defecto);
        estado = leerLinea(entrada, 100);
        if (estado == 0) return 0;
        if (estado == -1) {
            printf("ERROR: La entrada es demasiado larga.\n");
            continue;
        }
        vacia = 1;
        for (i = 0; entrada[i] != '\0'; i++) {
            if (entrada[i] == ',') entrada[i] = '.';
            if (entrada[i] != ' ' && entrada[i] != '\t' &&
                entrada[i] != '\r' && entrada[i] != '\n') vacia = 0;
        }
        if (vacia) {
            numero = defecto;
        } else if (sscanf(entrada, " %lf %c", &numero, &extra) != 1) {
            printf("ERROR: Ingrese solamente un numero valido.\n");
            continue;
        }
        // Esta comparacion tambien rechaza NaN.
        if (!(numero >= minimo && numero <= maximo)) {
            printf("ERROR: Ingrese un valor entre %.2f y %.2f.\n", minimo, maximo);
            continue;
        }
        *valor = numero;
        return 1;
    }
}

int leerEntero(const char mensaje[], int minimo, int maximo, int *valor) {
    char entrada[100], extra;
    int numero, estado;
    while (1) {
        printf("%s", mensaje);
        estado = leerLinea(entrada, 100);
        if (estado == 0) return 0;
        if (estado == -1 || sscanf(entrada, " %d %c", &numero, &extra) != 1) {
            printf("ERROR: Ingrese una opcion entera.\n");
            continue;
        }
        if (numero < minimo || numero > maximo) {
            printf("ERROR: Elija una opcion entre %d y %d.\n", minimo, maximo);
            continue;
        }
        *valor = numero;
        return 1;
    }
}

void esperarEnter(void) {
    char entrada[100];
    printf("\nPresione Enter para continuar...");
    leerLinea(entrada, 100);
}
