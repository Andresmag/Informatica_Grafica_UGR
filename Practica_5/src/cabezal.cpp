//**************************************************************************
// Práctica 3
//
// Andrés Molina López 2016-2017
//
// Implementacion de la clase Cabezal
//**************************************************************************

#include "cabezal.h"

//Constructor
Cabezal::Cabezal(){
	cabeza.Modificar_divisiones(20);
}
//Modifica el valor de alpha
void Cabezal::setAlpha(double a, double b){
	alpha = a;
	brazo.setBeta(b);
}

// Funcion para dibujar el cabezal en su sitio
void Cabezal::draw(char modo){
	glPushMatrix();
	glScalef(2,1,2);
	cabeza.draw(modo);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.5,0,0);
	glRotatef(alpha,0,0,1);
	brazo.draw(modo);
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(180,0,1,0);
	glTranslatef(0.5,0,0);
	glRotatef(alpha,0,0,1);
	brazo.draw(modo);
	glPopMatrix();
}
