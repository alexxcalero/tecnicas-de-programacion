/*
 * Proyecto : LAB5-Desarrollo
 * Archivo  : funciones.h
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 8 de noviembre de 2022, 11:05
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <fstream>
#include "PersonalAdministrativo.h"
using namespace std;

void leerDatosYActualizarInformacion(char **nombres,char **distritos,
        char **especialidades,char **facultades,int *codigos,int *escalas,
        double *valorDeCreditos,double *credMatriculados,int &cantAlum,
        struct PersonalAdministrativo *administrativos,int &cantAdmin);
char *leerCadenaExacta(ifstream &arch);
void modificarNombres(struct PersonalAdministrativo *administrativos,int cantAdmin,
                     char **nombres,int cantAlum);
void invertirNombre(char *nombre);
void ordenarArreglosDeAlumnos(char **nombres,char **distritos,char **especialidades,
                char **facultades,int *codigos,int *escalas,double *valorDeCreditos,
                double *credMatriculados,int cantAlum);
void cambiarInt(int &datoI, int &datoJ);
void cambiarDouble(double &datoI, double &datoJ);
void cambiarStr(char *&datoI, char *&datoJ);
void emitirReporte(char **nombres,char **distritos,char **especialidades,
            char **facultades,int *codigos,int *escalas,double *valorDeCreditos,
            double *credMatriculados,int &cantAlum,
            struct PersonalAdministrativo *administrativos,int &cantAdmin);
void imprimirCabecerasDeAlumnos(ofstream &arch);
void imprimirCabecerasDeAdministrativos(ofstream &arch);
void imprimirLinea(char c,int tam,ofstream &arch);

#endif /* FUNCIONES_H */
