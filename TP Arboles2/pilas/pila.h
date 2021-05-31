#ifndef __PILA_H__
#define __PILA_H__
#include <stddef.h>
#include "glist.h"

typedef GList Pila;

/**
 * Devuelve una pila vacia.
 */
Pila pila_crear();

/**
 * Destruye la pila.
 */
void pila_destruir(Pila pila, FuncionDestructora d);

/**
 * Comprueba que la pila este vacia.
 */
int pila_es_vacia(Pila pila);

/**
 * Devuelve el elemento en el tope de la pila.
 */
void * pila_tope(Pila pila, Copia c);

/**
 * Agrega un elemento al tope de la pila.
 */
void pila_apilar(Pila * pila, void * dato);

/**
 * Remueve el elemento al tope de la pila.
 */
void pila_desapilar(Pila *pila);

#endif /* __PILA_H__ */
