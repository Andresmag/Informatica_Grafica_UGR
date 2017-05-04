//**************************************************************************
// Práctica 3
//
// Andrés Molina López 2016-2017
//
// Implementacion de la clase Brazo completo
//**************************************************************************

#include "brazo_completo.h"

//Constructor
Brazo_completo::Brazo_completo(){
	cilindro.Modificar_divisiones(20);
	beta = 90;
}

//Calcula el valor de beta
void Brazo_completo::setBeta(double valor){
	beta = valor;
}

//Dibuja el brazo completo
void Brazo_completo::draw(char modo){
	brazo.draw(modo);
	
	glPushMatrix();
	glTranslatef(0,-5,0);
	glRotatef(beta,0,0,1);
	glTranslatef(0,2.5,0);
	glScalef(0.25,5,0.25);
	cilindro.draw(modo);
	glPopMatrix();
}
