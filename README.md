# Ordenamientos secuenciales y paralelos con OpenMP

Práctica de implementación y comparación de un algoritmo de ordenamiento
iterativo y otro recursivo, cada uno en versión secuencial y paralela.

## Integrantes

- DIEGO EDUARDO SILVA MONTES
- JORGE NATANAEL CASTOLO GONZALEZ
- RICARDO DOMINGUEZ ALCALA

## Algoritmos seleccionados

- **Counting Sort:** algoritmo iterativo. La versión paralela utiliza un
  contador privado por hilo, combina los conteos y reconstruye el arreglo en
  rangos de escritura independientes.
- **Merge Sort:** algoritmo recursivo. La versión paralela divide el trabajo en
  tareas para ordenar simultáneamente ambas mitades y las mezcla solamente
  después de sincronizarlas.

Todas las implementaciones trabajan con arreglos dinámicos de enteros; no se
utiliza `vector`.

## Directivas y funciones de OpenMP

- `parallel for`: distribuye el llenado, la combinación de conteos y la
  reconstrucción de Counting Sort.
- `parallel` y `for`: crean el equipo de hilos y reparten el conteo local.
- `single`: hace que un solo hilo inicie la recursión de Merge Sort.
- `task`: crea tareas para ordenar las mitades del arreglo.
- `taskwait` y `taskgroup`: esperan las tareas antes de mezclar las mitades.
- `schedule(static)`: reparte de manera determinista las iteraciones.
- `omp_get_wtime()`: mide el llenado y los cuatro ordenamientos.

Los finales de `for`, `single` y `parallel` proporcionan las barreras implícitas
necesarias. Counting Sort no requiere `critical` ni `atomic`: cada hilo modifica
su propio contador y la reconstrucción asigna a cada iteración un intervalo
distinto del arreglo. Agregar esas directivas no respondería a una necesidad
real de sincronización.

## Requisitos

- Compilador compatible con C++17.
- OpenMP. En macOS con Homebrew: `brew install libomp`.

## Compilación y ejecución en macOS

Desde la carpeta `src`:

```bash
clang++ -std=c++17 \
  -Xpreprocessor -fopenmp \
  -Iinclude \
  -I/opt/homebrew/opt/libomp/include \
  main.cpp \
  counting_secuencial.cpp \
  counting_paralelo.cpp \
  merge_secuencial.cpp \
  merge_paralelo.cpp \
  utilidades.cpp \
  -L/opt/homebrew/opt/libomp/lib \
  -lomp \
  -o ordenamientos

./ordenamientos
```

## Configuración de las dos ejecuciones

Las constantes se encuentran al inicio de `src/main.cpp`. No hay opciones del
menú predefinidas para cambiar el tamaño: se detiene el programa, se modifican
las constantes y se vuelve a compilar, como solicita la práctica.

Primera ejecución:

```cpp
const int TAM = 100;
const int MAX_VALOR = 200;
const bool MOSTRAR_ARREGLO = true;
```

Segunda ejecución:

```cpp
const int TAM = 10000000;
const int MAX_VALOR = 2000000;
const bool MOSTRAR_ARREGLO = false;
```

En ambas ejecuciones se deben seleccionar, en orden, las opciones del menú
para llenar, ejecutar las cuatro versiones y comparar los tiempos. Cada versión
ordena una copia de los mismos datos originales; la copia y la impresión quedan
fuera del intervalo medido.

## Pruebas realizadas

El directorio `src/tests` contiene pruebas independientes para:

- Llenado paralelo y verificación del rango aleatorio.
- Counting Sort secuencial y paralelo.
- Merge Sort secuencial y paralelo.
- Comparación de las cuatro salidas usando los mismos datos.

También se verificaron las ejecuciones completas con 100 y 10,000,000 de
elementos. En ambos casos las cuatro versiones produjeron arreglos ordenados;
la ejecución grande omitió correctamente el contenido del arreglo y mostró los
tiempos y el speedup.
