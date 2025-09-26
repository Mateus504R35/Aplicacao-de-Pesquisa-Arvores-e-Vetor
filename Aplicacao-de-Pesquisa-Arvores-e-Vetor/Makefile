# Makefile para Aplicação de Pesquisa (Árvores e Vetor)
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -O2
TARGET = pesquisa_arvores_vetor
OBJS = ABB.o AVL.o AVLF.o PB.o Repositorio.o main.o

.PHONY: all clean run debug

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

main.o: main.c PB.h AVL.h AVLF.h ABB.h Repositorio.h
	$(CC) $(CFLAGS) -c main.c

run: $(TARGET)
	./$(TARGET)

debug: CFLAGS += -g -O0
debug: clean all

clean:
	rm -f $(OBJS) $(TARGET)
