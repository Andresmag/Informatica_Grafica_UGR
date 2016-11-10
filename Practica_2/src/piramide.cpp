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
	perfil_piramide.resize(3);
	perfil_piramide[0] = _vertex3f(0,0.5,0);
	perfil_piramide[1] = _vertex3f(0.5,-0.5, 0);
	perfil_piramide[2] = _vertex3f(0,-0.5,0);
}

//Funcion para obtener el perfil de la piramide
vector<_vertex3f> Piramide::getPerfil(){
	return perfil_piramide;
}
