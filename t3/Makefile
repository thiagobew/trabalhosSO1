# https://www.softwaretestinghelp.com/cpp-makefile-tutorial/#:~:text=for%20rm%20commands-,C%2B%2B%20Makefile,as%20the%20build%2Dorder%20dependencies.

CC = g++
CFLAGS = -Wall -g

# Primeira linha são as dependências que irão causar a sequência de alterações abaixo
# Verificar a consistência do Makefile pois alterações no traits.h não são refletidas no projeto sem ocorrer um make clean e depois um make
# Mesmo que as alterações levem a uma nova compilação
main: main.o main_class.o cpu.o debug.o thread.o system.o traits.h
	$(CC) $(CFLAGS) main.o main_class.o cpu.o debug.o thread.o system.o traits.h -o main

main.o: main.cc main_class.h
	$(CC) $(CFLAGS) -c main.cc $<

main_class.o: main_class.cc main_class.h
	$(CC) $(CFLAGS) -c main_class.cc $<

cpu.o: cpu.cc cpu.h
	$(CC) $(CFLAGS) -c cpu.cc $<

thread.o: thread.cc thread.h debug.h traits.h
	$(CC) $(CFLAGS) -c thread.cc $<

debug.o: debug.cc debug.h
	$(CC) $(CFLAGS) -c debug.cc $<

system.o: system.cc system.h debug.h traits.h
	$(CC) $(CFLAGS) -c system.cc $<

clean:
	rm *.o main