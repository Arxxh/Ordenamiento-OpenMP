#ifndef UTILIDADES_H
#define UTILIDADES_H

void llenarArregloParalelo(
    int* arreglo,
    int n,
    int maxValor
);

void mostrarArreglo(
    const int* arreglo,
    int n
);

void copiarArreglo(
    const int* origen,
    int* destino,
    int n
);

bool estaOrdenado(
    const int* arreglo,
    int n
);

bool arreglosIguales(
    const int* arreglo1,
    const int* arreglo2,
    int n
);

#endif