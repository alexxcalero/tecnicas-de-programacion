/*
 * Proyecto : LAB2-Desarrollo
 * Archivo  : funciones.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 20 de septiembre de 2022, 11:18
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include "funciones.h"
#define CANTLIN 150
#define CANTLET 50
using namespace std;

void procesarDatosEImprimirReporte(ifstream &archMed,ifstream &archPac,
                                   ifstream &archCit,ofstream &archRep) {
    // Ajusto la cantidad de decimales para todo el reporte
    archRep.precision(2);
    archRep << fixed;
    imprimirCabeceraPrincipal(archRep);
    int codMed;
    double tarifa, totGastDeCit,totRecaudado = 0;
    while(1) {
        archMed >> codMed;
        if(archMed.eof()) break;
        leerEImprimirDatosDelMedico(codMed,tarifa,archMed,archRep);
        imprimirCabecerasSecundarias(archRep);
        totGastDeCit = 0;  // Inicializo en 0 para cada médico
        procesarCitasPorMedico(codMed,tarifa,totGastDeCit,totRecaudado,archCit,
                               archPac,archRep);
        imprimirLinea(archRep,'-',CANTLIN);
        imprimirTotalDeGastosPorCitas(totGastDeCit,archRep);
    }
    archRep << "TOTAL RECAUDADO POR LA CLINICA:" << setw(12) << totRecaudado << endl;
    imprimirLinea(archRep,'=',CANTLIN);
}

void imprimirCabeceraPrincipal(ofstream &archRep) {
    archRep << setw(75) << "CLINICA PSICOLOGICA TP." << endl;
    archRep << setw(78) << "RELACION DE CITAS POR MEDICO" << endl;
    imprimirLinea(archRep,'=',CANTLIN);
}

void leerEImprimirDatosDelMedico(int codMed,double &tarifa,ifstream &archMed,
                                 ofstream &archRep) {
    imprimirCabecerasDeMedicos(archRep);
    archRep << setw(10) << codMed << setw(7) << " ";
    leerEImprimirNombreDelMedico(archMed,archRep);
    archMed >> tarifa;
    archRep << setw(13) << tarifa << endl << endl;
}

void imprimirCabecerasDeMedicos(ofstream &archRep) {
    archRep << setw(10) << "Codigo";
    archRep << setw(13) << "Medico";
    archRep << setw(65) << "Tarifa por hora";
    archRep << endl;
}

void leerEImprimirNombreDelMedico(ifstream &archMed,ofstream &archRep) {
    int cantLet = 0;
    char c;
    while((c=archMed.get()) == ' ');
    while(1) {
        if(c == '_') archRep.put(' ');
        else {
            c = pasarLetraAMayus(c);
            archRep.put(c);
            cantLet++;
        }
        c = archMed.get();
        if(c == ' ') break;
    }
    imprimirBlancos(archRep,CANTLET-cantLet);
}

char pasarLetraAMayus(char c) {
    return c >= 'a' && c <= 'z' ? c -= 'a' - 'A' : c -= 0;
}

void imprimirCabecerasSecundarias(ofstream &archRep) {
    archRep << setw(21) << "CITAS ATENDIDAS:" << endl;
    imprimirLinea(archRep, '-', CANTLIN);
    archRep << setw(10) << "FECHA";
    archRep << setw(35) << "DNI - PACIENTE";
    archRep << setw(45) << "TELEFONO";
    archRep << setw(12) << "LLEGADA";
    archRep << setw(12) << "SALIDA";
    archRep << setw(20) << "TIEMPO(minutos)";
    archRep << setw(10) << "PAGO";
    archRep << endl;
    imprimirLinea(archRep, '-', CANTLIN);
}

void procesarCitasPorMedico(int codMed,double tarifa,double &totGastDeCit,
                            double &totRecaudado,ifstream &archCit,
                            ifstream &archPac,ofstream &archRep) {
    archCit.clear();
    archCit.seekg(0,ios::beg);
    int dni,codMedArch,dd,mm,aa,hhI,minI,segI,hhF,minF,segF,horaIni,horaFin;
    double minTot, totPac;
    char c;
    while(1) {
        archCit >> dni;
        if(archCit.eof()) break;
        archCit >> codMedArch;
        if(codMed == codMedArch) {
            archCit >> dd >> c >> mm >> c >> aa >> hhI >> c >> minI >> c >> segI
                    >> hhF >> c >> minF >> c >> segF;
            archRep << "     " << setfill('0') << setw(2) << dd << '/' << setw(2)
                    << mm << '/' << setw(4) << aa << setfill(' ');
            archRep << setw(7) << " " << setw(10) << dni << " - ";
            leerEImprimirNombreDelPaciente(dni,archPac,archRep);
            archRep << setfill('0') << setw(2) << hhI << ':' << setw(2)
                    << minI << ':' << setw(2) << segI << setfill(' ');
            archRep << "    " << setfill('0') << setw(2) << hhF << ':' << setw(2)
                    << minF << ':' << setw(2) << segF << setfill(' ');
            horaIni = hhI*3600+minI*60+segI;
            horaFin = hhF*3600+minF*60+segF;
            minTot = (double)((horaFin-horaIni) / 60); //en minutos
            totPac = (double)((horaFin-horaIni) / 3600) * tarifa; //en horas
            totGastDeCit += totPac;
            totRecaudado += totPac;
            archRep << setw(13) << minTot << setw(16) << totPac << endl;
        }
        while(archCit.get() != '\n');
    }
}

void leerEImprimirNombreDelPaciente(int dni,ifstream &archPac,ofstream &archRep) {
    archPac.clear();
    archPac.seekg(0,ios::beg);
    int DNI, tel, cantLet = 0;
    char c;
    while(1) {
        archPac >> DNI;
        if(archPac.eof()) break;
        if(DNI == dni) {
            while(archPac.get() != '[');
            while(1) {
                c = archPac.get();
                if(c == ']') break;
                archRep.put(c);
                cantLet++;
            }
            imprimirBlancos(archRep,45-cantLet);
            archPac >> tel;
            archRep << setw(11) << tel << setw(4) << " ";
        }
        while(archPac.get() != '\n');
    }
}

void imprimirTotalDeGastosPorCitas(double totGastDeCit,ofstream &archRep) {
    archRep << setw(31) << "Total de gastos por citas:" << setw(113)
            << totGastDeCit << endl;
    imprimirLinea(archRep,'=',CANTLIN);
}

void imprimirBlancos(ofstream &archRep, int tam) {
    for(int i = 0; i < tam; i++) archRep.put(' ');
}

void imprimirLinea(ofstream &archRep,char c,int tam) {
    for(int i = 0; i < tam; i++) archRep.put(c);
    archRep << endl;
}
