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
	modelo.CargarPLY("data/beethoven.ply");
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
	
	glPushMatrix();
	glTranslatef(1.75,-5,0);
	glRotatef(-90,0,0,1);
	glScalef(0.25,0.25,0.25);
	modelo.draw(modo);
	glPopMatrix();
}
