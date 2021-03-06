//**************************************************************************
// Práctica 3
//
// Andrés Molina López 2016-2017
//
// Clase para crear el regulador de Watt, a partir de las piezas cuerpo,
// un cilindro que hace de eje central y cubo que hace de base del objeto.
//**************************************************************************

#ifndef _REGULADOR
#define _REGULADOR

#include "cuerpo.h"
#include "base.h"

class Regulador{
private:
	Cuerpo pieza;
	Base base;
	double velocidad, rotacion;
public:
	Regulador();
	void draw(char modo);
	void cambiarVelocidad(double incremento);
	void mover();
};

#endif
