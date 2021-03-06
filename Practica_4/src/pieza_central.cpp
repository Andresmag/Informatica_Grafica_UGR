//**************************************************************************
// Práctica 3
//
// Andrés Molina López 2016-2017
//
// Implementacion de la clase Pieza central
//**************************************************************************

#include "pieza_central.h"

//Constructor
Pieza_central::Pieza_central(){
	tronco.Modificar_divisiones(20);
}

// Funcion para dibujar el cabezal en su sitio
void Pieza_central::draw(char modo){
	glPushMatrix();
	glScalef(2,1,2);
	tronco.draw(modo);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-0.75,-2.35,0);
	glScalef(0.25,4.7,0.25);
	varilla.draw(modo);
	glPopMatrix();
}
