CC=g++
CFLAGS=-Wall -std=c++17 -Idotenv-cpp/include
BINS=multiTarea
all: clean programa

programa:
	$(CC) $(CFLAGS) -o multiTarea multiTarea.cpp funciones.cpp menu.cpp userValidator.cpp contadorPalabras.cpp menuContador.cpp

clean:
	@echo " [CLN] Removing binary files... chao!!"
	@rm -f $(BINS)