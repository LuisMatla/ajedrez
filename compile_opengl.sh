#!/bin/bash

# Script para compilar programas de OpenGL en C
# Uso: ./compile_opengl.sh nombre_del_archivo.c

if [ $# -eq 0 ]; then
    echo "Uso: $0 <archivo.c>"
    echo "Ejemplo: $0 GC_Cubo_LFCM.c"
    exit 1
fi

ARCHIVO=$1
NOMBRE_SIN_EXTENSION=$(basename "$ARCHIVO" .c)

echo "Compilando $ARCHIVO..."

# Compilar con las librerías de OpenGL
gcc -o "$NOMBRE_SIN_EXTENSION" "$ARCHIVO" \
    -lGL -lGLU -lglut -lm

if [ $? -eq 0 ]; then
    echo "Compilación exitosa!"
    echo "Ejecutando $NOMBRE_SIN_EXTENSION..."
    ./"$NOMBRE_SIN_EXTENSION"
else
    echo "Error en la compilación"
    exit 1
fi


