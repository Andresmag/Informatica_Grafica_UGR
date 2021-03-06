//**************************************************************************
// Práctica 3
//
// Andrés Molina López 2016-2017
//
// Clase para crear un brazo a partir de un cilindro, una esfera engancha
// al final de este, y otro cilindro mas pequeño, enganchando en perpendicular
// a poco mas de la mitad del primer cilindro
//**************************************************************************

#ifndef _BRAZO_COMPLETO
#define _BRAZO_COMPLETO

#include "cilindro.h"
#include "brazo.h"

class Brazo_completo{
private:
	Brazo brazo;
	Cilindro cilindro;
	double beta;
public:
	Brazo_completo();
	void draw(char modo);
	void setBeta(double valor);
};

#endif
