/*
 * Proyecto : LAB1-Desarrollo
 * Archivo  : funciones.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 6 de setiembre de 2022, 11:20
 */

#include "funciones.h"
using namespace std;

double evaluaLaFuncion(double x, double c5, double c4, double c3, double c2,
					   double c1, double c0) {
	double resultado;

	// Se está multiplicando el coeficiente por la potencia de la variable.
	// Luego se suman los valores para obtener el resultado.
	resultado = c5 * potencia(x, 5) + c4 * potencia(x, 4) + c3 * potencia(x, 3) +
			    c2 * potencia(x, 2) + c1 * potencia(x, 1) + c0 * potencia(x, 0);

	return resultado;
}

// Funcion que calcula la potencia de un numero
double potencia(double x, int n) {
	// Inicializado correctamente en 1, si no ingresa al for debido a que el exponente
	// es un 0, el programa retornará correctamente un 1.
	double pot = 1;

	for(int i = 0; i < n; i++) {
		pot *= x;
	}

	return pot;
}
