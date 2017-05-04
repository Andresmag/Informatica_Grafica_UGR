//**************************************************************************
// Práctica 4
//
// Andrés Molina López 2016-2017
//
// Implementacion de la clase para el manejo de la luz general
//**************************************************************************

#include "iluminacion.h"

//Constructor
Iluminacion::Iluminacion(): light0(GL_LIGHT0), light1(GL_LIGHT1){
	activa = false;
	//light0
	light0.setDifusa(0.5, 0.5, 0.5, 1);
	light0.setEspecular(1, 1, 1, 1);
	light0.setAmbiental(0.3, 0.3, 0.3, 1);
	light0.setPosition(0, 0, 5, 0);

	//light1
	light1.setDifusa(0.8, 0.3, 0.5, 1);
	light1.setEspecular(1, 1, 1, 1);
	light1.setAmbiental(0.3, 0.3, 0.3, 1);
	light1.setPosition(0, 0, 3 ,1);
}

//set para activar/desactivar la luz general
void Iluminacion::luzGeneral(){
	if(activa)
		glDisable(GL_LIGHTING);
	else
		glEnable(GL_LIGHTING);
	activa = !activa;
}

//set para activar/desactivar la luz 0
void Iluminacion::turnLight(int num){
	if(num == 0)
		light0.turnLight();
	else
		light1.turnLight();
}

//aplicar las luces
void Iluminacion::aplicar(float alpha1, float beta1, float alpha2, float beta2){
	if(alpha1 < -90) alpha1 = -90;
	if(alpha1 > 90) alpha1 = 90;
	if(beta1 < 0) beta1 = 0;
	if(beta1 > 360) beta1 = 360;
	
	if(alpha2 < -90) alpha2 = -90;
	if(alpha2 > 90) alpha2 = 90;
	if(beta2 < 0) beta2 = 0;
	if(beta2 > 360) beta2 = 360;
	
	light0.aplicar(alpha1, beta1);
	light1.aplicar(alpha2, beta2);
}

