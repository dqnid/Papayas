main : arbol.o papayas.o
	gcc papayas.o arbol.o -o main

papayas.o : papayas.c arbol.h
	gcc -c -g papayas.c

arbol.o : arbol.c arbol.h
	gcc -c -g arbol.c
