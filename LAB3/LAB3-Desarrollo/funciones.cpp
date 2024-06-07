/*
 * Proyecto : LAB3-Desarrollo
 * Archivo  : funciones.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 4 de octubre de 2022, 11:12
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include "funciones.h"
#define CANT_LIN 120
#define NO_ENCONTRADO -1
using namespace std;

void leerCitasYLlenarArreglos(int *dniPac,int *cantMedVenc,double *totalDev,int &cantPac) {
    ifstream archCit("Citas.txt",ios::in);
    if(!archCit.is_open()) {
        cout << "Error en el archivo Citas.txt" << endl;
        exit(1);
    }

    int dniArch, dd,mm,aa, codMed,cantMed, pos, estaVencido;
    double precMed;
    char c;

    cantPac = 0;

    while(1) {
        archCit >> dniArch;
        if(archCit.eof()) break;
        //archCit >> dd >> c >> mm >> c >> aa;

        while(archCit.get() == ' '); // Saltamos la fecha, ya que no es
        while(archCit.get() != ' '); // relevante para el problema

        pos = buscarPaciente(dniArch,dniPac,cantPac);

        while(1) {
            archCit >> codMed >> cantMed >> precMed;

            estaVencido = verificarMedicamenteVencido(codMed);

            if(estaVencido == 1) {
                if(pos == NO_ENCONTRADO) {
                    dniPac[cantPac] = dniArch;
                    cantMedVenc[cantPac] += cantMed;
                    totalDev[cantPac] += cantMed * precMed;
                    cantPac++;
                } else {
                    cantMedVenc[pos] += cantMed;
                    totalDev[pos] += cantMed * precMed;
                }
            }

            if(archCit.get() == '\n') break;
        }
    }
}

int buscarPaciente(int dniArch,int *dniPac,int cantPac) {
    for(int pos = 0; pos < cantPac; pos++)
        if(dniArch == dniPac[pos])
            return pos;
    return NO_ENCONTRADO;
}

int verificarMedicamenteVencido(int codMed) {
    int dig;
    dig = codMed % 1000;
    if((dig > 235 && dig < 333) || (dig > 547 && dig < 743))
        return 1;
    else
        return 0;
}

void ordenarArreglos(int *dniPac,int *cantMedVenc,double *totalDev,int cantPac) {
    for(int i = 0; i < cantPac - 1; i++)
        for(int j = i + 1; j < cantPac; j++)
            if(totalDev[i] < totalDev[j]) {
                cambiarInt(dniPac[i],dniPac[j]);
                cambiarInt(cantMedVenc[i],cantMedVenc[j]);
                cambiarDouble(totalDev[i],totalDev[j]);
            }
}

void cambiarInt(int &a, int &b) {
    int aux = a;
    a = b;
    b = aux;
}

void cambiarDouble(double &a, double &b) {
    double aux = a;
    a = b;
    b = aux;
}

void emitirReporte(int *dniPac,int *cantMedVenc,double *totalDev,int cantPac) {
    ofstream archRep("ReporteDeMontosADevolverPorPaciente.txt",ios::out);
    if(!archRep.is_open()){
        cout << "Error en el archivo de ReporteDeMontosADevolverPorPaciente.txt" << endl;
        exit(1);
    }
    archRep.precision(4);
    archRep << fixed;
    imprimirTitulo(archRep);
    imprimirCabeceras(archRep);
    for(int i = 0; i < cantPac; i++) {
        archRep << right << setw(15) << dniPac[i] << setw(27) << cantMedVenc[i];
        archRep << right << setw(40) << totalDev[i] << endl;
    }

    imprimirLinea('=',CANT_LIN,archRep);

    int totMedDev;
    double montoTotDev;

    totMedDev = calcularTotalDeMedicamentosDevueltos(cantMedVenc,cantPac);
    montoTotDev = calcularMontoTotalDevuelto(totalDev,cantPac);

    archRep << "CANTIDAD TOTAL DE MEDICAMENTOS DEVUELTOS:" <<
            setw(40) << totMedDev << endl;
    archRep.precision(2);
    archRep << fixed;
    archRep << "MONTO TOTAL DEVUELTO:" << setw(60) << montoTotDev << endl;
    archRep << "Promedio ponderado devuelto por paciente por cantidad de medicamentos:";

    double promPond;
    promPond = hallarPromPond(totMedDev,cantMedVenc,totalDev,cantPac);
    archRep << setw(11) << promPond << endl;
    imprimirLinea('=',CANT_LIN,archRep);
}

void imprimirTitulo(ofstream &archRep) {
    archRep << right << setw(60) << "CLINICA PSICOLOGICA TP." << endl;
    archRep << right << setw(68) << "RELACION DE MONTOS A DEVOLVER POR PACIENTE" << endl;
    imprimirLinea('=',CANT_LIN,archRep);
}

void imprimirCabeceras(ofstream &archRep) {
    archRep << right << setw(15) << "PACIENTE";
    archRep << right << setw(44) << "CANTIDAD DE MEDICAMENTOS VENCIDOS";
    archRep << right << setw(25) << "TOTAL A DEVOLVER";
    archRep << endl;
    imprimirLinea('-',CANT_LIN,archRep);
}

int calcularTotalDeMedicamentosDevueltos(int *cantMedVenc,int cantPac) {
    int total = 0;
    for(int i = 0; i < cantPac; i++)
        total += cantMedVenc[i];
    return total;
}

double calcularMontoTotalDevuelto(double *totalDev,int cantPac) {
    double total = 0;
    for(int i = 0; i < cantPac; i++)
        total += totalDev[i];
    return total;
}

double hallarPromPond(int cantidadTot,int *cantMedVenc,double *totalDev,int cantPac) {
    double producto, suma = 0;
    for(int i = 0; i < cantPac; i++) {
        producto = cantMedVenc[i] * totalDev[i];
        suma += producto;
    }
    return suma / cantidadTot;
}

void imprimirLinea(char c,int tam,ofstream &archRep) {
    for(int i = 0; i < tam; i++) archRep.put(c);
    archRep << endl;
}
