all: init getty sh

hola1: Practica 2/init.c
	gcc -o bin/init Practica 2/init.c
	

hola2: Practica 2/getty.c
	gcc -o bin/getty Practica 2/getty.c
	

hola3: Practica 2/sh.c
	gcc -o bin/sh Practica 2/sh.c
	

clean:
	rm bin/init bin/getty bin/sh