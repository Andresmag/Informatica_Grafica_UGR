//**************************************************************************
// Práctica 3
//
// Andrés Molina López 2016-2017
//
// Clase para crear el cabezal del regulador de Watt el cual esta formado por
// un cilindro y dos brazos acoplados a este cilindro
//**************************************************************************

#ifndef _CABEZAL
#define _CABEZAL

#include "brazo_completo.h"
#include "cilindro.h"

class Cabezal{
private:
	Cilindro cabeza;
	Brazo_completo brazo;
	double alpha;
public:
	Cabezal();
	void draw(char modo);
	void setAlpha(double a,double b);
};

#endif
