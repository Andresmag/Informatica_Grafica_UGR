//**************************************************************************
// Práctica 3
//
// Andrés Molina López 2016-2017
//
// Clase para crear el cuerpo del regulador, el cual vamos a considerar que es
// todo el conjunto de piezas que no son ni el eje ni la base, de manera que 
// está formada por un cilindro del cual sale una barilla hacia abajo y la
// pieza cabezal.
//**************************************************************************

#ifndef _CUERPO
#define _CUERPO

#include "cabezal.h"
#include "pieza_central.h"

class Cuerpo{
private:
	Cabezal cabeza;
	Pieza_central centro;
	double distancia_cilindros;
public:
	Cuerpo();
	void draw(char modo);
	void setDistancia(double a, double b);
};

#endif
