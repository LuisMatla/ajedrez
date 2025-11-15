#!/bin/bash

echo "=== Instalando dependencias para OpenGL en C ==="
echo ""

# Verificar si el usuario tiene permisos de sudo
if ! sudo -n true 2>/dev/null; then
    echo "Este script requiere permisos de administrador."
    echo "Por favor, ejecuta: sudo $0"
    exit 1
fi

echo "1. Instalando herramientas de desarrollo..."
sudo dnf5 install gcc gcc-c++ make cmake pkg-config -y

echo ""
echo "2. Instalando librerías de OpenGL..."
sudo dnf5 install freeglut-devel mesa-libGL-devel mesa-libGLU-devel -y

echo ""
echo "4. Verificando instalación..."
if command -v gcc &> /dev/null; then
    echo "✓ GCC instalado: $(gcc --version | head -n1)"
else
    echo "✗ Error: GCC no se instaló correctamente"
fi

if pkg-config --exists glut; then
    echo "✓ FreeGLUT instalado correctamente"
else
    echo "✗ Error: FreeGLUT no se instaló correctamente"
fi

echo ""
echo "=== Instalación completada ==="
echo ""
echo "Ahora puedes compilar tus programas de OpenGL usando:"
echo "  ./compile_opengl.sh <archivo.c>"
echo "  o"
echo "  make <nombre_del_programa>"
echo ""
echo "Ejemplo:"
echo "  ./compile_opengl.sh GC_Cubo_LFCM.c"
echo "  make GC_Cubo_LFCM"
