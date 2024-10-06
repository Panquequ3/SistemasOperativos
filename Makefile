CC=g++
CFLAGS=-Wall -std=c++17 -Iexternal/dotenv-cpp/include -Isrc -Iinclude
BINS=multiTarea

all: clean programa

programa:
	$(CC) $(CFLAGS) -o multiTarea src/multiTarea.cpp src/funciones.cpp src/menu.cpp src/userValidator.cpp

clean:
	@echo " [CLN] Removing binary files... chao!!"
	@rm -f $(BINS)
