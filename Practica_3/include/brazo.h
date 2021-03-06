//**************************************************************************
// Práctica 3
//
// Andrés Molina López 2016-2017
//
// Clase para crear un brazo a partir de un cilindro y una esfera engancha
// al final de este
//**************************************************************************

#ifndef _BRAZO
#define _BRAZO

#include "cilindro.h"
#include "esfera.h"
#include "PLY.h"

class Brazo{
private:
	Cilindro antebrazo;
	Esfera mano;
	Modelo_PLY modelo;
public:
	Brazo();
	void draw(char modo);
};

#endif
