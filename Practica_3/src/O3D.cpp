//**************************************************************************
// Práctica 1
//
// Andrés Molina López 2016-2017
//
// Implementación de la clase Objeto 3D
//**************************************************************************

#include "O3D.h"

//Constructor
O3D::O3D(){}

//**************************************************************************
//Función que sirve para dibujar las aristas, o las caras tanto en solido
//del mismo color, como en ajedrez de un figura
void O3D::draw(char modo){
	switch(modo){
		case 'a':
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
			break;
		default:
			glPolygonMode(GL_FRONT,GL_FILL);
			break;
	}
	
	if(modo == 'p')
		draw_points();
	else{
		glBegin(GL_TRIANGLES);
	
		int vertex1,vertex2,vertex3;
		
		for(int i=0; i<triangles.size(); i++){
			if(modo == 'c' && i%2 == 0)
				glColor3f(1.0,1.0,0);
			else{
				if(modo == 's' || modo == 'c')
					glColor3f(0.5,0.0,0.5);
				else
					glColor3f(1.0, 0.0, 0.0);
			}
			
			vertex1=triangles[i].x;
			vertex2=triangles[i].y;
			vertex3=triangles[i].z;
			
			glVertex3fv((GLfloat *) &vertices[vertex1]);
			glVertex3fv((GLfloat *) &vertices[vertex2]);
			glVertex3fv((GLfloat *) &vertices[vertex3]);
		}

		glEnd();
	}
}

















