//**************************************************************************
// Práctica 5
//
// Andrés Molina López 2016-2017
//
// Implementacion de la clase para el manejo de la camara
//**************************************************************************

#ifndef _CAMARA
#define _CAMARA

#include <GL/gl.h>
#include <vector>

class Camara{
private:
	GLfloat Observer_distance;
	GLfloat Observer_angle_x;
	GLfloat Observer_angle_y;
	bool paralela;
	GLfloat Window_width,Window_height,Front_plane,Back_plane;
	
public:

	Camara(bool valor);
	void girar(float x, float y);
	void zoom(int i);
	void setObservador();
	GLfloat getDistance();
	void setDistance(float front_plane);
	bool getParalela();
	void setParalela();
};

#endif
