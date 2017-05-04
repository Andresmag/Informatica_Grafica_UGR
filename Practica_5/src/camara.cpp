//**************************************************************************
// Práctica 5
//
// Andrés Molina López 2016-2017
//
// Implementacion de la clase para el manejo de la camara
//**************************************************************************

#include "camara.h"

//Constructor
Camara::Camara(bool valor){
	Observer_distance=2;
	Observer_angle_x=0;
	Observer_angle_y=0;
	paralela=valor;
}

void Camara::girar(float x, float y){
	Observer_angle_x = y;
	Observer_angle_y = x;
}

void Camara::zoom(int i){
	if(i > 0)
		Observer_distance /=1.2;
	else
		Observer_distance *=1.2;
}

void Camara::setObservador(){

/*	if(paralela){
		glTranslatef(0,-Observer_distance/2,0);
		glTranslatef(-Observer_angle_y*0.0005,0,0);
		glTranslatef(0,0,-Observer_angle_x*0.0005);
	}
	else{*/
		glTranslatef(0,0,-Observer_distance);
		glRotatef(Observer_angle_x,1,0,0);
		glRotatef(Observer_angle_y,0,1,0);
	//}
}

GLfloat Camara::getDistance(){
	return Observer_distance;
}

bool Camara::getParalela(){
	return paralela;
}

void Camara::setParalela(){
	paralela = !paralela;
}

void Camara::setDistance(float front_plane){
	Observer_distance *= front_plane;
}
	
