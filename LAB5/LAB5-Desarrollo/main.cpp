/*
 * Proyecto : LAB5-Desarrollo
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 8 de noviembre de 2022, 11:04
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include "funciones.h"
#include "PersonalAdministrativo.h"
#define MAX_ALUM 100
#define MAX_ADMIN 200
using namespace std;

int main(int argc, char** argv) {
	// Alumnos
    char *nombres[MAX_ALUM], *distritos[MAX_ALUM];
    char *especialidades[MAX_ALUM], *facultades[MAX_ALUM];
    int codigos[MAX_ALUM], escalas[MAX_ALUM];
    double valorDeCreditos[MAX_ALUM], credMatriculados[MAX_ALUM];
    int cantAlum;

	// Personal Administrativo
    struct PersonalAdministrativo administrativos[MAX_ADMIN];
    int cantAdmin;

	// Leo el csv y lleno los arreglos
    leerDatosYActualizarInformacion(nombres,distritos,especialidades,facultades,
                                    codigos,escalas,valorDeCreditos,credMatriculados,
                                    cantAlum,administrativos,cantAdmin);

    modificarNombres(administrativos,cantAdmin,nombres,cantAlum);

    ordenarArreglosDeAlumnos(nombres,distritos,especialidades,facultades,codigos,
                             escalas,valorDeCreditos,credMatriculados,cantAlum);

    emitirReporte(nombres,distritos,especialidades,facultades,
                  codigos,escalas,valorDeCreditos,credMatriculados,
                  cantAlum,administrativos,cantAdmin);
	
	return 0;
}
