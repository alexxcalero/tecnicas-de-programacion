/*
 * Proyecto : LAB4-Desarrollo
 * Archivo  : funciones.h
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 25 de octubre de 2022, 11:08
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <fstream>
using namespace std;

void procesarComentariosYEmitirReporte(ifstream &,ifstream &,ofstream &);
void imprimirCabeceras(ofstream &);
void imprimirComentario(char *,ofstream &);
void imprimirPais(int,char *,ifstream &,ofstream &);
void transformarEImprimirComentario(char *,char *,ofstream &);
void transformarEImprimirPais(char *,ofstream &);
void imprimirLinea(char,int,ofstream &);

#endif /* FUNCIONES_H */
