# Guía para ejecutar programas de OpenGL en C

## Instalación de dependencias

### Opción 1: Instalación automática
```bash
sudo ./install_dependencies.sh
```

### Opción 2: Instalación manual
```bash
# Instalar herramientas de desarrollo
sudo dnf5 install gcc gcc-c++ make cmake pkg-config -y

# Instalar librerías de OpenGL
sudo dnf5 install freeglut-devel mesa-libGL-devel mesa-libGLU-devel -y
```

## Compilación y ejecución

### Método 1: Usando el script de compilación
```bash
./compile_opengl.sh <archivo.c>
```

**Ejemplos:**
```bash
./compile_opengl.sh GC_Cubo_LFCM.c
./compile_opengl.sh GC_Esfera_LFCM.c
./compile_opengl.sh GC_Practica_Menu_LFCM.c
```

### Método 2: Usando Makefile
```bash
# Compilar un programa específico
make <nombre_del_programa>

# Compilar todos los programas
make all

# Ver programas disponibles
make help

# Limpiar archivos compilados
make clean
```

**Ejemplos:**
```bash
make GC_Cubo_LFCM
make GC_Esfera_LFCM
make GC_Practica_Menu_LFCM
```

### Método 3: Compilación manual
```bash
gcc -o <nombre_ejecutable> <archivo.c> -lGL -lGLU -lglut -lm
./<nombre_ejecutable>
```

**Ejemplo:**
```bash
gcc -o cubo GC_Cubo_LFCM.c -lGL -lGLU -lglut -lm
./cubo
```

## Programas disponibles

Los siguientes programas están listos para compilar:

- `GC_Cubo_LFCM.c` - Dibujo de un cubo
- `GC_Esfera_LFCM.c` - Cálculos de esfera (programa de consola)
- `GC_Practica_Menu_LFCM.c` - Menú interactivo con figuras
- `GC_Esfera3D_LFCM.c` - Esfera 3D
- `GC_Cono3D_LFCM.c` - Cono 3D
- `GC_Toro3D_LFCM.c` - Toro 3D
- Y muchos más...

## Solución de problemas

### Error: "gcc: command not found"
```bash
sudo dnf5 install gcc gcc-c++ make -y
```

### Error: "glut.h: No such file or directory"
```bash
sudo dnf5 install freeglut-devel -y
```

### Error: "GL/gl.h: No such file or directory"
```bash
sudo dnf5 install mesa-libGL-devel -y
```

### Error: "GL/glu.h: No such file or directory"
```bash
sudo dnf5 install mesa-libGLU-devel -y
```

### El programa se ejecuta pero no muestra ventana gráfica
- Asegúrate de tener un servidor X funcionando
- Si usas SSH, usa `ssh -X` para habilitar X11 forwarding
- Verifica que tengas un entorno gráfico instalado

## Controles comunes en los programas

- **Teclas de flecha**: Mover la cámara
- **Mouse**: Rotar la vista (en algunos programas)
- **ESC o 'q'**: Salir del programa
- **Espacio**: Pausar/reanudar animación (en algunos programas)

## Notas importantes

1. Algunos programas como `GC_Esfera_LFCM.c` son programas de consola, no gráficos
2. Los programas que usan `glut.h` requieren un entorno gráfico
3. Si tienes problemas con permisos, asegúrate de que los scripts tengan permisos de ejecución:
   ```bash
   chmod +x *.sh
   ```
