CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OBJ = main.o simulador.o validaciones.o

all: simulador_sls

simulador_sls: $(OBJ)
	$(CC) $(OBJ) -o simulador_sls -lm

main.o: main.c simulador.h validaciones.h
	$(CC) $(CFLAGS) -c main.c

simulador.o: simulador.c simulador.h validaciones.h
	$(CC) $(CFLAGS) -c simulador.c

validaciones.o: validaciones.c validaciones.h
	$(CC) $(CFLAGS) -c validaciones.c

clean:
	rm -f $(OBJ) simulador_sls simulador_sls.exe
