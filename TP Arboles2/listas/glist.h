#ifndef __GLIST_H__
#define __GLIST_H__

#include <stddef.h>

typedef struct _GNodo {
  void *dato;
  struct _GNodo *sig;
} GNodo;

typedef GNodo *GList;

typedef void (*FuncionDestructora)(void* a);
typedef void* (* Copia) (void *dato);

/**
 * Devuelve una lista vacía.
 */
GList glist_crear();

/**
 * Destruccion de la lista.
 */
void glist_destruir(GList lista, FuncionDestructora d);

/**
 * Agrega un elemento al inicio de la lista.
 */
GList glist_agregar_inicio(GList lista, void * dato);

#endif /* __GLIST_H__ */
