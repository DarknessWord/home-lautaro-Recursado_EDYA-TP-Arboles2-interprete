#ifndef __TABLAOPS_H__
#define __TABLAOPS_H__

#include "operadores.h"
#include "glist.h"
#include <assert.h>
#include <math.h>

typedef struct _Operador{
  char* simbolo;
  int aridad;
  FuncionEvaluacion eval;
}_Operador;

typedef _Operador* Operador;

typedef GList TablaOps;

/**
 * Devuelve una tabla vacia.
 */
TablaOps tabla_crear();

/**
 * Destruccion de la tabla.
 */
void tabla_destruir(TablaOps tabla);

/**
 * Carga un operador en la tabla recibida con el simbolo, aridad y funcion evaluadora recibidos.
 */
TablaOps cargar_operador(TablaOps tabla, char* simbolo, int aridad, FuncionEvaluacion eval);

/**
 * Carga los operadores en la tabla recibida.
 */
TablaOps cargar_operadores_total(TablaOps tabla);

/**
 * Devuelve la aridad del operador recibido segun este guardado en la tabla.
 */
int aridad_operador(char * operador, TablaOps tabla);

/**
 * Verifica si el operador recibido se encuentra en la tabla.
 */
int buscar_operador(TablaOps tabla, char * simbolo);

#endif /* __TABLAOPS_H__ */