#include "glist.h"
#include <stdlib.h>
#include <stdio.h>

// glist_crear: _ -> GList
// Se retorna una lista general vacia.
// entrada: _, salida: NULL
GList glist_crear() {
  return NULL;
}

// glist_destruir: GList -> _
// El parametro representa una lista general.
// Se libera la memoria ocupada por la lista.
// entrada: list, salida: _
void glist_destruir(GList lista, FuncionDestructora d) {
  GNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = (lista)->sig;
    d(nodoAEliminar->dato);
    free(nodoAEliminar);
  }
}

// glist_agregar_inicio: GList void* -> GList
// El primer parametro representa una lista general.
// El segundo parametro representa un dato.
// Se agrega al inicio de la lista el dato recibido.
// entrada: list, salida: ?
GList glist_agregar_inicio(GList lista, void * dato) {
  GNodo *nuevoNodo = malloc(sizeof(GNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista;
  return nuevoNodo;
}
