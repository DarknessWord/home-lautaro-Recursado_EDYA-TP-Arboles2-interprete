#include "glist.h"
#include "operadores.h"
#include "tablaops.h"
#include <stdlib.h>
#include <string.h>

//tabla_crear: _ -> TablaOps
//Se retorna una tabla vacia
//entrada: _ ; salida: NULL
TablaOps tabla_crear(){
  GList tabla = glist_crear();
  return tabla;
}

void operador_destruir(void* dato){
  free(dato);
}

//tabla_destruir: TablaOps -> _
//El parametro representa una tabla de operadores
//Se destruye la tabla
//entrada: tabla ; salida: _
void tabla_destruir(TablaOps tabla){
  glist_destruir(tabla, operador_destruir);
}

//cargar_operador: TablaOps char* int FuncionEvaluacion -> TablaOps
//El primer parametro representa una tabla de operadores
//El segundo parametro representa un simbolo guardado en una cadena
//El tercer parametro representa la aridad de la funcion correspondiente al simbolo
//El cuarto parametro representa la funcion correspondiente al simbolo
//Se agrega a la tabla recibida un Operador con los valores recibidos
//entrada: tabla "+" 2 suma ; salida: tabla
TablaOps cargar_operador(TablaOps tabla, char* simbolo, int aridad,
                                        FuncionEvaluacion eval){
  Operador operator = malloc(sizeof(struct _Operador));
  operator->aridad = aridad;
  operator->simbolo = simbolo;
  operator->eval = eval;
  tabla = glist_agregar_inicio(tabla,operator);
  return tabla;
}

//cargar_operadores_total: TablaOps -> TablaOps
//El parametro representa una tabla de operadores
//Se cargan los operadores en la tabla
//entrada: tabla ; salida: tabla
TablaOps cargar_operadores_total(TablaOps tabla){
  tabla = cargar_operador(tabla, "+", 2, suma);
  tabla = cargar_operador(tabla, "-", 2, resta);
  tabla = cargar_operador(tabla, "--", 1, opuesto);
  tabla = cargar_operador(tabla, "*", 2, producto);
  tabla = cargar_operador(tabla, "/", 2, division);
  tabla = cargar_operador(tabla, "%", 2, modulo);
  tabla = cargar_operador(tabla, "^", 2, potencia);
  return tabla;
}

//aridad_operado: char* Tablaops -> int
//El primer parametro representa el simbolo de un operador
//El segundo parametro representa una tabla de operadores
//Se retorna la aridad de la funcion del simbolo segun esta
//guardado en la tabla
//entrada: "*" tabla ; salida: 2
int aridad_operador(char * operador, TablaOps tabla){
	int encontrado = 0;
	int aridad;
	for(TablaOps aux = tabla;aux != NULL && encontrado != 1;aux = aux->sig){
		if(!strcmp(operador,((Operador)aux->dato)->simbolo)){
			encontrado = 1;
			aridad = ((Operador)aux->dato)->aridad;}
	}
	return aridad;
}

//buscar_operador: Tablaops char* -> int
//El primer parametro representa una tabla de operadores
//El segundo parametro representa el simbolo de un operador
//Se verifica que el operador este guardado en la tabla
//entrada: tabla "*" ; salida: 1
int buscar_operador(TablaOps tabla, char * simbolo){
  int encontrado = 0;
  for(TablaOps aux = tabla;aux != NULL && encontrado != 1;aux = aux->sig){
    if(!strcmp(((Operador)aux->dato)->simbolo,simbolo))
      encontrado = 1;}
  return encontrado;
}
