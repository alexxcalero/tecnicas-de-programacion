/*
 * Proyecto : LAB3-Desarrollo
 * Archivo  : funciones.h
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 4 de octubre de 2022, 11:12
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <fstream>
using namespace std;

void leerCitasYLlenarArreglos(int *dniPac,int *cantMedVenc,double *totalDev,int &cantPac);
int buscarPaciente(int dniArch,int *dniPac,int cantPac);
int verificarMedicamenteVencido(int codMed);
void ordenarArreglos(int *dniPac,int *cantMedVenc,double *totalDev,int cantPac);
void cambiarInt(int &a, int &b);
void cambiarDouble(double &a, double &b);
void emitirReporte(int *dniPac,int *cantMedVenc,double *totalDev,int cantPac);
void imprimirTitulo(ofstream &archRep);
void imprimirCabeceras(ofstream &archRep);
int calcularTotalDeMedicamentosDevueltos(int *cantMedVenc,int cantPac);
double calcularMontoTotalDevuelto(double *totalDev,int cantPac);
double hallarPromPond(int cantidadTot,int *cantMedVenc,double *totalDev,int cantPac);
void imprimirLinea(char c,int tam,ofstream &archRep);

#endif /* FUNCIONES_H */
