//**************************************************************************
// Práctica 1
//
// Andrés Molina López 2016-2017
//
// Clase Objeto Básico 3D
//**************************************************************************

#ifndef _OB3D
#define _OB3D

#include <vector>
#include "vertex.h"
#include <GL/glut.h>

class OB3D{
protected:
	vector<_vertex3f> vertices;
	bool seleccionado;
	
public:
	
	OB3D();
	
	void draw_points();
	void setSeleccionado(bool val);
	
};
	
#endif
