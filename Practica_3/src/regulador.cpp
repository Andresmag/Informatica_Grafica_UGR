//**************************************************************************
// Práctica 3
//
// Andrés Molina López 2016-2017
//
// Implementacion de la clase Regulador
//**************************************************************************

#include "regulador.h"

//Constructor
Regulador::Regulador(){
	rotacion = 0;
	velocidad = 0;
	cambiarVelocidad(0);
}

// Modifica el valor de la rotacion
void Regulador::cambiarVelocidad(double incremento){
	velocidad += incremento;
	if(velocidad > 30)
		velocidad = 30;
	if(velocidad < 0)
		velocidad = 0;
		
	double alpha = 35+velocidad*1.63;
	double beta = 180-alpha*2;
	pieza.setDistancia(alpha, beta);
}

void Regulador::mover() {
	rotacion += velocidad/6;
	base.setRotacion(rotacion);
}

//Funcion para dibujar el regulador
void Regulador::draw(char modo){
	base.draw(modo);	
	
	glPushMatrix();
	glRotatef(rotacion,0,1,0);
	glTranslatef(0,13.5,0);
	pieza.draw(modo);
	glPopMatrix();

}
