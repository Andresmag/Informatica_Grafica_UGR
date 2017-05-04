//**************************************************************************
// Práctica 3
//
// Andrés Molina López 2016-2017
//
// Implementacion de la clase Base
//**************************************************************************

#include "base.h"

//Constructor
Base::Base(){
	eje.Modificar_divisiones(20);
	rotacion = 0;
}

//Asigna el valor de la rotacion del eje
void Base::setRotacion(double valor){
	rotacion = valor;
}

//Dibuja la base
void Base::draw(char modo){
	glPushMatrix();
	glTranslatef(0,0.5,0);
	glScalef(6,1,6);
	soporte.draw(modo);
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(rotacion,0,1,0);
	glTranslatef(0,7,0);
	glScalef(1,13,1);
	eje.draw(modo);
	glPopMatrix();
	
}
