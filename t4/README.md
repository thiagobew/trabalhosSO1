### Compile command
g++ -Wall -g  main.o main_class.o cpu.o debug.o thread.o system.o -o main

### Usefull Linux Commands
valgrind --leak-check=full --show-leak-kinds=all ./main

PROG_OBJ1 = main.o
nm -C -f sysv $PROG_OBJ1 | grep -e OBJECT -e FUNC -e NOTYPE >> global.txt