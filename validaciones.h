#ifndef VALIDACIONES_H
#define VALIDACIONES_H

int leerLinea(char entrada[], int capacidad);
int leerNumero(const char mensaje[], double defecto, double minimo, double maximo, double *valor);
int leerEntero(const char mensaje[], int minimo, int maximo, int *valor);
void esperarEnter(void);

#endif

