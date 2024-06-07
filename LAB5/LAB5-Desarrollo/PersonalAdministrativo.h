/*
 * Proyecto : LAB5-Desarrollo
 * Archivo  : PersonalAdministrativo.h
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 8 de noviembre de 2022, 11:11
 */

#ifndef PERSONALADMINISTRATIVO_H
#define PERSONALADMINISTRATIVO_H

struct PersonalAdministrativo {
	char nombre[60];
    int codigo;
    char distrito[60];
    char puesto[60];
    char gradoInstruccion[60];
    int anhosDeServicio;
    double sueldo;
};

#endif /* PERSONALADMINISTRATIVO_H */
