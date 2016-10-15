//**************************************************************************
// Práctica 1 - ampliación examen
//
// Andrés Molina López 2016-2017
//
// Clase Poligono
//**************************************************************************

#ifndef _poligono
#define _poligono

#include <stdio.h>
#include <cmath>
#include "O3D.h"

#define PI 3.1416

class Poligono : public O3D{
public:
	
	Poligono(int num_vertices);
	void draw_fan(char modo);
	
};

#endif		
