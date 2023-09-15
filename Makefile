main.o:
	gcc -c src/main.c -o build/main.o -Wpedantic -std=c11

gof: main.o
	gcc build/main.o -o gof 
