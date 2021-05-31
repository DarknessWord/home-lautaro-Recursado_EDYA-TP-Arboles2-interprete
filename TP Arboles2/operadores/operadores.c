#include "operadores.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

int suma(int* args){
  return args[0] + args[1];
}

int resta(int* args){
  return args[0] - args[1];
}

int opuesto(int* args){
  return -args[0];
}

int producto(int* args){
  return args[0] * args[1];
}

int division(int* args){
  return args[0] / args[1];
}

int modulo(int* args){
  return args[0] % args[1];
}

int potencia_aux(int a, int b){
  int c = (int) pow(a,b);
  return c;
}

int potencia(int* args){
  return potencia_aux(args[0], args[1]);
}
