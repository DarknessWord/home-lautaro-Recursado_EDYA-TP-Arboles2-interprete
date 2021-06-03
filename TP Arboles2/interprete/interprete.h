#ifndef __INTERPRETE_H__
#define __INTERPRETE_H__
#include "tablaops.h"
#include "btree.h"
#include <stddef.h>
#define MAXINT 150

typedef struct _arbolalias{
   BTree arbol;
   char alias[MAXINT];
}_arbolalias;
typedef _arbolalias * ArbolAlias;

/**
 * Recibe un string alias, y verifica sea valido.
 */
int verificar_alias(char* alias);

/**
 * Recibe un string y verifica que solo esté formado por números.
 */
int isnum(char* a);

/**
 * Recibe un arbol aritmetico y lo imprime en recorrido inorder.
 */
void imprimir_inorder(BTree arbol);

/**
 * Recibe una lista de ArbolAlias lista_arboles y un string alias,
 * imprime el arbol correspondiente al string alias.
 */
void imprimir(GList lista_arboles,char * alias);

/**
 * Recibe una lista de ArbolAlias lista_arboles, un string alias,
 * un string expresion y una tabla de operadores tabla,
 * carga el arbol correspondiente a la expresion, en lista_arboles
 * con el alias recibido.
 */
void cargar(GList * lista_arboles, char * alias, char * expresion,
                                                 TablaOps tabla);

/**
 * Interpreta los comandos recibidos por consola.
 */
void interpretar(TablaOps tabla);

#endif /* __INTERPRETE_H__ */
