# https://www.softwaretestinghelp.com/cpp-makefile-tutorial/#:~:text=for%20rm%20commands-,C%2B%2B%20Makefile,as%20the%20build%2Dorder%20dependencies.

CC = g++
CFLAGS = -Wall -g

# Primeira linha são as dependências que irão causar a sequência de alterações abaixo
main: main.o main_class.o cpu.o
	echo "Aoba"
	$(CC) $(CFLAGS) main.o main_class.o cpu.o –o main

main.o: main.cc main_class.h cpu.h
	echo "Eae"
	g++ –c main.cc

main_class.o: main_class.cc main_class.h
	$(CC) $(CFLAGS) -c main_class.cc

cpu.o: cpu.cc cpu.h
	$(CC) $(CFLAGS) -c cpu.cc

clean:
	rm *.o main