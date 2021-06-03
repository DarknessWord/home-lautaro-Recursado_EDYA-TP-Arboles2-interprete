#ifndef __BTREE_H__
#define __BTREE_H__

struct _BTNodo {
  void * dato;
  struct _BTNodo *left;
  struct _BTNodo *right;
};

typedef struct _BTNodo *BTree;
typedef void (*FuncionDestructora)(void* dato);
typedef void (*FuncionVisitanteExtra) (void * dato, void *extra);
/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear();

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo, FuncionDestructora d);

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo);

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(void * dato, BTree left, BTree right);

/**
 * Recibe un arbol y devuelve una copia.
 */
void * copytree(void * dato);

/**
 * Destruccion del arbol.
 */
void destroytree(void * dato);

/**
 * Chequea que la cadena contenga solo digitos.
 */
int isnum(char* a);

/**
 * Imprime la expresion del arbol recibido.
 */
void imprimir_inorder(BTree arbol);

BTree inorder_extra(BTree arbol,FuncionVisitanteExtra visit,void * extra);

#endif /* __BTREE_H__ */
