# TRABAJO PRÁCTICO 1 — Rendimiento

**Nombre del grupo:** Mr. Robot  
**Integrantes:** Ferraris Gianluca, Gallone Francesco & Marredo Ezequiel  
**Materia:** Sistemas de Computación  
**Fecha:** 30/03/2026

---

## Introducción

El presente trabajo tiene como objetivo aplicar conceptos fundamentales de análisis de rendimiento en sistemas de computación mediante el uso de benchmarks estandarizados y herramientas de profiling. La evaluación de performance resulta un aspecto crítico en el diseño, selección y optimización de hardware y software, especialmente en contextos donde las cargas de trabajo son intensivas, como en machine learning, compilación de código y procesamiento de datos.

En este informe se analizan distintos benchmarks representativos y se estudia el comportamiento de procesadores modernos frente a tareas reales. Asimismo, se realiza un análisis de profiling para identificar cuellos de botella en la ejecución de programas.

---

## Metodología

La metodología adoptada consistió en seleccionar benchmarks ampliamente utilizados dentro de Open Benchmarking que representen de forma fiel las tareas habituales que realizamos con nuestro computador personal. Es por eso que priorizamos herramientas que permitan medir el rendimiento de CPU, GPU y almacenamiento, así como frameworks específicos de machine learning.

Por otro lado, empleamos, como se solicitó, profiling basado en muestreo mediante la herramienta `gprof`, con el fin de analizar la distribución temporal de la ejecución del código y detectar funciones críticas.

---

## Selección de Benchmarks

Para evaluar correctamente el rendimiento de nuestros sistemas, es necesario seleccionar benchmarks que representen fielmente las tareas reales que ejecutamos con periodicidad. Para eso, y basándonos en la página OpenBenchmarking.org, hemos seleccionado un conjunto de benchmarks para componentes de nuestro hardware, así como también para tareas de Machine Learning que realizamos dentro de nuestras PPS.

### CPU
- Compilación del kernel de Linux (Phoronix Test Suite)
- Cinebench / Geekbench

### GPU
- GLmark2
- Benchmarks de TensorFlow / CUDA
- Blender Benchmark

### Disco
- FIO
- IOZone

### Machine Learning
- llama.cpp benchmark
- TensorFlow benchmark
- PyTorch benchmark

---

## Relación entre las tareas y los benchmarks

| Tarea                    | Benchmark representativo      |
|--------------------------|-------------------------------|
| Fine-tuning de LLMs      | TensorFlow & PyTorch          |
| Inferencia de LLMs       | llama.cpp                     |
| Procesamiento de imágenes| PyTorch & CUDA                |
| Compilación de código    | Linux Kernel Compilation      |
| Uso general              | Geekbench & Cinebench         |
| Manejo de datasets       | FIO                           |
| Carga de modelos         | FIO                           |

---

## Análisis de rendimiento de las CPUs

Analizamos el benchmark *Timed Linux Kernel Compilation*, el cual mide el tiempo necesario para compilar el kernel de Linux bajo una configuración estándar. En la página dispuesta dentro del Classroom encontramos los resultados de las CPUs solicitadas:

- **Intel Core i5-13600K:** 79,5 segundos
- **AMD Ryzen 9 5900X:** 61,7 segundos
- **AMD Ryzen 9 7950X:** 51,8 segundos

Si los comparamos entre sí para ver cuál tiene mejor rendimiento relativo, obtenemos:

- **Ryzen 9 5900X vs. i5-13600K:** ~1,29× más rápido
- **Ryzen 9 7950X vs. 5900X:** ~1,19× más rápido
- **Ryzen 9 7950X vs. i5-13600K:** ~1,54× más rápido

Los resultados evidencian que el rendimiento en tareas de compilación está fuertemente influenciado por la capacidad de paralelización del procesador. En este contexto, arquitecturas con mayor cantidad de núcleos y mejor manejo de hilos presentan ventajas significativas. El Ryzen 9 7950X demuestra el mejor desempeño, seguido por el 5900X, mientras que el i5-13600K presenta un rendimiento inferior en este tipo de carga altamente paralelizable.

---

## Time Profiling

El análisis de performance del código se realizó mediante la herramienta `gprof`, la cual permite estudiar la distribución temporal de ejecución de las funciones. El perfil plano muestra el tiempo consumido por cada función de manera individual. Se observa que:

| Función     | Gianluca          | Francesco         | Ezequiel  |
|-------------|-------------------|-------------------|-----------|
| `func_1`    | 52% tiempo total  | 55% tiempo total  | 55,25%    |
| `func_2`    | 45% tiempo total  | 38% tiempo total  | 34,88%    |
| `new_func_1`| 3% tiempo total   | 7% tiempo total   | 7,10%     |
| `main`      | ~0% tiempo total  | ~0% tiempo total  | 2,78%     |

Estos resultados indican que la ejecución del programa está dominada por las dos primeras funciones. Además, el grafo de llamadas permite analizar la relación entre funciones y la propagación del tiempo de ejecución. Aquí se observa que:

- `main` invoca a `func_1` y `func_2`
- `func_1` invoca a `new_func_1`
- `func_2` no presenta llamadas a otras funciones

Este análisis permite comprender la estructura del programa y la dependencia entre sus componentes.

Como conclusión final, el profiling evidencia que el tiempo de ejecución no se distribuye uniformemente, sino que se concentra en funciones específicas. Esto permite identificar cuellos de botella y orientar los esfuerzos de optimización hacia las funciones más costosas.

---

## Benchmark en ESP32

Otra práctica realizada fue analizar cómo la frecuencia del clock de un microprocesador determina el tiempo de ejecución de un código. Para ello, se utilizó un microcontrolador ESP32 en el cual se puede configurar la frecuencia del clock de instrucciones, de forma que se pueden evaluar los resultados con un pequeño código (el mismo será adjuntado en el repositorio del trabajo).

| Frecuencia de clock | Tiempo de ejecución |
|---------------------|---------------------|
| 80 MHz              | 9,906 segundos      |
| 160 MHz             | 4,952 segundos      |
| 240 MHz             | 3,303 segundos      |

La primera prueba se realizó con una frecuencia de clock de 80 MHz, dando como resultado un tiempo total de ejecución de 9,906 segundos.

En la segunda prueba se duplicó la frecuencia de trabajo a 160 MHz y el resultado fue equivalente al esperado: se redujo a la mitad el tiempo de ejecución, siendo este de 4,952 segundos.

Por último, se realizó una tercera prueba en la que se aumentó la frecuencia a 240 MHz, y el tiempo resultante se redujo a 3,303 segundos.
