#include <iostream>
#include "counting_sort.h"

using namespace std;

void mostrarArreglo(const int* arreglo, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arreglo[i] << " ";
    }

    cout << endl;
}

bool estaOrdenado(const int* arreglo, int n)
{
    for (int i = 1; i < n; i++)
    {
        if (arreglo[i - 1] > arreglo[i])
        {
            return false;
        }
    }

    return true;
}

int main()
{
    const int n = 10;
    const int maxValor = 20;

    int* arreglo = new int[n] {
        15, 3, 8, 3, 20,
        1, 9, 7, 15, 2
    };

    cout << "==================================" << endl;
    cout << " TEST COUNTING SORT PARALELO" << endl;
    cout << "==================================" << endl;

    cout << "\nArreglo original:" << endl;

    mostrarArreglo(arreglo, n);

    countingSortParalelo(
        arreglo,
        n,
        maxValor
    );

    cout << "\nArreglo ordenado:" << endl;

    mostrarArreglo(arreglo, n);

    cout << "\nResultado: ";

    if (estaOrdenado(arreglo, n))
    {
        cout << "CORRECTO" << endl;
    }
    else
    {
        cout << "ERROR" << endl;
    }

    delete[] arreglo;

    return 0;
}
