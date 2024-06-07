/*
 * Proyecto : LAB3-Desarrollo
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 4 de octubre de 2022, 11:11
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include "funciones.h"
#define MAX_PAC 300
using namespace std;

int main(int argc, char** argv) {
	int dniPac[MAX_PAC], cantMedVenc[MAX_PAC]{};
    double totalDev[MAX_PAC]{};
    int cantPac;

	leerCitasYLlenarArreglos(dniPac,cantMedVenc,totalDev,cantPac);
    ordenarArreglos(dniPac,cantMedVenc,totalDev,cantPac);
    emitirReporte(dniPac,cantMedVenc,totalDev,cantPac);

	return 0;
}
