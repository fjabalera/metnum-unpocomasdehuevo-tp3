#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>

/**
 * Formato del archivo de salida
 * 
 * posiciónArq posPoste1 posPoste2 cotaDesplazamiento
 * x0 y0
 * x1 y1
 * ...
 * xn yn
 *
 * dimensiones de la cancha: 1100 x 600.
 */

using namespace std;

#define POSICION_PRIMER_PALO 315
#define POSICION_SEGUNDO_PALO 385
#define COTA_DESPLAZAMIENTO 4
#define ANCHO_CANCHA 600
#define LARGO_CANCHA 1100
#define X_LINEA_META 125

struct punto {



	
	punto() : x(0), y(0) {};
	punto(int x, int y) : x(x), y(y) {};
	int x;
	int y;
};

int int main(int argc, char const *argv[])
{
	/**
	 * @param grado grado del polinomio con el que se generará la curva de la
	 *        trayectoria
	 * @param cantidadDeMediciones
	 * @param cantidadDeInstancias 
	 */
	
	if (argc != 4) {cout << "Cantidad de parámetros invalida." << endl; return 1;}

	int grado = atoi(argv[1]);
	int cantidadDeMediciones = atoi(argv[2]);
	int cantidadDeInstancias = atoi(argv[3]);

	if (cantidadDeMediciones < grado+1) {
		cout << "La cantidad de mediciones es demasiado chica para el grado que eligió." << endl;
		return 1;
	}

	int anchoArco = POSICION_SEGUNDO_PALO - POSICION_PRIMER_PALO;
	
	int posicionArquero = generarYRandDentroDelArco(anchoArco);
	int yGol = generarYRandDentroDelArco(anchoArco);

	vector<punto> puntosLagrange;
	puntosLagrange.push_back(punto(X_LINEA_META, yGol));
	int xRand, yRand;
	for(unsigned i = 0; i < grado; ++i) {
		xRand = generarXRandDentroDeLaCancha();
		yRand = generarYRandDentroDeLaCancha();

		puntosLagrange.push_back(punto(xRand, yRand));
	}

	vector<punto> trayectoria;
	// (cantidadDeMediciones - 1) por que yGol ya lo tengo
	int xInicial = generarXRandDentroDeLaCancha();
	int delta = (xInicial - X_LINEA_META)/(cantidadDeMediciones-1);
	int xActual;
	for(unsigned i = 0; i < cantidadDeMediciones-1; ++i) {
		xActual = xInicial + i*delta + (rand() % delta);
		trayectoria.push_back(punto(xActual, lagrange(puntosLagrange, xActual)));
	}

	trayectoria.push_back(punto(X_LINEA_META, yGol));

	ofstream tiroFile ("tiroPrueba.tiro");
	tiroFile << posicionArquero << " " << "POSICION_PRIMER_PALO " << "POSICION_SEGUNDO_PALO " << "COTA_DESPLAZAMIENTO" << endl;
	for(unsigned i = 0; i < trayectoria.size(); ++i) {
		tiroFile << trayectoria[i].x << " " << trayectoria[i].y << endl;
	}

	tiroFile.close()

	return 0;
}


int lagrange(vector<punto> puntosLagrange, int xActual) {
	double sum = 0;
	int mult;
	int cantidadDePuntos = puntosLagrange.size();
	for(int i = 0; i < cantidadDePuntos; i++) {
		mult = 1;
	    for(int j = 0;j < cantidadDePuntos; j++) {
	        if(j != i) {
	        	mult*=(xActual-puntosLagrange[j].x)/(puntosLagrange[i].x-puntosLagrange[j].x);
	        }
	    }
	    sum += mult*puntosLagrange[i].y;
	}	

	return (int) sum;
}

int generarXRandDentroDeLaCancha() {
	return (rand() % LARGO_CANCHA) + X_LINEA_META;
}

int generarYRandDentroDeLaCancha() {
	return (rand() % ANCHO_CANCHA);
}

int generarYRandDentroDelArco(int anchoArco) {
	return (rand() % anchoArco) + POSICION_PRIMER_PALO;
}