main.o:
	gcc -c src/main.c -o build/main.o -Wpedantic -std=c11

gof.o:
	gcc -c src/gof.c -o build/gof.o -Wpedantic -std=c11

gof: main.o gof.o
	gcc build/main.o build/gof.o -o gof -lSDL2main -lSDL2
