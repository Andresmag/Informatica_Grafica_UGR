//**************************************************************************
// Práctica 2
//
// Andrés Molina López 2016-2017
//
// Implementacion de la clase Piramide
//**************************************************************************

#include "piramide.h"

//Constructor
Piramide::Piramide(){
	figura_guardada.resize(3);
	figura_guardada[0] = _vertex3f(0,0.5,0);
	figura_guardada[1] = _vertex3f(0.5,-0.5, 0);
	figura_guardada[2] = _vertex3f(0,-0.5,0);
	
	//Siempre es 4 ya que si tuviese mas caras no seria una piramide
	Modificar_divisiones(4);
}

