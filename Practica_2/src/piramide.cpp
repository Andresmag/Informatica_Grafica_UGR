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
	vector<_vertex3f> perfil_piramide(3);
	perfil_piramide[0] = _vertex3f(0,0.5,0);
	perfil_piramide[1] = _vertex3f(0.5,-0.5, 0);
	perfil_piramide[2] = _vertex3f(0,-0.5,0);
	
	//Una vez tenemos el perfil de la piramide, lo giramos
	
	GenerarFigura(perfil_piramide, 4);
}
