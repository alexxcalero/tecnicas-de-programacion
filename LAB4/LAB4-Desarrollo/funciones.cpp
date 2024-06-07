/*
 * Proyecto : LAB4-Desarrollo
 * Archivo  : funciones.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 25 de octubre de 2022, 11:07
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cctype>
#include "funciones.h"
#define CANT_LIN 350
using namespace std;

void procesarComentariosYEmitirReporte(ifstream &archComen,ifstream &archPaises,
                                       ofstream &archRep) {
    archRep << setw(70) << "TikTok_tp" << endl;
    imprimirLinea('=',CANT_LIN,archRep);
    int dd,mm,aa, codPais,codUsuario, likes;
    char c, comentario[200], pais[20], comentarioModificado[200];
    while(1) {
        archComen >> dd;
        if(archComen.eof()) break;
        archComen >> c >> mm >> c >> aa;
        archRep << "Fecha del TikTok : " << setfill('0') << setw(2) << dd << '/'
                << setw(2) << mm << '/' << setw(4) << aa << setfill(' ');
        archRep << endl << endl;
        imprimirCabeceras(archRep);
        while(1) {
            archComen >> codPais >> c >> codUsuario >> comentario >> likes;
            imprimirComentario(comentario,archRep);
            imprimirPais(codPais,pais,archPaises,archRep);
            transformarEImprimirComentario(comentario,comentarioModificado,archRep);
            transformarEImprimirPais(pais,archRep);

            // Verifico que no sean los ultimos datos leidos en la linea
            if(archComen.get() == '\n') break;
        }
        imprimirLinea('=',CANT_LIN,archRep);
    }
}

void imprimirCabeceras(ofstream &archRep) {
    archRep << "Comentario";
    archRep << setw(129) << "Long";
    archRep << setw(13) << "Pais";
    archRep << setw(24) << "Long";
    archRep << setw(25) << "Transformacion 1";
    archRep << setw(102) << "Long";
    archRep << setw(28) << "Transformacion 2";
    archRep << setw(17) << "Long";
    archRep << endl;
    imprimirLinea('-',CANT_LIN,archRep);
}

void imprimirComentario(char *comentario,ofstream &archRep) {
    int len = strlen(comentario);
    for(int i = 0; i < len; i++)
        if(comentario[i] == '_')
            comentario[i] = ' ';
    archRep << left << setw(130) << comentario;
    archRep << right << "     " << setfill('0') << setw(3) << len << setfill(' ');

    // Espacios entre la longitud del comentario y el pais
    archRep << right << setw(10) << " ";
}

void imprimirPais(int codPais,char *pais,ifstream &archPaises,ofstream &archRep) {
    archPaises.clear();
    archPaises.seekg(0,ios::beg);
    int idPais;
    while(1) {
        archPaises >> idPais;
        if(archPaises.eof()) break;
        if(idPais != codPais) while(archPaises.get() != '\n');
        else {
            archPaises >> pais;
            break;
        }
    }
    int len = strlen(pais);
    archRep << left << setw(20) << pais;
    archRep << right << "     " << setfill('0') << setw(2) << len << setfill(' ');

    // Espacios entre la longitud del pais y la transformacion 1
    archRep << right << setw(10) << " ";
}

void transformarEImprimirComentario(char *comentario,char *comentarioModificado,
                                    ofstream &archRep) {
    int i;

    // Primero paso todo el comentario base a minuscula
    for(i = 0; comentario[i]; i++)
        if(comentario[i] != ' ')
            comentario[i] = tolower(comentario[i]);

    // Encuentro los espacios en blanco entre los que esta la 2da palabra
    int pos1erEsp = 0, pos2doEsp = 0, cont = 0;
    for(i = 0; comentario[i]; i++) {
        if(comentario[i] == ' ' && cont == 0) {
            pos1erEsp = i;
            cont++;
        }
        else if(comentario[i] == ' ' && cont == 1) {
            pos2doEsp = i;
            cont++;
        }
    }

    // Realizo la modificacion planteando tres casos diferentes, dependiendo
    // de la cantidad de espacios en blanco encontrados
    i = 0;
    int j = 0;
    bool unSoloAsterisco = true;

    // Si el comentario solo consta de una palabra:
    if(pos1erEsp == 0 && pos2doEsp == 0)
        strcpy(comentarioModificado,comentario);

    // Si el comentario consta de dos palabras:
    else if(pos2doEsp == 0) {
        while(i < pos1erEsp) {
            comentarioModificado[i] = comentario[i];
            i++;
        }

        // Añado el caracter de final de cadena
        comentarioModificado[i] = 0;
        i++;

        // Concateno un asterisco al final de la primera palabra
        strcat(comentarioModificado,"*");
    }

    // Si el comentario tiene mas de dos palabras:
    else {
        for(i = 0; comentario[i]; i++) {
            if(comentario[i] != ' ' && (i < pos1erEsp || i > pos2doEsp)) {
                comentarioModificado[j] = comentario[i];
                j++;
            }
            else if(unSoloAsterisco == true && (i >= pos1erEsp && i <=pos2doEsp)) {
                comentarioModificado[j] = '*';
                unSoloAsterisco = false;
                j++;
            }
        }

        // Añado el caracter de final de cadena
        comentarioModificado[j] = 0;
        j++;
    }

    // Imprimo mi comentario modificado
    int len = strlen(comentarioModificado);
    archRep << left << setw(110) << comentarioModificado;
    archRep << right << "     " << setfill('0') << setw(2) << len << setfill(' ');

    // Espacios entre la longitud de la transformacion 1 y la transformacion 2
    archRep << right << setw(18) << " ";
}

void transformarEImprimirPais(char *pais,ofstream &archRep) {
    // Primero paso todos los caracteres del pais a minuscula
    for(int i = 0; pais[i]; i++)
        pais[i] = tolower(pais[i]);

    // Como piden mostrar las tres primeras letras de los paises, hacemos lo sgt:
    pais[3] = 0;

    int len = strlen(pais);

    // Imprimimos el pais modificado
    archRep << left << setw(20) << pais;
    archRep << right << "     " << setfill('0') << setw(2) << len << setfill(' ') << endl;
}

void imprimirLinea(char c,int tam,ofstream &archRep) {
    for(int i = 0; i < tam; i++) archRep.put(c);
    archRep << endl;
}
