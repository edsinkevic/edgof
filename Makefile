build_folder:
	mkdir -p build

main.o: build_folder
	gcc -c src/main.c -o build/main.o -Wpedantic -std=c11

gof.o: build_folder
	gcc -c src/gof.c -o build/gof.o -Wpedantic -std=c11

gof: main.o gof.o
	gcc build/main.o build/gof.o -o gof -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all: gof