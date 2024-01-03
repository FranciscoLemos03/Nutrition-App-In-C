CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11
LDFLAGS =

SRC = main.c Plano.c ListaLigada.c Cliente.c Alimentos.c
OBJ = $(SRC:.c=.o)

EXECUTABLE = program

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(EXECUTABLE)

