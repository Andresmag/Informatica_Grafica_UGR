//**************************************************************************
// Práctica 4
//
// Andrés Molina López 2016-2017
//
// Clase para el manejo de la luz
//**************************************************************************

#ifndef _LUZ
#define _LUZ

#include <GL/glut.h>

class Luz{
private:
	GLenum tipo;
	bool activa;
	GLfloat difusa[4];
	GLfloat especular[4];
	GLfloat ambiental[4];
	GLfloat position[4];
	
public:
	Luz(GLenum num);
	void turnLight();
	void setDifusa(float a, float b, float c, float d);
	void setEspecular(float a, float b, float c, float d);
	void setAmbiental(float a, float b, float c, float d);
	void setPosition(float a, float b, float c, float d);
	void aplicar(float a, float b);
};

#endif
