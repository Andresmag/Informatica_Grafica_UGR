//**************************************************************************
// Práctica 1
//
// Andrés Molina López 2016-2017
//
// Implementación de la clase Objeto Básico 3D
//**************************************************************************

#include "OB3D.h"

//Constructor
OB3D::OB3D(){}
	
//**************************************************************************
//Función para dibujar los vertices de una figura geométrica
void OB3D::draw_points(){
	glColor3f(0.0, 1.0, 0.0);
	glPointSize(4);
	glBegin(GL_POINTS);
		
	for(int i=0; i<vertices.size(); i++)
		glVertex3fv((GLfloat *) &vertices[i]);
	
	glEnd();
}
