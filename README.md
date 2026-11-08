# Simulador Artemis — Ascenso y Propulsión del SLS

  Universidad: UTN — Facultad Regional Resistencia
  
  Materia: Algoritmos y Estructuras de Datos
  
  Trabajo: Trabajo Final Integrador en C
  
  Situación: 1 — Ascenso y Propulsión del SLS
  
  Equipo: Root7 (D16)
  
  Comisión: K1.4
  
  Integrantes: 
  
  - Eiden, Aldana
  - Halier, Fiorella Estefania
  - Maciel, Julieta Andrea
  - Sosa, Tomas      
  - Schiaffino, Danilo Jesus
    

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
  - Configurar parámetros de la misión (opción 1)
  - Iniciar simulación por eventos (opción 2)
  - Ver reporte de la última misión (opción 3)
  - Consultar historial de simulaciones (opción 4)
  - Restaurar valores iniciales (opción 5)
  - Salir (opción 0).

Durante la simulación se muestran los eventos de desacople de SRB, apagado de motores y altura máxima, acompañados por dibujos en consola realizados con printf().


# 4. Estructuras y recursos utilizados 

Para desarrollar el simulador se aplicaron los siguientes contenidos de Algoritmo y Estructuras de Datos, utilizando el lenguaje C.

- Tipos de datos variables: utilización de int, double y char para almacenar parámetros, resultados y opciones del programa.
- Constantes: definición de valores fijos mediante #define, como la gravedad terrestre y los tamaños máximos de los arreglos.
-  Operadores aritméticos, relacionales y lógicos: implementación de las ecuaciones del MRUV y comparación de valores para validar condiciones.
-  Estructuras secuenciales: ejecución ordenada de instrucciones para calcular las distintas etapas del ascenso.
-  Estructuras condicionales: utilización de if y else para controlar el menú, las validaciones y la decisiónes del simulador.
-  Estructuras repetitivas: utilización de while, do while y for para repetir el menú, solicitar datos correctos y recorrer arreglos.
-  Funciones y procedimientos: modularización lógica del programa para separar la lectura de datos, los cálculos físicos, los dibujos y la presentación de resultados.
-  Parámetros y paso por referencia: utilización de punteros para modificar configuraciones y devolver resultados desde las funciones.
-  Arreglos unidimensionales: almacenamiento de los eventos de cada misión y del historial de hasta diez simulaciones.
-  Registros y estructuras (struct): organización de los datos mediante las estructuras Configuración, Evento y Misión.
-  Punteros: acceso a los datos de las estructuras mediante operadores como &, * y ->.
-  Cadenas de caracteres: almacenamiento de los nombres de los aventos y procesamientos de las entradas del usuario.
-  Validación de datos: utilización de print(), fgets() y sscanf() para interactuar con el usuario.
-  Bibliotecas estandar: uso de stdio.h para entrada y salida, y math.h para cálculos matemáticos mediante sqrt().


# 5. Compilación y ejecución

El programa fue desarrollado en lenguaje C y actualmente se encuentra integrado en un único archivo main.c.

Para compilar el programa utilizando GCC:

- gcc main.c -o simulados_sls -1m

Para ejecutarlos en Windows: 

- .\simulador_sls.exe


# 6. Pruebas y Validaciones

Con los valores originales del enunciado se obtienen los siguientes resultados:

Rapidez al desacople = 2400,00 m/s

Altura al desacople = 144.000,00 m

Rapidez al apagado de motores = 2481,93 m/s

Altura máxima = 474.284,71 m

Aceleración en múltiplos de g = 2,04 g

El programa contempla la validación de entradas no numéricas, valores fuera de rango, alturas objetivos compatibles y opciones incorrectas del menú.


# 7. Uso de Inteligencia Artificial

Se utilizó ChatGPT (OpenIA) como herramienta de apoyo durante el desarrollo del proyecto.

Consultas y tareas realizadas:

 - Revisión de fórmulas y cálculos físicos del MRUV.
 - Corrección de errores y sugerencias para mejorar las validaciones.
 - Incorporación de dibujos en consola mediante printf().
 - Ayuda en el diseño de las representaciones gráficas.

Algunas de las preguntas para la IA fueron las siguientes:

  ¿Cómo se puede evitar que el código acepte valores negativos, letras o alturas que no sean compatibles con la simulación?
  
  ¿Cómo hago para que el código permita que el usuario vuelva a ingresar un dato cuando comete un error, sin que el programa se cierre?
  
  ¿Cómo se puede incorporar figuras al programa sin modificar las fórmulas ni los resultados?
  
  ¿Cómo puedo hacer para incorporar representaciones gráficas en un código en lenguaje C?
  
  ¿Cómo se pueden utilizar caracteres y símbolos para crear representaciones visuales claras y comprensibles?

Supervisión y verificación del equipo:

Cada vez que se utilizó la inteligencia artificial como herramienta de apoyo, las respuestas y sugerencias obtenidas fueron revisadas por los integrantes del equipo, comparando la información con los materiales proporcionados por la cátedra.
De esta forma buscamos garantizar que las modificaciones fueran correctas y acordes con los contenidos estudiados.


# 8. Conclusión

El desarrollo del simulador SLS permitió integrar los conocimientos adquiridos en la cátedra de Algoritmos y Estructuras de Datos con la resolución de una situación problemática basada en el Movimiento Rectilíneo Uniformemente Variado (MRUV).

A lo largo del TFI aplicamos distintos recursos del lenguaje C, como funciones, estructuras de control, arreglos, registros y punteros, para organizar la información y realizar los cálculos correspondientes a las etapas del ascenso.

Además, la incorporación de validaciones, un menú interactivo, simulación por eventos y representaciones visuales en consola permitió mejorar el funcionamiento del programa y facilitar la interpretación de los resultados.

Este trabajo nos permitió llevar los conceptos teóricos a una aplicación práctica, fortalecer nuestras habilidades de programación, resolución de problemas y organización del código, y comprender la importancia de desarrollar soluciones claras, funcionales y verificables.

