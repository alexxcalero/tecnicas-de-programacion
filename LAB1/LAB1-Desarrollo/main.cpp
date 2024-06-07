/*
 * Proyecto : LAB1-Desarrollo
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 6 de setiembre de 2022, 11:02
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include "funciones.h"
#define EXACTITUD 0.000001
using namespace std;

int main(int argc, char** argv) {
	// Declaracion de variables
	double c5, c4, c3, c2, c1, c0;
	double limiteInferior, limiteSuperior;
	double h, x1, x2, y1, y2;
	double area = 0.0, areaAnterior, longitud = 0.0, longitudAnterior;
	int numIntervalos = 0, i;
	bool fin = false;

	cout.precision(7);  // Defino la precision de 7 numeros
	cout << fixed;  // Uso fixed, para que precision(7) sea utilizado solo para la parte decimal

	cout << "Ingrese los coeficientes c5, c4, c3, c2, c1 y c0: ";
	cin >> c5 >> c4 >> c3 >> c2 >> c1 >> c0;

	cout << endl << "Ingrese los limites inferior y superior: ";
	cin >> limiteInferior >> limiteSuperior;
	cout << endl << left << setw(18) << "Intervalos" << setw(20) << "Area"
			<< setw(20) << "Longitud" << endl;

	while(not fin) {
		areaAnterior = area;
		longitudAnterior = longitud;
		area = longitud = 0;
		numIntervalos++;
		h = (limiteSuperior - limiteInferior) / numIntervalos;
		x1 = limiteInferior;

		for(i = 1; i <= numIntervalos; i++) {
			x2 = x1 + h;
			y1 = evaluaLaFuncion(x1, c5, c4, c3, c2, c1, c0);
			y2 = evaluaLaFuncion(x2, c5, c4, c3, c2, c1, c0);
			area += (y1 + y2) * h / 2;
			longitud += sqrt(potencia(y2 - y1, 2) + potencia(h, 2));
			x1 = x2;
		}

		cout << right << setw(7) << numIntervalos << setw(20) << area
				<< setw(20) << longitud << endl;

		// Corroboramos si se ha llegado al fin de los intervalos, viendo si la restas
		// de las areas y longitudes son menores a la exactitud brindada
		fin = fabs(area - areaAnterior) < EXACTITUD or
			  fabs(longitud - longitudAnterior) < EXACTITUD;
	}

	//cout << endl;
	cout << endl;
	// Las dos líneas de código siguientes han sido agregadas para responder a la pregunta 6
	// Este cout.precision(3); y cout << fixed; , solo será aplicado a las impresiones de resultados finales
	cout.precision(3);
	cout << fixed;
	cout << left << setw(25) << "Area bajo la curva = " << right << setw(10) << area << endl;
	cout << left << setw(25) << "Longitud de la curva = " << right << setw(10) << longitud << endl;

	return 0;
}
