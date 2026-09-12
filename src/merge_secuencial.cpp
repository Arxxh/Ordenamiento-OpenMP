#include "merge_sort.h"


// ==========================================
// MEZCLAR DOS PARTES ORDENADAS
// ==========================================

static void mezclar(
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

    // Copiar elementos restantes de la izquierda.
    while (izquierda <= medio)
    {
        auxiliar[posicion - base] =
            arreglo[izquierda];

        izquierda++;
        posicion++;
    }

    // Copiar elementos restantes de la derecha.
    while (derecha <= fin)
    {
        auxiliar[posicion - base] =
            arreglo[derecha];

        derecha++;
        posicion++;
    }

    // Regresar los datos ordenados al arreglo original.
    for (int i = inicio; i <= fin; i++)
    {
        arreglo[i] =
            auxiliar[i - base];
    }
}


// ==========================================
// MERGE SORT RECURSIVO
// ==========================================

static void mergeSortRecursivo(
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

    mergeSortRecursivo(
        arreglo,
        auxiliar,
        base,
        inicio,
        medio
    );

    mergeSortRecursivo(
        arreglo,
        auxiliar,
        base,
        medio + 1,
        fin
    );

    mezclar(
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

void mergeSortSecuencial(
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

    mergeSortRecursivo(
        arreglo,
        auxiliar,
        inicio,
        inicio,
        fin
    );

    delete[] auxiliar;
}