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
  ArbolAlias aa = (ArbolAlias)dato; // Se castea al tipo ArbolAlias
  btree_destruir(aa->arbol, destruir_char);//Destrucción del arbol y símbolos
//  free(aa->alias);//Destrucción del alias
  free(aa);//Destrucción de ArbolAlias
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
  if (!isalpha(alias[0]))//si no empieza con alguna letra
    return 0; //no es valida

  for (int i = 1; i < (int)strlen(alias); i++) { //si tiene algun caracter
    if (!isalnum(alias[i]))            //no alfanumerico
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

BTree buscar_arbol(GList listaArboles, char * alias){
  BTree arbol = btree_crear();
  for(GNodo * nodo = listaArboles;nodo != NULL && arbol == NULL; nodo = nodo->sig){
    if (!strcmp(((ArbolAlias)(nodo->dato))->alias, alias))
      arbol = ((ArbolAlias)nodo->dato)->arbol;
  }
  return arbol;
}





// imprimir: GList char* -> _
// El primer parametro representa una lista de arboles
// El segundo parametro representa un alias
// Se imprime el arbol asociado al alias
// entrada: listaArboles "alias", salida: _
void imprimir(GList listaArboles, char * alias){ //agregar token
  BTree arbol = buscar_arbol(listaArboles,alias);
  if(arbol != NULL){
    imprimir_inorder(arbol);
    puts("");
  }
  else
    printf("ERROR: No hay ninguna expresion con el alias \"%s\" \n", alias);
}



int evaluar_arbol(BTree arbol, TablaOps tabla){
  char * simbolo = (char *)arbol->dato;//Se inicializa el caracter
  if (isnum(simbolo)){//Si es un número, se devuelve el número como int
    return atoi(simbolo);
  }
  //Si es un operador, se matchea el simbolo en la tablaops para sacar sus datos
  FuncionEvaluacion f;
  int aridad,encontrado = 0, arg[2];
  //f: FuncionEvaluacion que está cargada en TablaOps, y va a aplicarse a sus hijos
  //aridad: aridad de f
  //arg: arreglo que guarda las entradas de f
  //encontrado: bandera que detiene el bucle cuando encuentra el dato
  for(TablaOps aux = tabla; aux != NULL && encontrado != 1;aux = aux->sig){
  //Se inicia un bucle en TablaOps hasta encontrar el operador
    if(!strcmp(((Operador)aux->dato)->simbolo, simbolo)){
      f = ((Operador)aux->dato)->eval;
      aridad = ((Operador)aux->dato)->aridad;
      encontrado = 1;}
  }
  arg[0] = evaluar_arbol(arbol->left, tabla);
  if(aridad == 2)
    arg[1] = evaluar_arbol(arbol->right, tabla);
  //Se evalúan recursivamente el arbol izquierdo, y el derecho en el caso de ser
  //aridad 2
  return f(arg); //Retorna la funcion evaluada con arg
}

int verificar_arbol(char * operador,BTree nodoizq, BTree nododer,TablaOps tabla){
  int aridad = 0;
  if(nodoizq != NULL)
    aridad++;
  if(nododer != NULL){
    if(!strcmp(operador,"/")){
      if(evaluar_arbol(nododer,tabla) == 0){
        puts("ERROR: División por 0");
        return 1;
      }
    }
    aridad++;}
  if(aridad != aridad_operador(operador,tabla)){
    printf("ERROR: Las entradas del operador %s no coiciden con su aridad", operador);
    puts("");
    return 1;
  }
  return 0;
}


void btree_destruir_char(void * arbol){
  btree_destruir((BTree)arbol,destruir_char);
}


ArbolAlias arbolalias_agregar(BTree raiz,char * alias){
  ArbolAlias aliasTree = malloc(sizeof(struct _arbolalias));
  aliasTree->arbol = raiz;
  strcpy(aliasTree->alias, alias);
  return aliasTree;
}


void cargar(GList * listaArboles, char * alias, char * expresion, TablaOps tabla){
  Pila pilaArboles = pila_crear(); //Se crea la pila auxiliar
  int error = 0,pilalong = 0;
  //error: es una bandera que detiene el bucle cuando encuentra un error
  //pilalong: índice que contabiliza la longitud actual de la pila
  char * simbolo;
  for(char * iter = strtok(expresion, " "); iter != NULL && error != 1;
   iter = strtok(NULL, " ")){
  //Se itera en el string expresion, tokenizandolo por espacios " " , hasta que
  //no quede nada en el string, es decir NULL, o se encuentre un error
    simbolo = malloc(sizeof(char)*(strlen(iter)+1));
    simbolo = strcpy(simbolo, iter); //simbolo es una copia del token
    //el cual representa un símbolo de la expresión (entero u operador)
    BTree arbol = btree_crear(); //Se crea el arbol donde se guardará la expresion

    if(isnum(simbolo)){//Si el símbolo es un entero, entonces se guardará una
      //hoja del arbol con el entero guardado como string
      arbol = btree_unir(simbolo, NULL, NULL); // Se crea la hoja con el entero
      pila_apilar(&pilaArboles, arbol);// Se apila la hoja a la pila auxiliar
      pilalong++;// Se aumenta la longitud de la pila
    }

    else if(buscar_operador(tabla, simbolo)){//Si el símbolo es un operador
      //que está cargado en TablaOps, se almacena como raiz cuyos hijos
      //son los que estan cargado en la pila auxiliar
	    BTree nodo1, nodo2 = NULL;//Se inicializan los nodos hijos

      if(!pilalong){ // No hay ningun dato en la pila, ejemplo: alias = cargar +
        puts("ERROR: Inserte un entero o una expresion seguido del operador");
        free(simbolo);
        error = 1;//Como no hay operadores de aridad 0, se devuelve error
      }

      else{//Hay al menos un dato en la pila
        nodo1 = pila_tope(pilaArboles, copytree); //Se inicializa un hijo
        //con el tope de la pila,es decir el último arbol que se insertó
        pila_desapilar(&pilaArboles);

        if(pilalong == 1) //Hay un solo elemento en la pila, ejemplo: alias = cargar 5 --
          arbol = btree_unir(simbolo, nodo1, nodo2);//Como nodo2 ya está
          //inicializado como NULL, se crea un arbol con la raíz como símbolo
          //y nodo1 como único hijo izquierdo

        else{ //Mas de un elemento en la pila, ejemplo: alias = cargar 4 3 +
          nodo2 = pila_tope(pilaArboles, copytree);//Se inicializa un hijo
          //con el tope de la pila,es decir el penúltimo arbol que se insertó
          pila_desapilar(&pilaArboles);
          arbol = btree_unir(simbolo, nodo2, nodo1); //Se crea un arbol con símbolo
          //como raíz, y nodo2, nodo1 como hijos izquierdo y derecho respectivamente
          pilalong--;//Al desapilar 2 veces y apilar 1 vez, la longitud de la pila
          //se reduce en 1
        }

        pila_apilar(&pilaArboles, arbol); // Se apila el arbol con 1 o 2 hijos
        error = verificar_arbol(simbolo, nodo2, nodo1, tabla);//Se verifica si
        //el arbol se definió con la aridad correspondiente al símbolo
      }
    }
    else{//Si el símbolo no es un número ni un operador cargado se devuelve el error
      puts("ERROR: Caracter distinto de operadores y operando cargados");
      free(simbolo);//Se libera el caracter
      error = 1;
    }
  }
  BTree raiz = (BTree)pila_tope(pilaArboles,copytree);//Una vez que termina el
  //bucle, el arbol final queda como único elemento de la pila, por lo que solo
  //queda inicializarla a BTree
  if(pilalong > 1){//Si hay otro elemento en la pila además del arbol final,
    //se debe a que quedó un numero sin operador, por lo que se devuelve el error
    puts("ERROR: Número sin ningun operador delante");
    error = 1;
  }
  if(error)//Si hubo algún error durante toda la carga, se procede a eliminar
  //todos los espacios de memorias asignados
    pila_destruir(pilaArboles, btree_destruir_char);

  else{// Si no hubo errores, se almacena el alias y el arbol generado
    pila_desapilar(&pilaArboles);
    ArbolAlias aliasTree = arbolalias_agregar(raiz,alias);//Se carga el arbol y
    //alias en la estructura ArbolAlias
    *listaArboles = glist_agregar_inicio(*listaArboles, aliasTree);//Se almacena
    //la estructura ArbolAlias en la lista de árboles
  }
}

void liberar_lista_arboles(GList listaArboles){
  glist_destruir(listaArboles, destruir_arbol_alias);
}

void interpretar(TablaOps tabla){
  char entrada[MAXINT] = "NULL"; // char* que guarda lo recibido por consola
  GList listaArboles = glist_crear(); // lista donde se guardan los ArbolAlias

  puts("Ingresar comando"); // mensajes de instruccion
  puts("ingresar \"salir\" para terminar el programa");
  fgets(entrada, MAXINT, stdin); // se lee lo recibido por consola y
                                 // se guarda en entrada

  while(strcmp(entrada, "salir\n")){ // si se recibe "salir"
                                     // se cierra el programa
    char entradaCopia[MAXINT]; //entrada por consola
    strcpy(entradaCopia, entrada);
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
        if(buscar_arbol(listaArboles,alias) != NULL){
          puts("ERROR: Alias ya utilizado");
          flag = 0;
        }
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
          puts("ERROR: Mal uso del comando cargar");
        }
      else
        puts("ERROR: Alias no valido");
    }

    else{
      puts("ERROR: Comando incorrecto");
    }

    puts("Ingresar comando");
    fgets(entrada, MAXINT, stdin);
  }
  liberar_lista_arboles(listaArboles);
}
