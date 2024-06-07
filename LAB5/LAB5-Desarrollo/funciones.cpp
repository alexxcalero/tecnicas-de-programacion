/*
 * Proyecto : LAB5-Desarrollo
 * Archivo  : funciones.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 8 de noviembre de 2022, 11:04
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "funciones.h"
#include "PersonalAdministrativo.h"
#define CANT_LIN 200
using namespace std;

void leerDatosYActualizarInformacion(char **nombres,char **distritos,
        char **especialidades,char **facultades,int *codigos,int *escalas,
        double *valorDeCreditos,double *credMatriculados,int &cantAlum,
        struct PersonalAdministrativo *administrativos,int &cantAdmin) {
    ifstream arch("MiembrosDeTP2.csv",ios::in);
    if(!arch.is_open()) {
        cout << "No se pudo abrir el archivo MiembrosDeTP2.csv" << endl;
        exit(1);
    }
    char categoria,c;
    cantAlum = 0;
    cantAdmin = 0;

    while(1) {
        arch >> categoria;
        if(arch.eof()) break;
        arch >> c;
        if(categoria == 'D') while(arch.get() != '\n');  // Descarto la linea
        // Creo variables para cada if, ya que para arreglos se pide que sean
        // cadenas de tamanho exacto, y para estructuras si no es necesario que
        // sean de tamanho exacto.
        else if(categoria == 'A') {
            char *nomb, *dist, *esp, *fac;
            int cod, esc;
            double valCred, credMat;
            nomb = leerCadenaExacta(arch);
            arch >> cod >> c;
            dist = leerCadenaExacta(arch);
            esp = leerCadenaExacta(arch);
            fac = leerCadenaExacta(arch);
            arch >> esc >> c >> valCred >> c >> credMat;
            arch.get();  // Me como el salto de linea
            nombres[cantAlum] = nomb;
            codigos[cantAlum] = cod;
            distritos[cantAlum] = dist;
            especialidades[cantAlum] = esp;
            facultades[cantAlum] = fac;
            escalas[cantAlum] = esc;
            valorDeCreditos[cantAlum] = valCred;
            credMatriculados[cantAlum] = credMat;
            cantAlum++;
        }
        else if(categoria == 'a') {
            char nomb[60], dist[60], puesto[60], gradoDeInstruccion[60];
            int cod, anhosDeServicio;
            double sueldo;
            arch.getline(nomb,60,',');
            arch >> cod >> c;
            arch.getline(dist,60,',');
            arch.getline(puesto,60,',');
            arch.getline(gradoDeInstruccion,60,',');
            arch >> anhosDeServicio >> c >> sueldo;
            arch.get();  // Me como el salto de linea
            strcpy(administrativos[cantAdmin].nombre,nomb);
            administrativos[cantAdmin].codigo = cod;
            strcpy(administrativos[cantAdmin].distrito,dist);
            strcpy(administrativos[cantAdmin].puesto,puesto);
            strcpy(administrativos[cantAdmin].gradoInstruccion,gradoDeInstruccion);
            administrativos[cantAdmin].anhosDeServicio = anhosDeServicio;
            administrativos[cantAdmin].sueldo = sueldo;
            cantAdmin++;
        }
    }
}

char *leerCadenaExacta(ifstream &arch) {
    char buffer[500], *cadena;

    arch.getline(buffer,500,',');
    if(arch.eof()) return nullptr;

    cadena = new char[strlen(buffer) + 1];
    strcpy(cadena,buffer);

    return cadena;
}

void modificarNombres(struct PersonalAdministrativo *administrativos,int cantAdmin,
                      char **nombres,int cantAlum) {
    // Modificacion para administrativos
    for(int i = 0; i < cantAdmin; i++) {
        invertirNombre(administrativos[i].nombre);
        for(int j = 0; j < administrativos[i].nombre[j]; j++)
            if(administrativos[i].nombre[j] == '/')
                administrativos[i].nombre[j] = ' ';
    }

    // Modificacion para alumnos
    for(int i = 0; i < cantAlum; i++) {
        invertirNombre(nombres[i]);
        for(int j = 0; j < nombres[i][j]; j++)
            if(nombres[i][j] == '/')
                nombres[i][j] = ' ';
    }
}

void invertirNombre(char *nombre) {
    int len = strlen(nombre), posI, posF, i, j = 0;

    // Busco el primer slash empezando desde atrás,
    // para ver donde comienza el nombre
    for(i = len - 1; nombre[i]; i--)
        if(nombre[i] == '/') {
            posI = i;
            break;
        }

    // Busco el primer slash empezando desde el comienzo
    // para ver donde comienza el segundo apellido
    for(i = 0; nombre[i]; i++)
        if(nombre[i] == '/') {
            posF = i;
            break;
        }

    char cadenaMomentanea[60];
    i = posI + 1;
    while(nombre[i]) {
        cadenaMomentanea[j] = nombre[i];
        i++;
        j++;
    }
    cadenaMomentanea[j] = 0;
    j++;
    strcat(cadenaMomentanea," ");
    for(i = 0; i <= posF + 1; i++) {
        cadenaMomentanea[j] = nombre[i];
        j++;
    }
    cadenaMomentanea[j] = 0;
    j++;
    strcpy(nombre,cadenaMomentanea);
}

void ordenarArreglosDeAlumnos(char **nombres,char **distritos,char **especialidades,
                char **facultades,int *codigos,int *escalas,double *valorDeCreditos,
                double *credMatriculados,int cantAlum) {
    for(int i = 0; i < cantAlum - 1; i++)
        for(int j = i + 1; j < cantAlum; j++)
            if((strcmp(especialidades[i],especialidades[j]) > 0) ||
            (strcmp(especialidades[i],especialidades[j]) == 0 &&
             strcmp(especialidades[i],especialidades[j]) < 0)) {
                cambiarInt(codigos[i],codigos[j]);
                cambiarInt(escalas[i],escalas[j]);
                cambiarDouble(valorDeCreditos[i],valorDeCreditos[j]);
                cambiarDouble(credMatriculados[i],credMatriculados[j]);
                cambiarStr(nombres[i],nombres[j]);
                cambiarStr(distritos[i],distritos[j]);
                cambiarStr(especialidades[i],especialidades[j]);
                cambiarStr(facultades[i],facultades[j]);
            }
}

void cambiarInt(int &datoI, int &datoJ) {
    int aux = datoI;
    datoI = datoJ;
    datoJ = aux;
}

void cambiarDouble(double &datoI, double &datoJ) {
    double aux = datoI;
    datoI = datoJ;
    datoJ = aux;
}

void cambiarStr(char *&datoI, char *&datoJ) {
    char *aux = datoI;
    datoI = datoJ;
    datoJ = aux;
}

void emitirReporte(char **nombres,char **distritos,char **especialidades,
            char **facultades,int *codigos,int *escalas,double *valorDeCreditos,
            double *credMatriculados,int &cantAlum,
            struct PersonalAdministrativo *administrativos,int &cantAdmin) {
    ofstream arch("Balance_de_Ingresos.txt",ios::out);
    if(!arch.is_open()) {
        cout << "No se pudo abrir el archivo Balance_de_Ingresos.txt" << endl;
        exit(1);
    }
    arch << setw(60) << "Universidad TP" << endl;
    imprimirLinea('=',CANT_LIN,arch);
    arch << "RECAUDACIÓN POR MATRÍCULA:" << endl;
    imprimirLinea('-',CANT_LIN,arch);
    imprimirCabecerasDeAlumnos(arch);
    imprimirLinea('-',CANT_LIN,arch);
    double pago, ingresoTotal = 0, egresoTotal = 0;
    arch.precision(2);
    arch << fixed;
    for(int i = 0; i < cantAlum; i++) {
        pago = valorDeCreditos[i] * credMatriculados[i];
        ingresoTotal += pago;
        arch << codigos[i] << "    " << left << setw(40) << nombres[i] << setw(30)
             << distritos[i] << setw(25) << especialidades[i] << setw(15)
             << facultades[i] << setw(10) << right << escalas[i] << setw(10)
             << valorDeCreditos[i] << setw(10) << credMatriculados[i]
             << setw(10) << pago << endl;
    }
    imprimirLinea('-',CANT_LIN,arch);
    arch << "INGRESO TOTAL POR MATRICULA: " << ingresoTotal << endl;
    imprimirLinea('=',CANT_LIN,arch);
    arch << "PAGO AL PERSONAL ADMINISTRATIVO:" << endl;
    imprimirLinea('-',CANT_LIN,arch);
    imprimirCabecerasDeAdministrativos(arch);
    imprimirLinea('-',CANT_LIN,arch);
    pago = 0;
    for(int i = 0; i < cantAdmin; i++) {
        arch << administrativos[i].codigo << "      " << left << setw(40)
             << administrativos[i].nombre << setw(40) << administrativos[i].distrito
             << setw(40) << administrativos[i].puesto << setw(40)
             << administrativos[i].gradoInstruccion << setw(10)
             << administrativos[i].anhosDeServicio << setw(10)
             << administrativos[i].sueldo << endl;
    }
}

void imprimirCabecerasDeAlumnos(ofstream &arch) {

}

void imprimirCabecerasDeAdministrativos(ofstream &arch) {

}

void imprimirLinea(char c,int tam,ofstream &arch) {
    for(int i = 0; i < tam; i++) arch.put(c);
    arch << endl;
}
