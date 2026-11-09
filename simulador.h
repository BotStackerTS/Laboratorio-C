#ifndef SIMULADOR_H
#define SIMULADOR_H

#define GRAVEDAD 9.80
#define MAX_EVENTOS 3
#define MAX_HISTORIAL 10

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
    double tiempoAscensoLibre, alturaMaxima, aceleracionEnG;
    Evento eventos[MAX_EVENTOS];
    int cantidadEventos;
} Mision;

void establecerValoresIniciales(Configuracion *config);
void configurarMision(Configuracion *config);
int calcularMision(const Configuracion *config, Mision *mision);
void dibujarFase1(void);
void dibujarFase2(void);
void dibujarFase3(void);
void dibujarFase4(void);
void ejecutarEventos(const Mision *mision);
void mostrarReporte(const Mision *mision);
void mostrarHistorial(const Mision historial[], int cantidad);

#endif

