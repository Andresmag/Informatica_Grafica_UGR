//**************************************************************************
// Práctica 4
//
// Andrés Molina López 2016-2017
//
// Clase para crear un tablero
/*
	A ·--------------· B 
	  |              |
	  |              |
	  |   tablero    |
	  |              |
	  |              |
	C ·--------------· D
*/
//**************************************************************************

#ifndef _TABLERO
#define _TABLERO

#include "O3D.h"
#include "vertex.h"

class Tablero : public O3D{
private:
	_vertex3f A;
	_vertex3f B;
	_vertex3f C;
	_vertex3f D;
	int num_divisiones;
public:
	Tablero();
	void Dimensionar(int divisiones);
	void setDivisiones(int valor);
	int getDivisiones();
};

#endif
