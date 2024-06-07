/*
 * Proyecto : LAB2-Desarrollo
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 20 de septiembre de 2022, 11:18
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include "funciones.h"
using namespace std;

int main(int argc, char** argv) {
	ifstream archMed("Medicos.txt",ios::in);
    if(!archMed.is_open()) {
        cout << "ERROR: El archivo Medicos.txt no se pudo abrir." << endl;
        exit(1);
    }

    ifstream archPac("Pacientes.txt",ios::in);
    if(!archPac.is_open()) {
        cout << "ERROR: El archivo Pacientes.txt no se pudo abrir." << endl;
        exit(1);
    }

    ifstream archCit("Citas.txt",ios::in);
    if(!archCit.is_open()) {
        cout << "ERROR: El archivo Citas.txt no se pudo abrir." << endl;
        exit(1);
    }

    ofstream archRep("ReporteDeCitasPorMedicos.txt",ios::out);
    if(!archRep.is_open()) {
        cout << "ERROR: El archivo ReporteDeCitasPorMedicos.txt no se pudo abrir." << endl;
        exit(1);
    }

	procesarDatosEImprimirReporte(archMed,archPac,archCit,archRep);

	return 0;
}
