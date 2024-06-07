/*
 * Proyecto : LAB2-Desarrollo
 * Archivo  : funciones.h
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 20 de septiembre de 2022, 11:18
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <fstream>
using namespace std;

void procesarDatosEImprimirReporte(ifstream &,ifstream &,ifstream &,ofstream &);
void imprimirCabeceraPrincipal(ofstream &);
void leerEImprimirDatosDelMedico(int ,double &,ifstream &,ofstream &);
void imprimirCabecerasDeMedicos(ofstream &);
void leerEImprimirNombreDelMedico(ifstream &,ofstream &);
char pasarLetraAMayus(char);
void imprimirCabecerasSecundarias(ofstream &);
void procesarCitasPorMedico(int,double,double &,double &,ifstream &,ifstream &,ofstream &);
void leerEImprimirNombreDelPaciente(int,ifstream &,ofstream &);
void imprimirTotalDeGastosPorCitas(double,ofstream &);
void imprimirBlancos(ofstream &, int);
void imprimirLinea(ofstream &,char c,int);

#endif /* FUNCIONES_H */
