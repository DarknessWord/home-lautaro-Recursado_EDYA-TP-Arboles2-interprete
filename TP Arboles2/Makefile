#Banderas para compilar

FLAGS = -Wall -Wextra -std=c99 -g
EJECUTABLE = ejecutar

#-Wall y -Wextra: activan todos las advertencias
#-Werror: convierte las advertencias en errores
#-std=c99: usa el est´andar C99
#-g: genera informaci´on para el debugging

#-c: Compila el codigo sin linkear, se crea un archivo objeto.
#-o: cambia el nombre por defecto del archivo generado por uno elegido.
#-lm: para enlazar la libreria math

### compilado ###
preparado :
	@cp operadores/*.h operadores/*.c ./
	@cp interprete/*.h interprete/*.c ./
	@cp arboles/*.h arboles/*.c ./
	@cp tablaops/*.h tablaops/*.c ./
	@cp pilas/*.h pilas/*.c ./
	@cp main/*.c ./
	@cp listas/*.h listas/*.c ./
	make main
	make clear
	@echo ------------------------------
	@echo  Compilación terminada
	@echo ------------------------------


### Programa principal ###
operadores.o : operadores.c operadores.h 
	gcc -c $(FLAGS) operadores.c

tablaops.o: tablaops.c tablaops.h glist.h operadores.h
	gcc -c $(FLAGS) tablaops.c
		

main : main.o operadores.o tablaops.o glist.o interprete.o btree.o pila.o
	gcc -o $(EJECUTABLE) main.o operadores.o tablaops.o glist.o interprete.o btree.o pila.o -lm

main.o : main.c tablaops.h operadores.h interprete.h
	gcc -c $(FLAGS) main.c

interprete.o: interprete.c interprete.h glist.h btree.h tablaops.h pila.h
	gcc -c $(FLAGS) interprete.c

glist.o : glist.c glist.h
	gcc -c $(FLAGS) glist.c

btree.o: btree.c btree.h
	gcc -c $(FLAGS) btree.c

pila.o: pila.c pila.h glist.h
	gcc -c $(FLAGS) pila.c	

CLEAR :
	make clear
	rm -f $(EJECUTABLE)
	@clear

### Limpieza de archivos ###
clear :
	rm -f *.c *.h *.o
