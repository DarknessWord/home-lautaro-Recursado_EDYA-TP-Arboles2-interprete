#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "glist.h"
#include "btree.h"
#include "interprete.h"
#include "pila.h"
#include "tablaops.h"
#include "operadores.h"
#define MAXINT 150

// destruir_char: void* -> _
// El parametro representa una cadena
// entrada: "hola", salida: _
void destruir_char(void* dato){
  free(dato);
}

// destruir_arbol_alias: void* -> _
// El parametro representa una estructura arbolalias la cual posee como
// atributos un arbol y un alias
// Se libera la memoria ocupada por la estructura y sus atributos
// entrada: arbolAlias, salida: _
void destruir_arbol_alias(void* dato){
  ArbolAlias aa = (ArbolAlias)dato;
  btree_destruir(aa->arbol, destruir_char);
  free(aa->alias);
  free(aa);
}

// verificar_alias: char* -> int
// El parametro representa un alias.
// Se verifica que el alias cumpla con ciertas condiciones.
// entrada: "4alias", salida: 0
// entrada: "ali as", salida: 0
// entrada: "alias", salida: 1
// entrada: "alias4", salida: 1
// entrada: "ali4as", salida: 1
int verificar_alias(char* alias){
  if (!isalpha(alias[0]) && !strcmp(alias[0], "ñ"))//si no empieza con alguna letra
    return 0; //no es valida

  for (int i = 1; i < (int)strlen(alias); i++) { //si tiene algun caracter
    if (!isalnum(alias[i]) && strcmp(alias[i],"ñ"))            //no alfanumerico
      return 0; //no es valida
  }

  if (!strcmp(alias, "evaluar") ||     //si es igual a algun comando
      !strcmp(alias, "imprimir") ||
      !strcmp(alias, "salir") ||
      !strcmp(alias, "cargar")){
    return 0; //no es valida
  }

  return 1; //si no cumple ninguna de las condiciones anteriores es valida
}

// imprimir: GList char* -> _
// El primer parametro representa una lista de arboles
// El segundo parametro representa un alias
// Se imprime el arbol asociado al alias
// entrada: listaArboles "alias", salida: _
void imprimir(GList listaArboles, char * al){ //agregar token
  BTree arbol = btree_crear(); //
  for(GNodo * nodo = listaArboles;nodo != NULL && arbol == NULL;
                                                nodo = nodo->sig){

    if (!strcmp(((ArbolAlias)(nodo->dato))->alias, al)){
      arbol = ((ArbolAlias)nodo->dato)->arbol;
    }
  }
  if(arbol != NULL){
    imprimir_inorder(arbol);
    puts("");
  }
  else
    printf("No hay ninguna expresion con el alias \"%s\" \n", al);
}


int verificar_arbol(char * operador,BTree nodoizq, BTree nododer,TablaOps tabla){
  int aridad = 0;
  if(nodoizq != NULL)
    aridad++;
  if(nododer != NULL)
    aridad++;
  if(aridad != aridad_operador(operador,tabla)){
    printf("Las entradas del operador %s no coiciden con su aridad", operador);
    return 1;
  }
  return 0;
}

int evaluar_arbol(BTree arbol, TablaOps tabla){
  char * simbolo = (char *)arbol->dato;
  if (isnum(simbolo)){
    return atoi(simbolo);
  }
  FuncionEvaluacion f;
  int aridad,encontrado = 0, arg[2];
  for(TablaOps aux = tabla; aux != NULL && encontrado != 1;aux = aux->sig){ // MATCHEA EL SIMBOLO EN LA TABLA
    if(!strcmp(((Operador)aux->dato)->simbolo, simbolo)){
      f = ((Operador)aux->dato)->eval;
      aridad = ((Operador)aux->dato)->aridad;
      encontrado = 1;}
  }
  arg[0] = evaluar_arbol(arbol->left, tabla);
  if(aridad == 2)
    arg[1] = evaluar_arbol(arbol->right, tabla);
  return f(arg);
}

BTree buscar_arbol(GList listaArboles, char * alias){
  BTree arbol = btree_crear();
  for(GNodo * nodo = listaArboles;nodo != NULL && arbol == NULL; nodo = nodo->sig){
    if (!strcmp(((ArbolAlias)(nodo->dato))->alias, alias))
      arbol = ((ArbolAlias)nodo->dato)->arbol;
  }
  return arbol;
}

void cargar(GList * listaArboles, char * alias, char * expresion, TablaOps tabla){
  Pila pilaArboles = pila_crear();
  int error = 0,pilalong = 0;
  for(char * iter = strtok(expresion, " "); iter != NULL && error != 1; iter = strtok(NULL, " ")){
    char * simbolo = malloc(sizeof(char) * (strlen(iter) + 1));
    strcpy(simbolo, iter);
    if(isnum(simbolo)){
      BTree arbol = btree_crear();
      arbol = btree_unir(simbolo, NULL, NULL);
      pila_apilar(&pilaArboles, arbol);
      pilalong++;
    }
    else if(buscar_operador(tabla, simbolo)){
	    BTree arbol = btree_crear(), nodo1, nodo2 = NULL;
      if(!pilalong){ // No hay ningun dato en la pila
        puts("Inserte un entero o una expresion seguido del operador");
        error = 1;}
      else{
        nodo1 = (BTree)pila_tope(pilaArboles, copytree);
        pila_desapilar(&pilaArboles);
        if(pilalong == 1)
          arbol = btree_unir(simbolo, nodo1, NULL);

        else{
          nodo2 = (BTree)pila_tope(pilaArboles, copytree);
          pila_desapilar(&pilaArboles);
        }

        pila_apilar(&pilaArboles, arbol);
        error = verificar_arbol(simbolo, nodo1, nodo2, tabla);
      }
	    switch(pilalong){
	      case 0:
		      puts("Inserte un entero o una expresion seguido del operador");
		      error = 1;
		      break;
	      case 1:
	        nodo1 = (BTree)pila_tope(pilaArboles, copytree);
		      pila_desapilar(&pilaArboles);
		      error = verificar_arbol(simbolo, nodo1, NULL, tabla);
		      arbol = btree_crear();
		      arbol = btree_unir(simbolo, nodo1, NULL);
		      pila_apilar(&pilaArboles, arbol);
		      break;
		    default:
          nodo1 = (BTree)pila_tope(pilaArboles, copytree);
          pila_desapilar(&pilaArboles);
          nodo2 = (BTree)pila_tope(pilaArboles, copytree);
          pila_desapilar(&pilaArboles);
          error = verificar_arbol(simbolo, nodo1, nodo2, tabla);
          arbol = btree_crear();
	        arbol = btree_unir(simbolo, nodo2, nodo1);
	        pila_apilar(&pilaArboles, arbol);
	        pilalong--;
      }
    }
    else{
      puts("Caracter distinto de operadores y operando cargados");
      error = 1;
    }
  }
  BTree raiz = (BTree)pila_tope(pilaArboles,copytree);
  if(error){
    btree_destruir(raiz, destruir_char);
    //pila_destruir(pila_arboles, btree_destruir_char);
    //puede quedar memoria
  }
  else{
    pila_desapilar(&pilaArboles);
    pila_destruir(pilaArboles, destruir_char);
    ArbolAlias aliasTree = malloc(sizeof(struct _arbolalias));
    aliasTree->arbol = raiz;
    aliasTree->alias = malloc(sizeof(char) * (strlen(alias)+1));
    aliasTree->alias = strcpy(aliasTree->alias, alias);
    *listaArboles = glist_agregar_inicio(*listaArboles, aliasTree);
  }
}

void liberar_lista_arboles(GList listaArboles){
  glist_destruir(listaArboles, destruir_arbol_alias);
}

void interprete(TablaOps tabla){
  char entrada[MAXINT] = "NULL"; // char* que guarda lo recibido por consola
  GList listaArboles = glist_crear(); // lista donde se guardan los ArbolAlias

  puts("Ingresar comando"); // mensajes de instruccion
  puts("ingresar \"salir\" para terminar el programa");
  fgets(entrada, MAXINT, stdin); // se lee lo recibido por consola y
                                 // se guarda en entrada

  while(strcmp(entrada, "salir\n")){ // si se recibe "salir"
                                     // se cierra el programa
    char entradaCopia[MAXINT]; //entrada por consola
    strcpy(entradaCopia, entrada); //copiado de
		char * token = strtok(entrada," ");
    int flag = 1;
    if(!strcmp(token, "imprimir")){ //"alias"
      token = strtok(NULL, "\n");
      imprimir(listaArboles, token);
		}

    else if(!strcmp(token, "evaluar")){
      token = strtok(NULL, "\n");
			printf("%d\n", evaluar_arbol(buscar_arbol(listaArboles, token), tabla));
		}
    else if(strstr(entradaCopia, "= cargar") != NULL){
      if (verificar_alias(token)){ //"asdasdas = cargar 2 3 +"
        char* alias = token;
        token = strtok(NULL, " ");
        if (strcmp(token, "="))
          flag = 0;
        token = strtok(NULL, " ");
        if (strcmp(token, "cargar"))
          flag = 0;
        token = strtok(NULL, "\n");
        if (flag){
          char * expresion = token;
          cargar(&listaArboles, alias, expresion,tabla);
        }
        else
          puts("Mal uso del comando cargar");
        }
      else
        puts("Alias no valido");
    }

    else{
      puts("Comando incorrecto");
    }

    puts("Ingresar comando");
    fgets(entrada, MAXINT, stdin);
  }
  liberar_lista_arboles(listaArboles);
}
