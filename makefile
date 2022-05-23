all: P3

main.o: main.c fitxers.h tipus.h pila.h domino.h llistapdi.h
	gcc main.c -c -Wall -Wextra

fitxers.o: fitxers.c fitxers.h
	gcc fitxers.c -c -Wall -Wextra

pila.o: pila.c pila.h
	gcc pila.c -c -Wall -Wextra

domino.o: domino.c domino.h
	gcc domino.c -c -Wall -Wextra

llistapdi.o: llistapdi.c llistapdi.h
	gcc llistapdi.c -c -Wall -Wextra

P3: main.o fitxers.o pila.o domino.o llistapdi.o
	gcc main.o fitxers.o pila.o domino.o llistapdi.o -o P3 -Wall -Wextra

clean:
	rm *.o P3

tar:
	tar -cvzf p3.tar.gz *.c *.h makefile
