#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

#include "utilidades.h"

using namespace std;


// ==========================================
// LLENADO PARALELO
// ==========================================

void llenarArregloParalelo(
    int* arreglo,
    int n,
    int maxValor
)
{
    if (arreglo == nullptr || n <= 0)
        return;

    int numHilos = omp_get_max_threads();

    // Cada hilo tendrá su propia semilla.
    unsigned int* semillas =
        new unsigned int[numHilos];

    unsigned int semillaBase =
        static_cast<unsigned int>(time(nullptr));

    for (int i = 0; i < numHilos; i++)
    {
        semillas[i] =
            semillaBase + (i * 1009);
    }

    // ======================================
    // LLENADO DISTRIBUIDO ENTRE LOS HILOS
    // ======================================

    #pragma omp parallel for schedule(static)
    for (int i = 0; i < n; i++)
    {
        int idHilo =
            omp_get_thread_num();

        arreglo[i] =
            rand_r(&semillas[idHilo])
            % (maxValor + 1);
    }

    delete[] semillas;
}


// ==========================================
// MOSTRAR ARREGLO
// ==========================================

void mostrarArreglo(
    const int* arreglo,
    int n
)
{
    if (arreglo == nullptr)
        return;

    for (int i = 0; i < n; i++)
    {
        cout << arreglo[i] << " ";
    }

    cout << endl;
}


// ==========================================
// COPIAR ARREGLO
// ==========================================

void copiarArreglo(
    const int* origen,
    int* destino,
    int n
)
{
    if (origen == nullptr ||
        destino == nullptr)
    {
        return;
    }

    for (int i = 0; i < n; i++)
    {
        destino[i] = origen[i];
    }
}


// ==========================================
// COMPROBAR SI ESTÁ ORDENADO
// ==========================================

bool estaOrdenado(
    const int* arreglo,
    int n
)
{
    if (arreglo == nullptr)
        return false;

    for (int i = 1; i < n; i++)
    {
        if (arreglo[i - 1] > arreglo[i])
        {
            return false;
        }
    }

    return true;
}


// ==========================================
// COMPARAR DOS ARREGLOS
// ==========================================

bool arreglosIguales(
    const int* arreglo1,
    const int* arreglo2,
    int n
)
{
    if (arreglo1 == nullptr ||
        arreglo2 == nullptr)
    {
        return false;
    }

    for (int i = 0; i < n; i++)
    {
        if (arreglo1[i] != arreglo2[i])
        {
            return false;
        }
    }

    return true;
}