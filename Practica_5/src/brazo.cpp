//**************************************************************************
// Práctica 3
//
// Andrés Molina López 2016-2017
//
// Implementacion de la clase Brazo
//**************************************************************************

#include "brazo.h"

//Constructor
Brazo::Brazo(){
	antebrazo.Modificar_divisiones(20);
	mano.Redimensionar(20);
}

//Dibuja el brazo
void Brazo::draw(char modo){
	glPushMatrix();
	glTranslatef(0,-9,0);
	mano.draw(modo);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0,-4.5,0);
	glScalef(0.5,9,0.5);
	antebrazo.draw(modo);
	glPopMatrix();
}
