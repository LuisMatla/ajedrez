# Makefile para programas de OpenGL
# Uso: make <nombre_del_programa>
# Ejemplo: make GC_Cubo_LFCM

# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lGL -lGLU -lglut -lm

# Directorio de archivos fuente
SRC_DIR = .
OBJ_DIR = .

# Encontrar todos los archivos .c
SOURCES = $(wildcard $(SRC_DIR)/*.c)
TARGETS = $(SOURCES:.c=)

# Regla por defecto
all: $(TARGETS)

# Regla para compilar cualquier archivo .c
%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

# Regla para limpiar archivos compilados
clean:
	rm -f $(TARGETS)

# Regla para mostrar ayuda
help:
	@echo "Uso del Makefile:"
	@echo "  make <nombre_del_programa>  - Compila un programa específico"
	@echo "  make all                    - Compila todos los programas"
	@echo "  make clean                  - Elimina todos los ejecutables"
	@echo "  make help                   - Muestra esta ayuda"
	@echo ""
	@echo "Programas disponibles:"
	@for target in $(TARGETS); do \
		echo "  - $$(basename $$target)"; \
	done

.PHONY: all clean help


