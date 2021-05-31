#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interprete.h"
#include "tablaops.h"

int main(){
  TablaOps tabla = tabla_crear();
  tabla = cargar_operadores_total(tabla);
  //interprete//
  interprete(tabla);
  //almacena en el arbol//
  tabla_destruir(tabla); 
  return 0;
}
