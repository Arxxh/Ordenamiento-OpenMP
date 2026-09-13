// ITERATIVO
#include "counting_sort.h"

void countingSortSecuencial(int* arreglo, int n, int maxValor)
{
    if (arreglo == nullptr || n <= 1)
        return;

    // Arreglo auxiliar para contar cuántas veces aparece cada valor.
    int* conteo = new int[maxValor + 1]();

    // Contar apariciones.
    for (int i = 0; i < n; i++)
    {
        conteo[arreglo[i]]++;
    }

    // Reconstruir el arreglo ordenado.
    int posicion = 0;

    for (int valor = 0; valor <= maxValor; valor++)
    {
        while (conteo[valor] > 0)
        {
            arreglo[posicion] = valor;

            posicion++;
            conteo[valor]--;
        }
    }

    delete[] conteo;
}