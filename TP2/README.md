# TP 2: Calculadora de índices GINI

## Descripción
Aplicación multicapa que consulta el índice GINI de Argentina
desde la API del Banco Mundial, y procesa los datos a través
de una librería escrita en C y ensamblador x86-64.

## Arquitectura
- **Python** (`gini_fetch.py`): consulta la API REST y muestra resultados
- **C** (`gini_calc.c`): declara la función y sirve de puente
- **Ensamblador** (`gini_calc.s`): implementa la conversión float → entero y suma +1


# Ejecución

Crear el entorno virtuale e instalar dependencias:

```bash
python3 -m venv venv
source venv/bin/activate
pip install requests
```

Compilar el ensamblador y la librería de C:

```bash
nasm -f elf64 -g -o gini_calc.o gini_calc.s
gcc -g -O0 -shared -fPIC -o libgini.so gini_calc.c gini_calc.o
```

Ejecutar:

```bash
python3 gini_fetch.py
```
