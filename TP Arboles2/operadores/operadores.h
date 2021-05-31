#ifndef __OPERADORES_H__
#define __OPERADORES_H__

typedef int(*FuncionEvaluacion)(int *args);

/**
 * Retorna la suma de los primeros 2 elementos del arreglo.
 */
int suma(int* args);

/**
 * Retorna la resta de los primeros 2 elementos del arreglo, el primero menos el
 * segundo
 */
int resta(int* args);

/**
 * Retorna el opuesto de un argumento.
 */

int opuesto(int* args);

/**
 * Retorna el producto de dos argumentos.
 */

int producto(int* args);

/**
 * Retorna la división de dos argumentos, el primero dividido el segundo.
 */

int division(int* args);

/**
 * Retorna el módulo de dos argumento, el primero módulo el segundo.
 */

int modulo(int* args);

/**
 * Retorna la potencia de dos argumentos, el primero elevado al segundo.
 */
int potencia_aux(int a,int b);

/**
 * Retorna la potencia de dos argumentos, el primero elevado al segundo.
 */
int potencia(int* args);


#endif/**__OPERADORES_H__*/