#include <iostream>
#include <omp.h>

#include "utilidades.h"

using namespace std;

int main()
{
    const int TAM = 100;
    const int MAX_VALOR = 200;

    // ======================================
    // ARREGLO DINÁMICO
    // ======================================

    int* arreglo =
        new int[TAM];

    cout << "======================================" << endl;
    cout << " TEST LLENADO PARALELO" << endl;
    cout << "======================================" << endl;

    cout << "\nElementos: "
         << TAM
         << endl;

    cout << "Rango: 0 - "
         << MAX_VALOR
         << endl;

    cout << "Hilos disponibles: "
         << omp_get_max_threads()
         << endl;

    // ======================================
    // MEDIR LLENADO
    // ======================================

    double inicio =
        omp_get_wtime();

    llenarArregloParalelo(
        arreglo,
        TAM,
        MAX_VALOR
    );

    double fin =
        omp_get_wtime();

    double tiempo =
        fin - inicio;

    // ======================================
    // MOSTRAR RESULTADO
    // ======================================

    cout << "\nArreglo generado:" << endl;

    mostrarArreglo(
        arreglo,
        TAM
    );

    cout << "\nTiempo de llenado: "
         << tiempo
         << " segundos"
         << endl;

    // ======================================
    // VERIFICAR RANGO
    // ======================================

    bool rangoCorrecto = true;

    for (int i = 0; i < TAM; i++)
    {
        if (arreglo[i] < 0 ||
            arreglo[i] > MAX_VALOR)
        {
            rangoCorrecto = false;
            break;
        }
    }

    cout << "\nVerificacion del rango: ";

    if (rangoCorrecto)
    {
        cout << "CORRECTO" << endl;
    }
    else
    {
        cout << "ERROR" << endl;
    }

    // ======================================
    // LIBERAR MEMORIA
    // ======================================

    delete[] arreglo;

    return 0;
}