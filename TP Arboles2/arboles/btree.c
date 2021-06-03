#include "btree.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// btree_crear: _ -> BTree
// Esta funcion no tiene argumentos y devuelve una estructura tipo BTree
// entrada: _, salida: NULL
BTree btree_crear() {
	return NULL;
}

// btree_destruir: BTree -> _
// Esta funcion recibe un parametro tipo BTree y no tiene return.
// Libera la memoria ocupada por el arbol "nodo"
// entrada: NULL, salida: _
// entrada: nodo, salida: _
void btree_destruir(BTree nodo, FuncionDestructora f){
  if (nodo != NULL) {
    btree_destruir(nodo->left, f);
    btree_destruir(nodo->right, f);
		f(nodo->dato);
    free(nodo);
  }
}

// btree_empty: BTree -> int
// Esta funcion recibe un parametro tipo BTree retorna un entero {0,1}.
// Evalua a 1 si el arbol se encuentra vacio y 0 caso contrario.
// entrada: NULL, salida: 1
// entrada: nodo, salida: 0
int btree_empty(BTree nodo) {
	return nodo == NULL;
}

// btree_unir: void* BTree BTree -> BTree
// Los parametros representan:
// El primero un dato.
// El segundo y el tercero representan cada uno un BTree.
// El retorno es el arbol creado con los parametros recibidos.
// Crea un BTree con el dato recibido, BTree izquierdo left y BTree derecho right.
// entrada: 5 arbol1 arbol2 , salida: ?
// entrada: 6 arbol1 arbol2 , salida: ?
BTree btree_unir(void * dato, BTree left, BTree right) {
  BTree nuevoNodo = malloc(sizeof(struct _BTNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->dato = dato;
  nuevoNodo->left = left;
  nuevoNodo->right = right;
  return nuevoNodo;
}

// copytree: void* -> void*
// El parametro representa un arbol y se retorna una copia del mismo.
// entrada: arbol1, salida: arbol2
// entrada: arbol1, salida: arbol2
void* copytree(void * dato){
  return (BTree)dato;
}

// destroytree: void* -> _
// El parametro representa un puntero a un arbol.
// Se libera el puntero.
// entrada: *arbol1, salida: _
// entrada: *arbol1, salida: _
void destroytree(void * dato){
  free(dato);
}

// isnum: char* -> int
// El parametro representa una cadena y se retorna un booleano.
// Se retorna 1 si la cadena solo contiene como caracteres a digitos,
// se retorna 0 caso contrario
// entrada: "123 13", salida: 0
// entrada: "12345", salida: 1
// entrada: "123a", salida 0
int isnum(char* a){
  /* Chequeamos que los caracteres sean todos digitos */
	for (int i = 0; i < (int)strlen(a); i++) {
		if (!isdigit(a[i]))
			return 0; // En el caso que alguno no sea digito, se retorna 0.
	}
  /* Si no se retorno 0 en el bucle for, significa que todos
  caracteres son digitos. */
	return 1; // Se retorna 1.
}

// imprimir_inorder: BTree -> _
// El parametro representa un arbol binario aritmetico.
// Se imprime la expresion que el arbol representa.
// entrada: ?, salida: ?
void imprimir_inorder(BTree arbol){
	if(btree_empty(arbol));
	else if(!isnum((char*)arbol->dato)){//se puede cambiar una vez sepamos evaluar
		if(!isnum((char*)(arbol->left->dato))){
			printf("(");
			imprimir_inorder(arbol->left);
			printf(")");
		}
		else
			imprimir_inorder(arbol->left);

		printf(" %s ", (char*)arbol->dato);
		if(!btree_empty(arbol->right)){
			if(!isnum((char*)(arbol->right->dato))){
				printf("(");
				imprimir_inorder(arbol->right);
				printf(")");
			}
			else{
				imprimir_inorder(arbol->right);
			}
		}
  }
  else
		printf("%s", (char*)arbol->dato);

}
