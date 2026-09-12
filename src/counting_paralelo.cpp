#include <omp.h>
#include <cstddef>

#include "counting_sort.h"

void countingSortParalelo(int* arreglo, int n, int maxValor)
{
    if (arreglo == nullptr || n <= 1)
        return;

    int numHilos = omp_get_max_threads();

    std::size_t rango =
        static_cast<std::size_t>(maxValor) + 1;

    // Cada hilo tendrá su propio contador.
    int* conteosLocales =
        new int[rango * numHilos]();

    // ==========================================
    // FASE 1: CONTEO PARALELO
    // ==========================================

    #pragma omp parallel
    {
        int idHilo = omp_get_thread_num();

        int* conteoLocal =
            conteosLocales + (idHilo * rango);

        #pragma omp for
        for (int i = 0; i < n; i++)
        {
            conteoLocal[arreglo[i]]++;
        }
    }

    // ==========================================
    // FASE 2: COMBINAR CONTEOS
    // ==========================================

    int* conteoGlobal =
        new int[rango]();

    #pragma omp parallel for
    for (int valor = 0; valor <= maxValor; valor++)
    {
        int total = 0;

        for (int hilo = 0; hilo < numHilos; hilo++)
        {
            total += conteosLocales[
                static_cast<std::size_t>(hilo) * rango
                + valor
            ];
        }

        conteoGlobal[valor] = total;
    }

    // ==========================================
    // FASE 3: CALCULAR POSICIONES
    // ==========================================

    long long* posiciones =
        new long long[rango];

    long long posicionActual = 0;

    for (int valor = 0; valor <= maxValor; valor++)
    {
        posiciones[valor] = posicionActual;

        posicionActual += conteoGlobal[valor];
    }

    // ==========================================
    // FASE 4: RECONSTRUIR EN PARALELO
    // ==========================================

    #pragma omp parallel for schedule(static)
    for (int valor = 0; valor <= maxValor; valor++)
    {
        long long inicio = posiciones[valor];

        int cantidad = conteoGlobal[valor];

        for (int j = 0; j < cantidad; j++)
        {
            arreglo[inicio + j] = valor;
        }
    }

    delete[] posiciones;
    delete[] conteoGlobal;
    delete[] conteosLocales;
}