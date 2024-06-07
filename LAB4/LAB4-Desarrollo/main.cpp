/*
 * Proyecto : LAB4-Desarrollo
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 25 de octubre de 2022, 11:07
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include "funciones.h"
using namespace std;

int main(int argc, char** argv) {
	ifstream archComen("Comentarios.txt",ios::in);
    if(!archComen.is_open()) {
        cout << "No se pudo abrir el archivo Comentarios.txt" << endl;
        exit(1);
    }

    ifstream archPaises("Paises.txt",ios::in);
    if(!archPaises.is_open()) {
        cout << "No se pudo abrir el archivo Paises.txt" << endl;
        exit(1);
    }

    ofstream archRep("ReportePreprocesamiento.txt",ios::out);
    if(!archRep.is_open()) {
        cout << "No se pudo abrir el archivo ReportePreprocesamiento.txt" << endl;
        exit(1);
    }
	
	procesarComentariosYEmitirReporte(archComen,archPaises,archRep);

	return 0;
}
