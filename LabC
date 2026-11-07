#include <stdio.h>
#include <math.h>

#define GRAVEDAD 9.80
#define MAX_EVENTOS 3
#define MAX_HISTORIAL 10

// ESTRUCTURAS DE DATOS

typedef struct {
    double a1;
    double t1;
    double a2;
    double alturaObjetivo;
} Configuracion;

typedef struct {
    char nombre[45];
    double tiempo;
    double altura;
    double velocidad;
    double aceleracion;
} Evento;

typedef struct {
    Configuracion datos;

    double v1, y1, deltaY, t2, v2;
    double tiempoAscensoLibre;
    double alturaMaxima;
    double aceleracionEnG;

    Evento eventos[MAX_EVENTOS];
    int cantidadEventos;
} Mision;


// FUNCIONES DE LECTURA Y VALIDACION

int leerLinea(char entrada[], int capacidad) {

    int i = 0, c;

    if (fgets(entrada, capacidad, stdin) == NULL) {
        return 0;
    }

    while (entrada[i] != '\0' && entrada[i] != '\n') {
        i++;
    }

    if (entrada[i] == '\n' || feof(stdin)) {
        return 1;
    }

    while ((c = getchar()) != '\n' && c != EOF) {
    }

    return -1;
}


// LECTURA DE NUMEROS REALES

int leerNumero(const char mensaje[],
               double defecto,
               double minimo,
               double maximo,
               double *valor) {

    char entrada[100], extra;
    double numero;
    int i, vacia, estado;

    while (1) {

        printf("%s [Defecto: %.2f]: ", mensaje, defecto);

        estado = leerLinea(entrada, 100);

        if (estado == 0) {
            return 0;
        }

        if (estado == -1) {
            printf("ERROR: La entrada es demasiado larga.\n");
            continue;
        }

        vacia = 1;

        for (i = 0; entrada[i] != '\0'; i++) {

            if (entrada[i] == ',') {
                entrada[i] = '.';
            }

            if (entrada[i] != ' ' &&
                entrada[i] != '\t' &&
                entrada[i] != '\r' &&
                entrada[i] != '\n') {

                vacia = 0;
            }
        }

        if (vacia) {

            numero = defecto;

        } else if (sscanf(entrada, " %lf %c", &numero, &extra) != 1) {

            printf("ERROR: Ingrese solamente un numero valido.\n");
            continue;
        }

        if (!(numero >= minimo && numero <= maximo)) {

            printf("ERROR: Ingrese un valor entre %.2f y %.2f.\n", minimo, maximo);

            continue;
        }

        *valor = numero;

        return 1;
    }
}


// LECTURA DE OPCIONES DEL MENU

int leerEntero(const char mensaje[], int minimo, int maximo, int *valor) {

    char entrada[100], extra;
    int numero, estado;

    while (1) {

        printf("%s", mensaje);

        estado = leerLinea(entrada, 100);

        if (estado == 0) {
            return 0;
        }

        if (estado == -1 ||
            sscanf(entrada, " %d %c", &numero, &extra) != 1) {

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


// ESPERAR PARA MOSTRAR EL SIGUIENTE EVENTO

void esperarEnter(void) {

    char entrada[100];

    printf("\nPresione Enter para continuar...");

    leerLinea(entrada, 100);
}


// VALORES INICIALES DE LA MISION

void establecerValoresIniciales(Configuracion *config) {

    config->a1 = 20.0;
    config->t1 = 120.0;
    config->a2 = 12.5;
    config->alturaObjetivo = 160000.0;
}


// CONFIGURACION DE PARAMETROS

void configurarMision(Configuracion *config) {

    Configuracion nueva = *config;

    double alturaPrimeraFase;
    double alturaIngresada;
    double defectoAltura;

    printf("\n--- CONFIGURACION DE LA MISION ---\n");
    printf("Presione Enter para conservar el valor mostrado.\n");

    if (!leerNumero("Aceleracion primera fase (m/s^2)", nueva.a1, 0.01, 1000.0, &nueva.a1)) {
        return;
    }

    if (!leerNumero("Tiempo desacople SRB (s)", nueva.t1, 0.01, 10000.0, &nueva.t1)) {
        return;
    }

    if (!leerNumero("Aceleracion segunda fase (m/s^2)", nueva.a2, 0.01, 1000.0, &nueva.a2)) {
        return;
    }

    alturaPrimeraFase = 0.5 * nueva.a1 * nueva.t1 * nueva.t1;

    defectoAltura = nueva.alturaObjetivo;

    if (defectoAltura <= alturaPrimeraFase) {
        defectoAltura = alturaPrimeraFase + 1000.0;
    }

    do {

        if (!leerNumero("Altura objetivo (m)", defectoAltura, 0.01, 1000000000000.0, &alturaIngresada)) {
            return;
        }

        if (alturaIngresada <= alturaPrimeraFase) {

            printf("ERROR: La altura debe superar %.2f m, " "alcanzados en la fase 1.\n", alturaPrimeraFase);
        }

    } while (alturaIngresada <= alturaPrimeraFase);

    nueva.alturaObjetivo = alturaIngresada;

    *config = nueva;

    printf("Configuracion guardada.\n");
}


// CALCULOS DE LAS CUATRO PREGUNTAS

int calcularMision(const Configuracion *config, Mision *mision) {

    double discriminante;

    if (config->a1 <= 0 || config->a1 > 1000 ||
        config->t1 <= 0 || config->t1 > 10000 ||
        config->a2 <= 0 || config->a2 > 1000 ||
        config->alturaObjetivo <= 0 ||
        config->alturaObjetivo > 1e12) {

        return 0;
    }

    mision->datos = *config;

    // PREGUNTA 1: PRIMERA FASE

    mision->v1 = config->a1 * config->t1;

    mision->y1 = 0.5 * config->a1 * config->t1 * config->t1;

    // PREGUNTA 2: SEGUNDA FASE

    mision->deltaY = config->alturaObjetivo - mision->y1;

    if (mision->deltaY <= 0) {
        return 0;
    }

    discriminante = mision->v1 * mision->v1 + 2.0 * config->a2 * mision->deltaY;

    if (!(discriminante > 0)) {
        return 0;
    }

    mision->v2 = sqrt(discriminante);

    mision->t2 = 2.0 * mision->deltaY / (mision->v1 + mision->v2);

    // PREGUNTA 3: ASCENSO LIBRE

    mision->tiempoAscensoLibre = mision->v2 / GRAVEDAD;

    mision->alturaMaxima = config->alturaObjetivo + mision->v2 * mision->v2 / (2.0 * GRAVEDAD);

    // PREGUNTA 4: MULTIPLOS DE G

    mision->aceleracionEnG =
        config->a1 / GRAVEDAD;

    // REGISTRO DE EVENTOS

    mision->cantidadEventos = 3;

    // EVENTO 1: DESACOPLE SRB

    snprintf(mision->eventos[0].nombre, 45, "Desacople de los SRB");

    mision->eventos[0].tiempo = config->t1;
    mision->eventos[0].altura = mision->y1;
    mision->eventos[0].velocidad = mision->v1;
    mision->eventos[0].aceleracion = config->a1;

    // EVENTO 2: APAGADO DE MOTORES

    snprintf(mision->eventos[1].nombre, 45, "Apagado de motores");

    mision->eventos[1].tiempo = config->t1 + mision->t2;

    mision->eventos[1].altura = config->alturaObjetivo;

    mision->eventos[1].velocidad = mision->v2;
    mision->eventos[1].aceleracion = config->a2;

    // EVENTO 3: ALTURA MAXIMA

    snprintf(mision->eventos[2].nombre, 45, "Altura maxima alcanzada");

    mision->eventos[2].tiempo = config->t1 + mision->t2 + mision->tiempoAscensoLibre;

    mision->eventos[2].altura = mision->alturaMaxima;
    mision->eventos[2].velocidad = 0.0;
    mision->eventos[2].aceleracion = -GRAVEDAD;

    return 1;
}


// DIBUJO DE LA PRIMERA FASE

void dibujarFase1(void) {

    printf("\n========================================\n");
    printf("       FASE 1 - DESPEGUE DEL SLS\n");
    printf("========================================\n");

    printf("                 /\\\n");
    printf("                /  \\\n");
    printf("               /ORION\\\n");
    printf("               |     |\n");
    printf("          /\\   |     |   /\\\n");
    printf("         |  |  | SLS |  |  |\n");
    printf("         |SRB| |     | |SRB|\n");
    printf("         |  |  |     |  |  |\n");
    printf("         |__|  |_____|  |__|\n");
    printf("          ||      ||     ||\n");
    printf("         /\\/\\    /\\/\\   /\\/\\\n");
    printf("        /\\/\\/\\  /\\/\\/\\ /\\/\\/\\\n");

    printf("\n            ASCENSO VERTICAL\n");
}


// DIBUJO DE LA SEGUNDA FASE

void dibujarFase2(void) {

    printf("\n========================================\n");
    printf("     FASE 2 - ASCENSO CON MOTOR\n");
    printf("========================================\n");

    printf("                  /\\\n");
    printf("                 /  \\\n");
    printf("                /ORION\\\n");
    printf("                |     |\n");
    printf("                | SLS |\n");
    printf("                |     |\n");
    printf("                |     |\n");
    printf("                |_____|\n");
    printf("                   ||\n");
    printf("                  /\\/\\\n");
    printf("                 /\\/\\/\\\n");

    printf("\n          SRB             SRB\n");
    printf("           \\               /\n");
    printf("            \\             /\n");
    printf("             v           v\n");

    printf("\n       PROPULSORES DESACOPLADOS\n");
}


// DIBUJO DE LA TERCERA FASE

void dibujarFase3(void) {

    printf("\n========================================\n");
    printf("    FASE 3 - ASCENSO LIBRE DE ORION\n");
    printf("========================================\n");

    printf("             ALTURA MAXIMA\n");
    printf("                 /\\\n");
    printf("                /  \\\n");
    printf("               |ORION|\n");
    printf("               |_____|\n");
    printf("                 v = 0\n");
    printf("                   ^\n");
    printf("                   |\n");
    printf("            ASCENSO POR INERCIA\n");
    printf("                   |\n");
    printf("                   |\n");
    printf("           APAGADO DE MOTORES\n");

    printf("\n         GRAVEDAD HACIA ABAJO\n");
    printf("                   v\n");
}


// DIBUJO DEL PUNTO 4

void dibujarFase4(void) {

    printf("\n========================================\n");
    printf("    ACELERACION DE LA PRIMERA FASE\n");
    printf("========================================\n");

    printf("                  /\\\n");
    printf("                 /  \\\n");
    printf("                |ORION|\n");
    printf("                | SLS |\n");
    printf("                |_____|\n");
    printf("                   ||\n");
    printf("                  /\\/\\\n");
    printf("                 /\\/\\/\\\n");
    printf("                   ^^\n");
    printf("                   ^^\n");
    printf("              ACELERACION\n");
}


// SIMULACION POR EVENTOS

void ejecutarEventos(const Mision *mision) {

    int i;

    for (i = 0; i < mision->cantidadEventos; i++) {

        if (i == 0) {

            dibujarFase1();

        } else if (i == 1) {

            dibujarFase2();

        } else {

            dibujarFase3();
        }

        printf("\nEVENTO %d: %s\n", i + 1, mision->eventos[i].nombre);

        printf("Tiempo desde el despegue: %.2f s\n", mision->eventos[i].tiempo);

        printf("Altitud: %.2f m\n", mision->eventos[i].altura);

        printf("Velocidad vertical: %.2f m/s\n", mision->eventos[i].velocidad);

        printf("Aceleracion del tramo: %.2f m/s^2\n", mision->eventos[i].aceleracion);

        esperarEnter();
    }

    // REPRESENTACION DEL PUNTO 4

    dibujarFase4();

    printf("\nPUNTO 4: ACELERACION COMO MULTIPLO DE G\n");
    
    printf("Aceleracion fase 1: %.2f m/s^2\n", mision->datos.a1);

    printf("Gravedad terrestre: %.2f m/s^2\n", GRAVEDAD);

    printf("Equivalencia: %.2f g\n", mision->aceleracionEnG);

    printf("\nSIMULACION FINALIZADA.\n");
}


// REPORTE FINAL DE LA MISION

void mostrarReporte(const Mision *mision) {

    int i;

    printf("\n========================================\n");
    printf("          REPORTE FINAL SLS\n");
    printf("========================================\n");

    printf("PARAMETROS: a1=%.2f m/s^2, t1=%.2f s\n", mision->datos.a1, mision->datos.t1);

    printf("            a2=%.2f m/s^2, h=%.2f m\n", mision->datos.a2, mision->datos.alturaObjetivo);

    printf("\n1. DESACOPLE SRB\n");

    printf("Rapidez v1: %.2f m/s\n", mision->v1);

    printf("Altitud y1: %.2f m (%.2f km)\n", mision->y1, mision->y1 / 1000.0);

    printf("\n2. APAGADO DE MOTORES\n");

    printf("Rapidez v2: %.2f m/s\n", mision->v2);

    printf("Desplazamiento segunda fase: %.2f m\n", mision->deltaY);

    printf("Tiempo segunda fase: %.2f s\n", mision->t2);

    printf("\n3. ASCENSO LIBRE\n");

    printf("Tiempo adicional: %.2f s\n", mision->tiempoAscensoLibre);

    printf("Altitud maxima: %.2f m (%.2f km)\n", mision->alturaMaxima, mision->alturaMaxima / 1000.0);

    printf("\n4. ACELERACION COMO MULTIPLO DE G\n");

    printf("Aceleracion fase 1: %.2f m/s^2\n", mision->datos.a1);

    printf("Equivalencia: %.2f g\n", mision->aceleracionEnG);

    printf("\nLINEA DE EVENTOS:\n");

    for (i = 0; i < mision->cantidadEventos; i++) {

        printf("%d) %s - t=%.2f s, h=%.2f m, v=%.2f m/s\n",
               i + 1,
               mision->eventos[i].nombre,
               mision->eventos[i].tiempo,
               mision->eventos[i].altura,
               mision->eventos[i].velocidad);
    }

    printf("\nEstado: mision simulada hasta la altura maxima.\n");
    printf("Nota: modelo idealizado de MRUV, sin resistencia del aire.\n");
}


// HISTORIAL DE SIMULACIONES

void mostrarHistorial(const Mision historial[], int cantidad) {

    int i;

    if (cantidad == 0) {

        printf("\nNo hay simulaciones guardadas.\n");
        return;
    }

    printf("\n--- HISTORIAL DE SIMULACIONES ---\n");

    for (i = 0; i < cantidad; i++) {

        printf("Mision %d: a1=%.2f, t1=%.2f, a2=%.2f, h=%.2f | ",
               i + 1,
               historial[i].datos.a1,
               historial[i].datos.t1,
               historial[i].datos.a2,
               historial[i].datos.alturaObjetivo);

        printf("v2=%.2f m/s, hmax=%.2f m\n", historial[i].v2, historial[i].alturaMaxima);
    }
}


// PROGRAMA PRINCIPAL

int main(void) {

    Configuracion config;

    Mision historial[MAX_HISTORIAL];
    Mision ultima;

    int cantidad = 0;
    int hayUltima = 0;

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

        if (!leerEntero("Seleccione una opcion: ",
                        0, 5, &opcion)) {

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

                printf("ERROR: No se puede simular "
                       "con estos parametros.\n");

            } else {

                hayUltima = 1;

                // CONSERVAR SOLO LAS ULTIMAS 10 MISIONES

                if (cantidad == MAX_HISTORIAL) {

                    for (i = 1; i < MAX_HISTORIAL; i++) {
                        historial[i - 1] = historial[i];
                    }

                    cantidad--;
                }

                historial[cantidad] = ultima;
                cantidad++;

                ejecutarEventos(&ultima);
                mostrarReporte(&ultima);
            }

        } else if (opcion == 3) {

            if (hayUltima) {
                mostrarReporte(&ultima);
            } else {
                printf("Primero debe ejecutar una simulacion.\n");
            }

        } else if (opcion == 4) {

            mostrarHistorial(historial, cantidad);

        } else if (opcion == 5) {

            establecerValoresIniciales(&config);
            printf("Parametros originales restaurados.\n");
        }
    }

    return 0;
}







  

