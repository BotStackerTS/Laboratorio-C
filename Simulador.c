#include <stdio.h>
#include <math.h>
#include "simulador.h"
#include "validaciones.h"

void establecerValoresIniciales(Configuracion *config) {
    config->a1 = 20.0;
    config->t1 = 120.0;
    config->a2 = 12.5;
    config->alturaObjetivo = 160000.0;
}

void configurarMision(Configuracion *config) {
    Configuracion nueva = *config;
    double alturaPrimeraFase, alturaIngresada, defectoAltura;

    printf("\n--- CONFIGURACION DE LA MISION ---\n");
    printf("Presione Enter para conservar el valor mostrado.\n");
    if (!leerNumero("Aceleracion primera fase (m/s^2)",
                    nueva.a1, 0.01, 1000.0, &nueva.a1)) return;
    if (!leerNumero("Tiempo desacople SRB (s)",
                    nueva.t1, 0.01, 10000.0, &nueva.t1)) return;
    if (!leerNumero("Aceleracion segunda fase (m/s^2)",
                    nueva.a2, 0.01, 1000.0, &nueva.a2)) return;

    alturaPrimeraFase = 0.5 * nueva.a1 * nueva.t1 * nueva.t1;
    defectoAltura = nueva.alturaObjetivo;
    if (defectoAltura <= alturaPrimeraFase)
        defectoAltura = alturaPrimeraFase + 1000.0;

    do {
        if (!leerNumero("Altura objetivo (m)", defectoAltura,
                        0.01, 1000000000000.0, &alturaIngresada)) return;
        if (alturaIngresada <= alturaPrimeraFase) {
            printf("ERROR: La altura debe superar %.2f m, alcanzados en la fase 1.\n",
                   alturaPrimeraFase);
        }
    } while (alturaIngresada <= alturaPrimeraFase);

    nueva.alturaObjetivo = alturaIngresada;
    *config = nueva;
    printf("Configuracion guardada.\n");
}

int calcularMision(const Configuracion *config, Mision *mision) {
    double discriminante;
    if (config->a1 <= 0 || config->a1 > 1000 ||
        config->t1 <= 0 || config->t1 > 10000 ||
        config->a2 <= 0 || config->a2 > 1000 ||
        config->alturaObjetivo <= 0 || config->alturaObjetivo > 1e12) return 0;

    mision->datos = *config;
    mision->v1 = config->a1 * config->t1;
    mision->y1 = 0.5 * config->a1 * config->t1 * config->t1;
    mision->deltaY = config->alturaObjetivo - mision->y1;
    if (mision->deltaY <= 0) return 0;

    discriminante = mision->v1 * mision->v1 + 2.0 * config->a2 * mision->deltaY;
    if (!(discriminante > 0)) return 0;
    mision->v2 = sqrt(discriminante);
    mision->t2 = 2.0 * mision->deltaY / (mision->v1 + mision->v2);
    mision->tiempoAscensoLibre = mision->v2 / GRAVEDAD;
    mision->alturaMaxima = config->alturaObjetivo +
                          mision->v2 * mision->v2 / (2.0 * GRAVEDAD);
    mision->aceleracionEnG = config->a1 / GRAVEDAD;
    mision->cantidadEventos = 3;

    snprintf(mision->eventos[0].nombre, 45, "Desacople de los SRB");
    mision->eventos[0].tiempo = config->t1;
    mision->eventos[0].altura = mision->y1;
    mision->eventos[0].velocidad = mision->v1;
    mision->eventos[0].aceleracion = config->a1;

    snprintf(mision->eventos[1].nombre, 45, "Apagado de motores");
    mision->eventos[1].tiempo = config->t1 + mision->t2;
    mision->eventos[1].altura = config->alturaObjetivo;
    mision->eventos[1].velocidad = mision->v2;
    mision->eventos[1].aceleracion = config->a2;

    snprintf(mision->eventos[2].nombre, 45, "Altura maxima alcanzada");
    mision->eventos[2].tiempo = config->t1 + mision->t2 + mision->tiempoAscensoLibre;
    mision->eventos[2].altura = mision->alturaMaxima;
    mision->eventos[2].velocidad = 0.0;
    mision->eventos[2].aceleracion = -GRAVEDAD;
    return 1;
}

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

void ejecutarEventos(const Mision *mision) {
    int i;
    for (i = 0; i < mision->cantidadEventos; i++) {
        if (i == 0) dibujarFase1();
        else if (i == 1) dibujarFase2();
        else dibujarFase3();

        printf("\nEVENTO %d: %s\n", i + 1, mision->eventos[i].nombre);
        printf("Tiempo desde el despegue: %.2f s\n", mision->eventos[i].tiempo);
        printf("Altitud: %.2f m\n", mision->eventos[i].altura);
        printf("Velocidad vertical: %.2f m/s\n", mision->eventos[i].velocidad);
        printf("Aceleracion del tramo: %.2f m/s^2\n", mision->eventos[i].aceleracion);
        esperarEnter();
    }
    dibujarFase4();
    printf("\nPUNTO 4: ACELERACION COMO MULTIPLO DE G\n");
    printf("Aceleracion fase 1: %.2f m/s^2\n", mision->datos.a1);
    printf("Gravedad terrestre: %.2f m/s^2\n", GRAVEDAD);
    printf("Equivalencia: %.2f g\n", mision->aceleracionEnG);
    printf("\nSIMULACION FINALIZADA.\n");
}

void mostrarReporte(const Mision *mision) {
    int i;
    printf("\n========================================\n");
    printf("          REPORTE FINAL SLS\n");
    printf("========================================\n");
    printf("PARAMETROS: a1=%.2f m/s^2, t1=%.2f s\n",
           mision->datos.a1, mision->datos.t1);
    printf("            a2=%.2f m/s^2, h=%.2f m\n",
           mision->datos.a2, mision->datos.alturaObjetivo);
    printf("\n1. DESACOPLE SRB\n");
    printf("Rapidez v1: %.2f m/s\n", mision->v1);
    printf("Altitud y1: %.2f m (%.2f km)\n", mision->y1, mision->y1 / 1000.0);
    printf("\n2. APAGADO DE MOTORES\n");
    printf("Rapidez v2: %.2f m/s\n", mision->v2);
    printf("Desplazamiento segunda fase: %.2f m\n", mision->deltaY);
    printf("Tiempo segunda fase: %.2f s\n", mision->t2);
    printf("\n3. ASCENSO LIBRE\n");
    printf("Tiempo adicional: %.2f s\n", mision->tiempoAscensoLibre);
    printf("Altitud maxima: %.2f m (%.2f km)\n",
           mision->alturaMaxima, mision->alturaMaxima / 1000.0);
    printf("\n4. ACELERACION COMO MULTIPLO DE G\n");
    printf("Aceleracion fase 1: %.2f m/s^2\n", mision->datos.a1);
    printf("Equivalencia: %.2f g\n", mision->aceleracionEnG);
    printf("\nLINEA DE EVENTOS:\n");
    for (i = 0; i < mision->cantidadEventos; i++) {
        printf("%d) %s - t=%.2f s, h=%.2f m, v=%.2f m/s\n",
               i + 1, mision->eventos[i].nombre,
               mision->eventos[i].tiempo, mision->eventos[i].altura,
               mision->eventos[i].velocidad);
    }
    printf("\nEstado: mision simulada hasta la altura maxima.\n");
    printf("Nota: modelo idealizado de MRUV, sin resistencia del aire.\n");
}

void mostrarHistorial(const Mision historial[], int cantidad) {
    int i;
    if (cantidad == 0) {
        printf("\nNo hay simulaciones guardadas.\n");
        return;
    }
    printf("\n--- HISTORIAL DE SIMULACIONES ---\n");
    for (i = 0; i < cantidad; i++) {
        printf("Mision %d: a1=%.2f, t1=%.2f, a2=%.2f, h=%.2f | ",
               i + 1, historial[i].datos.a1, historial[i].datos.t1,
               historial[i].datos.a2, historial[i].datos.alturaObjetivo);
        printf("v2=%.2f m/s, hmax=%.2f m\n",
               historial[i].v2, historial[i].alturaMaxima);
    }
}

