//**************************************************************************
// Práctica 3
//
// Andrés Molina López 2016-2017
//
// Clase para crear la pieza central formada por un cilindro y una varilla 
// unida a este.
//**************************************************************************

#ifndef _PIEZA_CENTRAL
#define _PIEZA_CENTRAL

#include "cilindro.h"
#include "cubo.h"

class Pieza_central{
private:
	Cilindro tronco;
	Cube varilla;
public:
	Pieza_central();
	void draw(char modo);
};

#endif
