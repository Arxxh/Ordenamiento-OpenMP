#include <omp.h>

#include "merge_sort.h"


// Tamaño mínimo para seguir creando tareas.
//
// Si la sección es menor a este tamaño,
// se continúa de manera secuencial.
static const int UMBRAL_TAREA = 50000;


// ==========================================
// MEZCLAR
// ==========================================

static void mezclarParalelo(
    int* arreglo,
    int* auxiliar,
    int base,
    int inicio,
    int medio,
    int fin
)
{
    int izquierda = inicio;
    int derecha = medio + 1;
    int posicion = inicio;

    while (izquierda <= medio &&
           derecha <= fin)
    {
        if (arreglo[izquierda] <= arreglo[derecha])
        {
            auxiliar[posicion - base] =
                arreglo[izquierda];

            izquierda++;
        }
        else
        {
            auxiliar[posicion - base] =
                arreglo[derecha];

            derecha++;
        }

        posicion++;
    }

    while (izquierda <= medio)
    {
        auxiliar[posicion - base] =
            arreglo[izquierda];

        izquierda++;
        posicion++;
    }

    while (derecha <= fin)
    {
        auxiliar[posicion - base] =
            arreglo[derecha];

        derecha++;
        posicion++;
    }

    for (int i = inicio; i <= fin; i++)
    {
        arreglo[i] =
            auxiliar[i - base];
    }
}


// ==========================================
// VERSIÓN SECUENCIAL INTERNA
//
// Se utiliza cuando una sección ya es
// demasiado pequeña para justificar
// nuevas tareas.
// ==========================================

static void mergeSortInternoSecuencial(
    int* arreglo,
    int* auxiliar,
    int base,
    int inicio,
    int fin
)
{
    if (inicio >= fin)
        return;

    int medio =
        inicio + (fin - inicio) / 2;

    mergeSortInternoSecuencial(
        arreglo,
        auxiliar,
        base,
        inicio,
        medio
    );

    mergeSortInternoSecuencial(
        arreglo,
        auxiliar,
        base,
        medio + 1,
        fin
    );

    mezclarParalelo(
        arreglo,
        auxiliar,
        base,
        inicio,
        medio,
        fin
    );
}


// ==========================================
// MERGE SORT CON TAREAS
// ==========================================

static void mergeSortTareas(
    int* arreglo,
    int* auxiliar,
    int base,
    int inicio,
    int fin
)
{
    if (inicio >= fin)
        return;

    int cantidad =
        fin - inicio + 1;

    // Si el problema ya es pequeño,
    // dejamos de generar tareas.
    if (cantidad <= UMBRAL_TAREA)
    {
        mergeSortInternoSecuencial(
            arreglo,
            auxiliar,
            base,
            inicio,
            fin
        );

        return;
    }

    int medio =
        inicio + (fin - inicio) / 2;

    // taskgroup garantiza que todas las tareas
    // pertenecientes al grupo hayan terminado.
    #pragma omp taskgroup
    {
        // Ordenar mitad izquierda.
        #pragma omp task shared(arreglo, auxiliar) \
        firstprivate(base, inicio, medio)
        {
            mergeSortTareas(
                arreglo,
                auxiliar,
                base,
                inicio,
                medio
            );
        }

        // Ordenar mitad derecha.
        #pragma omp task shared(arreglo, auxiliar) \
        firstprivate(base, medio, fin)
        {
            mergeSortTareas(
                arreglo,
                auxiliar,
                base,
                medio + 1,
                fin
            );
        }

        // Esperar a las tareas antes de continuar.
        #pragma omp taskwait
    }

    // Las dos mitades ya están ordenadas.
    // Ahora sí podemos mezclarlas.
    mezclarParalelo(
        arreglo,
        auxiliar,
        base,
        inicio,
        medio,
        fin
    );
}


// ==========================================
// FUNCIÓN PÚBLICA
// ==========================================

void mergeSortParalelo(
    int* arreglo,
    int inicio,
    int fin
)
{
    if (arreglo == nullptr ||
        inicio >= fin)
    {
        return;
    }

    int cantidad =
        fin - inicio + 1;

    int* auxiliar =
        new int[cantidad];

    #pragma omp parallel
    {
        // Solo un hilo inicia la recursión.
        //
        // Después las tareas se distribuyen
        // entre los hilos disponibles.
        #pragma omp single
        {
            mergeSortTareas(
                arreglo,
                auxiliar,
                inicio,
                inicio,
                fin
            );
        }
    }

    delete[] auxiliar;
}