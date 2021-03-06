#ifndef IO_H
#define IO_H

#include "defines.h"
#include "fstream"
#include <limits>
#include <string>
#include <sstream>
//#include <stdlib.h>
//#include <chrono>
#include "Matriz.h"


// Funciones de entrada salida pare leer y escribir datos en archivos.
// Siempre tratar de usar >> para eliminar los espacios.

void setearPrecision(ostream& os, int prec);

// Cuento los caracteres hasta el primer espacio ESPACIO, y restauro el stream.
int contarCaracteres(ifstream& ifs);

// Ignoro cantidad veces hasta el caracter c.
void ignorarHastaCaracter(ifstream& ifs, int cantidad, char c);

// Ignoro cantidad lineas.
void ignorarLineas(ifstream& ifs, int cantidad = 1);
// Copio hasta el caracter c en el buffer.
void obtenerHastaCaracter(ifstream& ifs, char * buffer, char c);

int contarLineas(const char* file);


//Lee los datos basios del archivo. La primer linea.
void leerDatosBasicos(const char* file, Data& data);


void leerDatosJugadores(const char* file, Data& data);

std::ifstream::pos_type filesize(const char* filename);

// Escribe los resultados en archivo de salida.
template<class T>
void escribirVectorS(ostream& os, const vector<T>& b, int modo = VERT){
	setearPrecision(os, PRECISION);
	int tamanio = b.size();
	for(int i = 0; i < tamanio; i++){
	os << b[i];
	if(modo == VERT){
	    os << endl;
	}
	if(i == tamanio-1 and modo == HORIZ){os << endl;}
	else if(modo == HORIZ){os << " ";}
	}
}


template<class T>
void escribirVector(const char*  file, const vector<T>& b, int modo = VERT){
	ofstream file_s; file_s.open(file);
	setearPrecision(file_s, PRECISION);
	escribirVectorS(file_s, b, modo);
	file_s.close();
}

template<class T>
void escribirColumnaS(ostream& os, Matriz<T>& A, int j){
	int cantFilas = A.cantFilas();
	setearPrecision(os, PRECISION);
	for(int i = 0; i < cantFilas; i++){
	    os << A[i][j];
	    if(i != cantFilas - 1 ){os << " ";}
	}
}

template<class T>
void escribirColumna(const char* file, Matriz<T>& A, int j){
	ofstream file_s; file_s.open(file);
	escribirFilaS(file_s, A, j);
	file_s.close();
}

template<class T>
void escribirFilaS(ostream& os, Matriz<T>& A, int i){
	int cantColumnas = A.cantColumnas();
	setearPrecision(os, PRECISION);
	for(int j = 0; j < cantColumnas; j++){
	    os << A[i][j];
	    if(j != cantColumnas - 1 ){os << " ";}
	}
}

template<class T>
void escribirFila(const char* file, Matriz<T>& A, int i){
	ofstream file_s; file_s.open(file);
	escribirFilaS(file_s, A, i);
	file_s.close();
}

template<class T>
void escribirMatrizS(ostream& os, Matriz<T>& A){
	int cantFilas = A.cantFilas();
	setearPrecision(os, PRECISION);
	for(int i = 0; i < cantFilas; i++){
		escribirFilaS(os, A, i);
		if(i != cantFilas - 1 ){os << endl;}
	}
}

template<class T>
void escribirMatriz(const char*  file, Matriz<T>& A){
	ofstream file_s; file_s.open(file);
	escribirMatrizS(file_s, A);
	file_s.close();
}

template<class T>
void leerVector(const char*  file, vector<T>& b){
	ifstream file_s; file_s.open(file);
	int tamanio = b.size();
	for(int i = 0; i < tamanio; i++){
		file_s >> b[i];
	}
	file_s.close();
}

template<class T>
void leerMatrizS(ifstream& is, Matriz<T>& A){
	int cantFilas = A.cantFilas(); int cantColumnas = A.cantColumnas();
	for(int i = 0; i < cantFilas; i++){
		for(int j = 0; j < cantColumnas; j++){
		    is >> A[i][j];
		}
		is.get();
	}
}


template<class T>
void leerMatriz(const char*  file, Matriz<T>& A){
	ifstream file_s; file_s.open(file);
	leerMatrizS(file_s, A);
	file_s.close();
}

void escribirTiempo(const char*  file, string st);
#endif
