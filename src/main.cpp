#include <iostream>
#include <iomanip>
#include <omp.h>

#include "counting_sort.h"
#include "merge_sort.h"
#include "utilidades.h"

using namespace std;


// ==========================================
// CONFIGURACION DE LA EJECUCION
// ==========================================

// PRIMERA EJECUCION
const int TAM = 10000000; // 100 y 10,000,000
const int MAX_VALOR = 2000000; // 200 y 2,000,000
const bool MOSTRAR_ARREGLO = false; // sin mostrar el contenido o mostrar el contenido
 

/*
SEGUNDA EJECUCION

Cuando terminemos la prueba de 100 elementos,
detener el programa y cambiar las constantes por:

const int TAM = 10000000;
const int MAX_VALOR = 2000000;
const bool MOSTRAR_ARREGLO = false;

*/


int main()
{
    int opcion;

    bool arregloLleno = false;

    // Arreglo original.
    int* original = new int[TAM];

    // Arreglo que usaremos para cada ordenamiento.
    int* trabajo = new int[TAM];


    // ======================================
    // TIEMPOS
    // ======================================

    double tiempoLlenado = 0.0;

    double tiempoCountingSec = 0.0;
    double tiempoCountingPar = 0.0;

    double tiempoMergeSec = 0.0;
    double tiempoMergePar = 0.0;


    // Saber si ya se ejecutaron los algoritmos.
    bool ejecutadoCountingSec = false;
    bool ejecutadoCountingPar = false;

    bool ejecutadoMergeSec = false;
    bool ejecutadoMergePar = false;


    do
    {
        cout << "\n";
        cout << "==========================================" << endl;
        cout << "      ORDENAMIENTOS CON OPENMP" << endl;
        cout << "==========================================" << endl;

        cout << "Elementos: " << TAM << endl;
        cout << "Rango: 0 - " << MAX_VALOR << endl;
        cout << "Hilos disponibles: "
             << omp_get_max_threads()
             << endl;

        cout << "==========================================" << endl;

        cout << "1. Llenar arreglo" << endl;
        cout << "2. Mostrar arreglo original" << endl;

        cout << "3. Counting Sort secuencial" << endl;
        cout << "4. Counting Sort paralelo" << endl;

        cout << "5. Merge Sort secuencial" << endl;
        cout << "6. Merge Sort paralelo" << endl;

        cout << "7. Comparar tiempos" << endl;
        cout << "8. Salir" << endl;

        cout << "==========================================" << endl;

        cout << "Seleccione una opcion: ";
        cin >> opcion;

        cout << endl;


        switch (opcion)
        {

        // ==================================
        // LLENAR ARREGLO
        // ==================================

        case 1:
        {
            double inicio =
                omp_get_wtime();

            llenarArregloParalelo(
                original,
                TAM,
                MAX_VALOR
            );

            double fin =
                omp_get_wtime();

            tiempoLlenado =
                fin - inicio;

            arregloLleno = true;


            // Al generar datos nuevos,
            // los resultados anteriores dejan
            // de ser validos.

            ejecutadoCountingSec = false;
            ejecutadoCountingPar = false;

            ejecutadoMergeSec = false;
            ejecutadoMergePar = false;


            cout << "Arreglo llenado correctamente." << endl;

            cout << "Tiempo de llenado: "
                 << tiempoLlenado
                 << " segundos"
                 << endl;


            if (MOSTRAR_ARREGLO)
            {
                cout << "\nArreglo generado:" << endl;

                mostrarArreglo(
                    original,
                    TAM
                );
            }

            break;
        }


        // ==================================
        // MOSTRAR ORIGINAL
        // ==================================

        case 2:
        {
            if (!arregloLleno)
            {
                cout << "Primero debe llenar el arreglo."
                     << endl;

                break;
            }


            if (!MOSTRAR_ARREGLO)
            {
                cout << "La visualizacion del arreglo "
                     << "esta desactivada debido a su tamaño."
                     << endl;

                break;
            }


            cout << "Arreglo original:" << endl;

            mostrarArreglo(
                original,
                TAM
            );

            break;
        }


        // ==================================
        // COUNTING SECUENCIAL
        // ==================================

        case 3:
        {
            if (!arregloLleno)
            {
                cout << "Primero debe llenar el arreglo."
                     << endl;

                break;
            }


            // Usar exactamente los mismos datos.
            copiarArreglo(
                original,
                trabajo,
                TAM
            );


            double inicio =
                omp_get_wtime();

            countingSortSecuencial(
                trabajo,
                TAM,
                MAX_VALOR
            );

            double fin =
                omp_get_wtime();


            tiempoCountingSec =
                fin - inicio;

            ejecutadoCountingSec = true;


            cout << "Counting Sort secuencial terminado."
                 << endl;

            cout << "Tiempo: "
                 << tiempoCountingSec
                 << " segundos"
                 << endl;


            cout << "Resultado correcto: "
                 << (
                    estaOrdenado(trabajo, TAM)
                    ? "SI"
                    : "NO"
                 )
                 << endl;


            if (MOSTRAR_ARREGLO)
            {
                cout << "\nArreglo ordenado:" << endl;

                mostrarArreglo(
                    trabajo,
                    TAM
                );
            }

            break;
        }


        // ==================================
        // COUNTING PARALELO
        // ==================================

        case 4:
        {
            if (!arregloLleno)
            {
                cout << "Primero debe llenar el arreglo."
                     << endl;

                break;
            }


            copiarArreglo(
                original,
                trabajo,
                TAM
            );


            double inicio =
                omp_get_wtime();

            countingSortParalelo(
                trabajo,
                TAM,
                MAX_VALOR
            );

            double fin =
                omp_get_wtime();


            tiempoCountingPar =
                fin - inicio;

            ejecutadoCountingPar = true;


            cout << "Counting Sort paralelo terminado."
                 << endl;

            cout << "Tiempo: "
                 << tiempoCountingPar
                 << " segundos"
                 << endl;


            cout << "Resultado correcto: "
                 << (
                    estaOrdenado(trabajo, TAM)
                    ? "SI"
                    : "NO"
                 )
                 << endl;


            if (MOSTRAR_ARREGLO)
            {
                cout << "\nArreglo ordenado:" << endl;

                mostrarArreglo(
                    trabajo,
                    TAM
                );
            }

            break;
        }


        // ==================================
        // MERGE SECUENCIAL
        // ==================================

        case 5:
        {
            if (!arregloLleno)
            {
                cout << "Primero debe llenar el arreglo."
                     << endl;

                break;
            }


            copiarArreglo(
                original,
                trabajo,
                TAM
            );


            double inicio =
                omp_get_wtime();

            mergeSortSecuencial(
                trabajo,
                0,
                TAM - 1
            );

            double fin =
                omp_get_wtime();


            tiempoMergeSec =
                fin - inicio;

            ejecutadoMergeSec = true;


            cout << "Merge Sort secuencial terminado."
                 << endl;

            cout << "Tiempo: "
                 << tiempoMergeSec
                 << " segundos"
                 << endl;


            cout << "Resultado correcto: "
                 << (
                    estaOrdenado(trabajo, TAM)
                    ? "SI"
                    : "NO"
                 )
                 << endl;


            if (MOSTRAR_ARREGLO)
            {
                cout << "\nArreglo ordenado:" << endl;

                mostrarArreglo(
                    trabajo,
                    TAM
                );
            }

            break;
        }


        // ==================================
        // MERGE PARALELO
        // ==================================

        case 6:
        {
            if (!arregloLleno)
            {
                cout << "Primero debe llenar el arreglo."
                     << endl;

                break;
            }


            copiarArreglo(
                original,
                trabajo,
                TAM
            );


            double inicio =
                omp_get_wtime();

            mergeSortParalelo(
                trabajo,
                0,
                TAM - 1
            );

            double fin =
                omp_get_wtime();


            tiempoMergePar =
                fin - inicio;

            ejecutadoMergePar = true;


            cout << "Merge Sort paralelo terminado."
                 << endl;

            cout << "Tiempo: "
                 << tiempoMergePar
                 << " segundos"
                 << endl;


            cout << "Resultado correcto: "
                 << (
                    estaOrdenado(trabajo, TAM)
                    ? "SI"
                    : "NO"
                 )
                 << endl;


            if (MOSTRAR_ARREGLO)
            {
                cout << "\nArreglo ordenado:" << endl;

                mostrarArreglo(
                    trabajo,
                    TAM
                );
            }

            break;
        }


        // ==================================
        // COMPARAR TIEMPOS
        // ==================================

        case 7:
        {
            cout << fixed << setprecision(8);

            cout << "==========================================" << endl;
            cout << "        COMPARACION DE TIEMPOS" << endl;
            cout << "==========================================" << endl;

            cout << "\nTiempo de llenado: "
                 << tiempoLlenado
                 << " segundos"
                 << endl;


            cout << "\n---------- COUNTING SORT ----------"
                 << endl;


            if (ejecutadoCountingSec)
            {
                cout << "Secuencial: "
                     << tiempoCountingSec
                     << " segundos"
                     << endl;
            }
            else
            {
                cout << "Secuencial: NO EJECUTADO"
                     << endl;
            }


            if (ejecutadoCountingPar)
            {
                cout << "Paralelo:   "
                     << tiempoCountingPar
                     << " segundos"
                     << endl;
            }
            else
            {
                cout << "Paralelo:   NO EJECUTADO"
                     << endl;
            }


            if (
                ejecutadoCountingSec &&
                ejecutadoCountingPar &&
                tiempoCountingPar > 0.0
            )
            {
                double speedup =
                    tiempoCountingSec /
                    tiempoCountingPar;

                cout << "Speedup:     "
                     << speedup
                     << "x"
                     << endl;
            }


            cout << "\n------------ MERGE SORT ------------"
                 << endl;


            if (ejecutadoMergeSec)
            {
                cout << "Secuencial: "
                     << tiempoMergeSec
                     << " segundos"
                     << endl;
            }
            else
            {
                cout << "Secuencial: NO EJECUTADO"
                     << endl;
            }


            if (ejecutadoMergePar)
            {
                cout << "Paralelo:   "
                     << tiempoMergePar
                     << " segundos"
                     << endl;
            }
            else
            {
                cout << "Paralelo:   NO EJECUTADO"
                     << endl;
            }


            if (
                ejecutadoMergeSec &&
                ejecutadoMergePar &&
                tiempoMergePar > 0.0
            )
            {
                double speedup =
                    tiempoMergeSec /
                    tiempoMergePar;

                cout << "Speedup:     "
                     << speedup
                     << "x"
                     << endl;
            }


            cout << "==========================================" << endl;

            break;
        }


        // ==================================
        // SALIR
        // ==================================

        case 8:
        {
            cout << "Finalizando programa..."
                 << endl;

            break;
        }


        default:
        {
            cout << "Opcion no valida."
                 << endl;

            break;
        }

        }

    } while (opcion != 8);


    // ======================================
    // LIBERAR MEMORIA
    // ======================================

    delete[] original;
    delete[] trabajo;


    return 0;
}