//**************************************************************************
// Práctica 3
//
// Andrés Molina López 2016-2017
//
// Clase para crear la base, a partir de un cubo y de un cilindro
//**************************************************************************

#ifndef _BASE
#define _BASE

#include "cilindro.h"
#include "cubo.h"

class Base{
private:
	Cilindro eje;
	Cube soporte;
	double rotacion;
public:
	Base();
	void draw(char modo);
	void setRotacion(double valor);
};

#endif
