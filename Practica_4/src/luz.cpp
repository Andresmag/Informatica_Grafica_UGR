//**************************************************************************
// Práctica 4
//
// Andrés Molina López 2016-2017
//
// Implementacion de la clase para el manejo de la luz
//**************************************************************************

#include "luz.h"

//Constructor
Luz::Luz(GLenum num){
	tipo = num;
	activa = false;
}


//set para desactivar la luces 0 y 1
void Luz::turnLight(){
	if(activa) glDisable(tipo);
	else glEnable(tipo);
	activa = !activa;
}

//set para asignar los valores a la componente difusa
void Luz::setDifusa(float a, float b, float c, float d){
	difusa[0] = a;
	difusa[1] = b;
	difusa[2] = c;
	difusa[3] = d;
}

//set para asignar los valores a la componente especular
void Luz::setEspecular(float a, float b, float c, float d){
	especular[0] = a;
	especular[1] = b;
	especular[2] = c;
	especular[3] = d;
}

//set para asignar los valores a la componente ambiental
void Luz::setAmbiental(float a, float b, float c, float d){
	ambiental[0] = a;
	ambiental[1] = b;
	ambiental[2] = c;
	ambiental[3] = d;
}

//set para asignar los valores a la componente position
void Luz::setPosition(float a, float b, float c, float d){
	position[0] = a;
	position[1] = b;
	position[2] = c;
	position[3] = d;
}

//Aplicar la luz
void Luz::aplicar(float a, float b){
	glPushMatrix();
	glRotatef(a,1,0,0);
	glRotatef(b,0,1,0);
	glLightfv(tipo, GL_DIFFUSE, difusa);
	glLightfv(tipo, GL_AMBIENT, ambiental);
	glLightfv(tipo, GL_SPECULAR, especular);
	glLightfv(tipo, GL_POSITION, position);
	glPopMatrix();
}

