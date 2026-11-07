# Simulador Artemis — Ascenso y Propulsión del SLS

  Universidad: UTN — Facultad Regional Resistencia
  
  Materia: Algoritmos y Estructuras de Datos
  
  Trabajo: Trabajo Final Integrador en C
  
  Situación: 1 — Ascenso y Propulsión del SLS
  
  Equipo: Root7 (D16)
  
  Comisión: K1.4
  
  Integrantes: 
      Halier, Fiorella Estefania
      

# 1. Descripción del TFI 

El Trabajo Práctico Integrador consiste en desarrollar un simulador interactivo en lenguaje C que representa el ascenso vertical del cohete Space Launch System (SLS), encargado de transportar la nave Orion.

Utilizamos ecuaciones del Movimiento Rectilíneo Uniformemente Variado (MRUV) para analizar tres etapas: despegue y desacople de los SRB, ascenso con el motor principal y ascenso libre hasta alcanzar la altura máxima.

El simulador permite modificar parámetros, visualizar eventos, consultar resultados y almacenar un historial de hasta diez misiones.

# 2. Análisis de la situación problemática

Se parte de las siguientes condiciones iniciales:

Velocidad inicial (v0) = 0 m/s
Altura inicial (y0)  = 0 m
Aceleración inicial (a1) =  20 m/s²
Tiempo de desacople (t1) = 120 s
Aceleración segunda fase (a2) = 12,5 m/s²
Altura objetivo (h) = 160.000 m
Gravedad (g) = 9,80 m/s²
El programa responde cuatro preguntas:

1. Velocidad y altura al desacople de los SRB

Aplicamos las siguientes ecuaciones:
v1 = v0 + a1 * t1
y1 = y0 + v0 * t1 + 0.5 * a1 * t1²

2. Velocidad al apagar los motores

Primero se calcula el desplazamiento pendiente:
deltaY = h - y1
Luego se obtiene la velocidad:
v2 = sqrt(v1² + 2 * a2 * deltaY)

3. Altura máxima durante el ascenso libre

Después del apagado de motores, la gravedad disminuye la velocidad ascendente hasta cero.
tiempoAscensoLibre = v2 / g
hMax = h + v2² / (2 * g)

4. Aceleración como múltiplo de la gravedad

aceleracionEnG = a1 / g


# 3. Funcionamiento del programa

El simulador tiene el siguiente menú interactivo:

Configurar parámetros de la misión.
Iniciar simulación por eventos.
Ver reporte de la última misión.
Consultar historial de simulaciones.
Restaurar valores iniciales.
Salir (opción 0).

Durante la simulación se muestran los eventos de desacople de SRB, apagado de motores y altura máxima, acompañados por dibujos en consola realizados con printf().
