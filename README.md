# Ordenamiento-OpenMP

## Actividad 2.5: Ordenamientos

Implementar un algoritmo de ordenamiento iterativo y un algoritmo de ordenamiento recursivo en sus versiones secuencial y paralela utilizando OpenMP, aplicando mecanismos de paralelización y sincronización para comparar su desempeño.

## Antes de Comenzar

asegurate que tengas tu configuracion para vs code:


este es un archivo c_cpp_properties.json que va dentro de ".vscode"
```text
{
    "configurations": [
        {
            "name": "Mac ARM64 - MPI/OpenMP",
            "includePath": [
                "${workspaceFolder}/**",
                "/opt/homebrew/opt/mpich/include",
                "/opt/homebrew/opt/libomp/include"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/clang++",
            "cStandard": "c17",
            "cppStandard": "c++17",
            "intelliSenseMode": "macos-clang-arm64"
        }
    ],
    "version": 4
}
```
## Compilacion y ejecucion en Vs code

Colocate en la carpeta src en terminal y ejecuta: 

```text
clang++ -std=c++17 \                                                                  
-Xpreprocessor -fopenmp \
-Iinclude \
-I/opt/homebrew/opt/libomp/include \
main.cpp \
counting_secuencial.cpp \
counting_paralelo.cpp \
merge_secuencial.cpp \
merge_paralelo.cpp \
utilidades.cpp \
-L/opt/homebrew/opt/libomp/lib \
-lomp \
-o ordenamientos
```

y despues:

- **Run:** ./ordenamientos 



