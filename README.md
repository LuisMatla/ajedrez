# 🎮 Ajedrez 3D con OpenGL/GLUT

⚠️ **ESTADO: INCOMPLETO** ⚠️

Este proyecto es un juego de ajedrez 3D implementado en C usando OpenGL y GLUT. Actualmente está en desarrollo y algunas funcionalidades pueden no estar completamente implementadas o pueden tener bugs.

## 👨‍💻 Autor

**Luis Fernando Contreras Matla**

## 🎓 Información Académica

Este proyecto fue creado para la materia de **Graficación por Computadora** de la **Universidad Veracruzana**.

## 🛠️ Tecnologías Utilizadas

<div align="center">

![C](https://img.shields.io/badge/C-A8A8A8?style=for-the-badge&logo=c&logoColor=555555)
![OpenGL](https://img.shields.io/badge/OpenGL-5586A4?style=for-the-badge&logo=opengl&logoColor=white)
![GLUT](https://img.shields.io/badge/GLUT-DD6B6B?style=for-the-badge&logo=opengl&logoColor=white)
![Mesa](https://img.shields.io/badge/Mesa-0000FF?style=for-the-badge&logo=opengl&logoColor=white)

</div>

<table>
<tr>
<td align="center" width="25%">
  <img src="https://img.shields.io/badge/C-A8A8A8?style=flat-square&logo=c&logoColor=555555" alt="C" />
  <br>C
</td>
<td align="center" width="25%">
  <img src="https://img.shields.io/badge/OpenGL-5586A4?style=flat-square&logo=opengl&logoColor=white" alt="OpenGL" />
  <br>OpenGL
</td>
<td align="center" width="25%">
  <img src="https://img.shields.io/badge/GLUT-DD6B6B?style=flat-square&logo=opengl&logoColor=white" alt="GLUT" />
  <br>GLUT
</td>
<td align="center" width="25%">
  <img src="https://img.shields.io/badge/Mesa-0000FF?style=flat-square&logo=opengl&logoColor=white" alt="Mesa" />
  <br>Mesa
</td>
</tr>
</table>

## Descripción General

Este programa implementa un juego de ajedrez en 3D donde los jugadores pueden ver el tablero desde una perspectiva isométrica, seleccionar piezas, ver movimientos válidos y jugar turnos alternados.

## 📋 Requisitos del Sistema

- **Compilador**: GCC
- **Bibliotecas**:
  - OpenGL (libGL)
  - GLU (libGLU)
  - GLUT/FreeGLUT (libglut)
  - Matemáticas (libm)

## 🔨 Compilación

```bash
gcc ajedrez.c -o ajedrez -lGL -lGLU -lglut -lm
```

## ▶️ Ejecución

```bash
./ajedrez
```

## 📐 Estructura del Programa

### 🎯 Estados del Juego

El programa utiliza un sistema de estados (`EstadoJuego`) para manejar diferentes pantallas:

1. **MENU_INICIAL**: Pantalla de inicio con opciones "Uno vs Uno" y "Uno vs IA"
2. **SOLICITANDO_NOMBRE_BLANCO**: Solicita el nombre del jugador de piezas blancas
3. **SOLICITANDO_NOMBRE_NEGRO**: Solicita el nombre del jugador de piezas negras
4. **JUGANDO_UNO_VS_UNO**: Estado de juego para dos jugadores
5. **JUGANDO_UNO_VS_IA**: Estado de juego contra IA (no implementado completamente)

### 🎲 Sistema de Tablero

El tablero se representa mediante una matriz 8x8 (`tableroJuego[8][8]`) donde:
- **Fila 0-7**: Representa las filas del tablero (1-8 en notación de ajedrez)
- **Columna 0-7**: Representa las columnas del tablero (A-H en notación de ajedrez)
- **Coordenada (0,0)**: Corresponde a A1 (esquina inferior izquierda para blancas)
- **Coordenada (7,7)**: Corresponde a H8 (esquina superior derecha para blancas)

### ♟️ Tipos de Piezas

Las piezas se representan mediante un enum `TipoPieza`:
- Valores positivos: Piezas blancas (1-6)
- Valores negativos: Piezas negras (-1 a -6)
- 0: Casilla vacía

```
PEON_BLANCO = 1,    PEON_NEGRO = -1
TORRE_BLANCA = 2,   TORRE_NEGRA = -2
CABALLO_BLANCO = 3, CABALLO_NEGRO = -3
ALFIL_BLANCO = 4,   ALFIL_NEGRO = -4
REINA_BLANCA = 5,   REINA_NEGRA = -5
REY_BLANCO = 6,     REY_NEGRO = -6
```

### 🔄 Sistema de Turnos

- `turnoActual = 1`: Turno de las piezas blancas
- `turnoActual = -1`: Turno de las piezas negras
- Solo se pueden mover piezas del color correspondiente al turno actual

### 🖱️ Selección de Piezas

- `filaSeleccionada` y `columnaSeleccionada`: Coordenadas de la pieza seleccionada (-1 si no hay selección)
- `casillasValidas[8][8]`: Matriz que marca las casillas válidas para movimiento (1 = válida, 0 = no válida)

## ✨ Funcionalidades Implementadas

### 1. 📋 Menú Inicial
- Botones para seleccionar "Uno vs Uno" o "Uno vs IA"
- Botón de flecha para volver atrás
- Detección de clics en botones

### 2. ✍️ Entrada de Nombres
- Solicita nombres de jugadores uno por uno
- Muestra el nombre ingresado junto con una pieza del color correspondiente
- Soporte para imágenes personalizadas de jugadores (usando stb_image.h)

### 3. 🎨 Tablero 3D
- Tablero con patrón de colores alternado (rosa claro y morado)
- Vista isométrica desde arriba
- Piezas modeladas en 3D usando primitivas de OpenGL

### 4. 🎯 Sistema de Movimientos

#### Movimientos Implementados por Pieza:

**♟️ Peón (PEON_BLANCO/PEON_NEGRO)**:
- Primer movimiento: 1 o 2 casillas hacia adelante
- Movimientos normales: 1 casilla hacia adelante
- Captura: Diagonal (solo si hay pieza enemiga)
- No implementado: En passant, promoción

**♜ Torre (TORRE_BLANCA/TORRE_NEGRA)**:
- Movimiento horizontal y vertical ilimitado
- Se detiene al encontrar otra pieza

**♞ Caballo (CABALLO_BLANCO/CABALLO_NEGRO)**:
- Movimiento en L (2 casillas en una dirección, 1 en perpendicular)
- Puede saltar sobre otras piezas

**♝ Alfil (ALFIL_BLANCO/ALFIL_NEGRO)**:
- Movimiento diagonal ilimitado
- Se detiene al encontrar otra pieza

**♛ Reina (REINA_BLANCA/REINA_NEGRA)**:
- Combina movimientos de torre y alfil
- Movimiento horizontal, vertical y diagonal ilimitado

**♚ Rey (REY_BLANCO/REY_NEGRO)**:
- Movimiento de 1 casilla en cualquier dirección
- No implementado: Enroque, detección de jaque

### 5. 🔴 Visualización de Movimientos Válidos
- Cuando se selecciona una pieza, se muestran cuadros rojos en las casillas válidas
- Los cuadros rojos se dibujan ligeramente por encima del tablero

### 6. 📷 Control de Cámara
- **Zoom**: Rueda del mouse (acerca/aleja)
- **Rotación**: Clic derecho + arrastrar (rota la vista)
- Vista isométrica fija (no se puede mover el tablero)

### 7. 🖱️ Interacción con el Mouse
- **Clic izquierdo**: Selecciona pieza o mueve pieza seleccionada
- Conversión de coordenadas de pantalla a coordenadas del tablero usando `gluUnProject`

## 🔧 Funciones Principales

### ⚙️ Inicialización
- `inicializarTablero()`: Coloca todas las piezas en sus posiciones iniciales
- `reshape2()`: Maneja el redimensionamiento de la ventana y configura la proyección

### 🧮 Cálculo de Movimientos
- `calcularMovimientosValidos(int fila, int columna)`: Calcula y marca las casillas válidas
- `calcularMovimientosPeon()`: Movimientos específicos del peón
- `calcularMovimientosTorre()`: Movimientos específicos de la torre
- `calcularMovimientosAlfil()`: Movimientos específicos del alfil
- `calcularMovimientosCaballo()`: Movimientos específicos del caballo
- `calcularMovimientosReina()`: Movimientos específicos de la reina
- `calcularMovimientosRey()`: Movimientos específicos del rey

### 🎨 Dibujo
- `dibujarJuego()`: Función principal de renderizado del juego
- `dibujarPiezaSegunTipo()`: Dibuja una pieza según su tipo y posición
- `dibujar_tablero()`: Dibuja el tablero con patrón de colores
- `dibujarCuadroRojo()`: Dibuja un cuadro rojo para indicar movimiento válido
- Funciones individuales de piezas: `dibujar_Rey()`, `dibujar_Reina()`, `dibujar_Alfil()`, `dibujar_Caballo()`, `dibujar_Torre()`, `dibujar_Peon()`

### 🖱️ Interacción
- `mouseAjedrezFunc()`: Maneja los clics del mouse en el tablero
- `keyboardtodos()`: Maneja la entrada de texto para nombres de jugadores
- `specialKeys()`: Maneja teclas especiales (zoom, rotación)

## 📊 Variables Globales Importantes

### 📷 Control de Cámara
- `cameraX`, `cameraY`, `cameraZ`: Posición de la cámara
- `rotacionX`, `rotacionY`: Ángulos de rotación
- `zoomJuego`: Nivel de zoom

### 🎮 Estado del Juego
- `estadoActual`: Estado actual del juego (menú, entrada de nombres, juego)
- `tableroJuego[8][8]`: Estado del tablero
- `turnoActual`: Turno actual (1 = blancas, -1 = negras)
- `filaSeleccionada`, `columnaSeleccionada`: Pieza seleccionada
- `casillasValidas[8][8]`: Casillas válidas para movimiento

### 💻 Interfaz
- `nombreJugadorBlanco[]`, `nombreJugadorNegro[]`: Nombres de los jugadores
- `inputBuffer[]`: Buffer para entrada de texto
- `texturaPiezaBlanca`, `texturaPiezaNegra`: Texturas para imágenes de jugadores

## ⚠️ Problemas Conocidos / Limitaciones

⚠️ **El proyecto está INCOMPLETO**. Algunas limitaciones conocidas:

1. **Selección Visual**: Las piezas peón y caballo no muestran efecto visual de selección (no se ponen grises) debido a problemas con el manejo de color en OpenGL
2. **IA**: El modo "Uno vs IA" no está implementado
3. **Reglas Avanzadas**:
   - Enroque no implementado
   - En passant no implementado
   - Promoción de peón no implementado
   - Detección de jaque/jaque mate no implementado
   - Validación de movimientos que dejan al rey en jaque no implementada
4. **Fin del Juego**: No hay detección de fin de partida
5. **Validación**: No se valida si un movimiento deja al rey propio en jaque

## 📁 Estructura del Código

El código está organizado en secciones:

1. **Includes y definiciones**: Librerías y constantes
2. **Variables globales**: Estado del juego, cámara, tablero
3. **Funciones auxiliares**: Conversión de coordenadas, cálculos matemáticos
4. **Funciones de dibujo de piezas**: Cada pieza tiene funciones para dibujarla
5. **Funciones de lógica del juego**: Inicialización, cálculo de movimientos
6. **Funciones de interfaz**: Menú, entrada de texto, botones
7. **Funciones de OpenGL**: Callbacks de GLUT (display, mouse, keyboard)
8. **Función main**: Inicialización de ventanas y GLUT

## 💡 Notas Técnicas

- El programa usa `gluUnProject` para convertir coordenadas de pantalla a coordenadas del mundo 3D
- Las piezas se dibujan usando primitivas de OpenGL (GL_QUADS, glutSolidSphere, glutSolidTorus, etc.)
- Se usa `glPushMatrix()` y `glPopMatrix()` para aislar transformaciones
- El color se maneja con `glColor3f()` y `GL_COLOR_MATERIAL` para compatibilidad con iluminación
- Las imágenes de jugadores se cargan usando `stb_image.h` (single-file header library)

## 🚀 Mejoras Futuras

- [ ] Implementar detección de jaque y jaque mate
- [ ] Implementar enroque
- [ ] Implementar en passant
- [ ] Implementar promoción de peón
- [ ] Implementar IA básica
- [ ] Mejorar la visualización de selección de piezas
- [ ] Agregar sonidos 🔊
- [ ] Agregar animaciones de movimiento
- [ ] Implementar guardado/carga de partidas 💾
- [ ] Agregar modo de análisis de partidas

## 📝 Licencia

Este proyecto es de código abierto para fines educativos.
