#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "glist.h"
#include "pila.h"

//pila_crear: _ -> Pila
//se retorna una pila vacia.
//entrada: _ ; salida: NULL
Pila pila_crear(){
	return glist_crear();
}

//pila_destruir: Pila -> _
//El parametro representa una pila
//Se libera la memoria ocupada por la pila
//entrada: pila ; salida: _
void pila_destruir(Pila pila, FuncionDestructora d){
	glist_destruir(pila, d);
}

//pila_es_vacia: Pila -> int
//Verifica si la pila se encuentra vacia
//En caso de estar vacia retorna 1, retorna 0 caso contrario
//entrada: pila ; salida: _
int pila_es_vacia(Pila pila){
	return pila == NULL;
}

//pila_tope: Pila Copia -> void*
//El primer parametro representa una pila y el segundo una funcion
//que retorna una copia del dato recibido
//Se retorna una copia del elemento que se encuentra en el tope de la pila
//entrada: pila copia ; salida: dato
void * pila_tope(Pila pila, Copia c){
	return pila_es_vacia(pila)?NULL:c(pila->dato);
}

//pila_apilar: Pila void* -> _
//El primer parametro representa una pila y el segundo un dato.
//Se coloca en el tope de la pila el dato recibido
//entrada: pila dato ; salida: _
void pila_apilar(Pila * pila, void * dato){
	*pila = glist_agregar_inicio(*pila, dato);
}

//pila_desapilar: Pila FuncionDestructora -> _
//El primer parametro representa una pila y el segundo una funcion
//que destruye un dato.
//Se destruye el elemento al tope de la pila
//entrada: pila d ; salida: _
void pila_desapilar(Pila *pila){
	Pila aux = *pila;
	*pila = (*pila)->sig;
	free(aux);
}
