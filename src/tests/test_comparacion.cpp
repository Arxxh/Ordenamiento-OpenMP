#include <iostream>
#include <omp.h>

#include "counting_sort.h"
#include "merge_sort.h"
#include "utilidades.h"

using namespace std;

int main()
{
    const int TAM = 100;
    const int MAX_VALOR = 200;

    // ======================================
    // ARREGLOS DINÁMICOS
    // ======================================

    int* original = new int[TAM];

    int* countingSec = new int[TAM];
    int* countingPar = new int[TAM];

    int* mergeSec = new int[TAM];
    int* mergePar = new int[TAM];

    cout << "========================================" << endl;
    cout << " TEST COMPARACION DE ALGORITMOS" << endl;
    cout << "========================================" << endl;

    // ======================================
    // LLENAR ARREGLO ORIGINAL
    // ======================================

    llenarArregloParalelo(
        original,
        TAM,
        MAX_VALOR
    );

    cout << "\nArreglo original:" << endl;

    mostrarArreglo(
        original,
        TAM
    );

    // ======================================
    // COPIAR LOS MISMOS DATOS
    // ======================================

    copiarArreglo(
        original,
        countingSec,
        TAM
    );

    copiarArreglo(
        original,
        countingPar,
        TAM
    );

    copiarArreglo(
        original,
        mergeSec,
        TAM
    );

    copiarArreglo(
        original,
        mergePar,
        TAM
    );

    // ======================================
    // COUNTING SORT SECUENCIAL
    // ======================================

    double inicio = omp_get_wtime();

    countingSortSecuencial(
        countingSec,
        TAM,
        MAX_VALOR
    );

    double fin = omp_get_wtime();

    double tiempoCountingSec =
        fin - inicio;

    // ======================================
    // COUNTING SORT PARALELO
    // ======================================

    inicio = omp_get_wtime();

    countingSortParalelo(
        countingPar,
        TAM,
        MAX_VALOR
    );

    fin = omp_get_wtime();

    double tiempoCountingPar =
        fin - inicio;

    // ======================================
    // MERGE SORT SECUENCIAL
    // ======================================

    inicio = omp_get_wtime();

    mergeSortSecuencial(
        mergeSec,
        0,
        TAM - 1
    );

    fin = omp_get_wtime();

    double tiempoMergeSec =
        fin - inicio;

    // ======================================
    // MERGE SORT PARALELO
    // ======================================

    inicio = omp_get_wtime();

    mergeSortParalelo(
        mergePar,
        0,
        TAM - 1
    );

    fin = omp_get_wtime();

    double tiempoMergePar =
        fin - inicio;

    // ======================================
    // MOSTRAR RESULTADOS
    // ======================================

    cout << "\nCounting Sort Secuencial:" << endl;
    mostrarArreglo(countingSec, TAM);

    cout << "\nCounting Sort Paralelo:" << endl;
    mostrarArreglo(countingPar, TAM);

    cout << "\nMerge Sort Secuencial:" << endl;
    mostrarArreglo(mergeSec, TAM);

    cout << "\nMerge Sort Paralelo:" << endl;
    mostrarArreglo(mergePar, TAM);

    // ======================================
    // VERIFICAR ORDENAMIENTO
    // ======================================

    cout << "\n========================================" << endl;
    cout << " VERIFICACION" << endl;
    cout << "========================================" << endl;

    cout << "\nCounting Secuencial: "
         << (estaOrdenado(countingSec, TAM)
             ? "CORRECTO"
             : "ERROR")
         << endl;

    cout << "Counting Paralelo:   "
         << (estaOrdenado(countingPar, TAM)
             ? "CORRECTO"
             : "ERROR")
         << endl;

    cout << "Merge Secuencial:    "
         << (estaOrdenado(mergeSec, TAM)
             ? "CORRECTO"
             : "ERROR")
         << endl;

    cout << "Merge Paralelo:      "
         << (estaOrdenado(mergePar, TAM)
             ? "CORRECTO"
             : "ERROR")
         << endl;

    // ======================================
    // COMPARAR RESULTADOS
    // ======================================

    bool iguales =
        arreglosIguales(
            countingSec,
            countingPar,
            TAM
        )
        &&
        arreglosIguales(
            countingSec,
            mergeSec,
            TAM
        )
        &&
        arreglosIguales(
            countingSec,
            mergePar,
            TAM
        );

    cout << "\nTodos producen el mismo resultado: ";

    if (iguales)
    {
        cout << "SI" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }

    // ======================================
    // MOSTRAR TIEMPOS
    // ======================================

    cout << "\n========================================" << endl;
    cout << " TIEMPOS" << endl;
    cout << "========================================" << endl;

    cout << "\nCounting Secuencial: "
         << tiempoCountingSec
         << " segundos"
         << endl;

    cout << "Counting Paralelo:   "
         << tiempoCountingPar
         << " segundos"
         << endl;

    cout << "Merge Secuencial:    "
         << tiempoMergeSec
         << " segundos"
         << endl;

    cout << "Merge Paralelo:      "
         << tiempoMergePar
         << " segundos"
         << endl;

    // ======================================
    // LIBERAR MEMORIA
    // ======================================

    delete[] original;

    delete[] countingSec;
    delete[] countingPar;

    delete[] mergeSec;
    delete[] mergePar;

    return 0;
}