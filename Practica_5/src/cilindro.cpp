//**************************************************************************
// Práctica 3
//
// Andrés Molina López 2016-2017
//
// Implementacion de la clase Cilindro
//**************************************************************************

#include "cilindro.h"

//Constructor sin argumentos
Cilindro::Cilindro(){
	figura_guardada.resize(4);
	figura_guardada[0] = _vertex3f(0,0.5,0);
	figura_guardada[1] = _vertex3f(0.5,0.5,0);
	figura_guardada[2] = _vertex3f(0.5,-0.5,0);
	figura_guardada[3] = _vertex3f(0,-0.5,0);
}

