//**************************************************************************
// Práctica 3
//
// Andrés Molina López 2016-2017
//
// Implementacion de la clase Cuerpo
//**************************************************************************

#include "cuerpo.h"

//Constructor
Cuerpo::Cuerpo(){}

//Permite modificar la distancia entre los dos cilindros
void Cuerpo::setDistancia(double a, double b){
	//pasamos los angulos a radianes
	cabeza.setAlpha(a, b);
	a *= M_PIl/180;
	b *= M_PIl/180;
	distancia_cilindros = sin(b)*(4.75/sin(a));
	if(distancia_cilindros < 1)
		distancia_cilindros = 1;
}

// Funcion para dibujar el cabezal en su sitio
void Cuerpo::draw(char modo){
	cabeza.draw(modo);

	glPushMatrix();
	glTranslatef(0,-distancia_cilindros, 0);
	centro.draw(modo);
	glPopMatrix();
}
