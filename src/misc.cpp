#include "misc.h"

vector<double> obtenerXs(vector<Posicion> trayectoria){
	vector<double> res;
	for(unsigned i = 0; i < trayectoria.size(); ++i) {
		res.push_back(trayectoria[i].x)
	}

	return res;
}

vector<double> obtenerYs(vector<Posicion> trayectoria){
	vector<double> res;
	for(unsigned i = 0; i < trayectoria.size(); ++i) {
		res.push_back(trayectoria[i].y)
	}

	return res;
}

double calcularRaiz(vector<double> coeficientes, int metodo = BISECCION) {
	if (metodo == BISECCION) {
		double a = coeficientes.size()-1;
		double b = a + INTERVALO_BISECCION;
		pair<double,double> res = bisect(bind(eval, coeficientes, _1), a, b, TerminationCondition());
		return (res.first + res.second)/2;
	}
	if (metodo == NEWTON) {		
		double min = coeficientes.size()-1, max = min + INTERVALO_BISECCION;
		double x0 = (min+max)/2;
		int digits = 10;
		return newton_raphson_iterate(bind(evalNewton, coefs, _1), x0, min, max, digits);
	}
}

double eval(vector<double> &coefs, double x) {
	double res = coefs[0];
	for(unsigned i = 1; i < coefs.size(); ++i) {
		res += coefs[i]*pow(x,i);
	}
	return res;
}

tuple<double,double> evalNewton(vector<double> &coefs, double x) {
	tuple<double,double> ret;

	double resPol = coefs[0];
	for(unsigned i = 1; i < coefs.size(); ++i) {
		resPol += coefs[i]*pow(x,i);
	}
	get<0>(ret) = resPol

	double resDer = coefs[1];
	for(unsigned i = 2; i < coefs.size(); ++i) {
		resDer += coefs[i]*pow(x,i-1);
	}
	get<1>(ret) = resDer;

	return ret;
}