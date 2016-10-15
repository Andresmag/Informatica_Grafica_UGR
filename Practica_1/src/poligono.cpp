//**************************************************************************
// Práctica 1 - ampliación examen
//
// Andrés Molina López 2016-2017
//
// Implementación de la clase Poligono
//**************************************************************************

#include "poligono.h"

//Constructor
Poligono::Poligono(int num_vertices){
	//Punto inicial de la circunferencia
	/*v0*/vertices.push_back(_vertex3f(0.0,0.0,0.0));
	
	//Calculamos en cuantos trozos tiene que dividirse la circunferencia
	//El radio de la circunferencia al ser unitaria va a ser 1
	//por lo tanto el primer punto será siempe el (1,0)
	
	/*v1*/vertices.push_back(_vertex3f(1.0,0.0,0.0));
	
	float radianes_division = (360/num_vertices) * (PI/180);
	float acumulacion = radianes_division;
	
	for(int i=1; i<num_vertices; i++){
		if(acumulacion <= PI/2){
			vertices.push_back(_vertex3f(cos(acumulacion),sin(acumulacion),0.0));
		}
		else if(acumulacion > PI/2 && acumulacion <= PI){
			vertices.push_back(_vertex3f(cos(acumulacion),sin(acumulacion),0.0));
		}
		else if(acumulacion > PI && acumulacion <= 3*PI/2){
			vertices.push_back(_vertex3f(cos(acumulacion),sin(acumulacion),0.0));
		}
		else{
			vertices.push_back(_vertex3f(cos(acumulacion),sin(acumulacion),0.0));
		}
		
		acumulacion += radianes_division;
	}
	
	//Una vez sabemos los puntos y estan guardados en el vector de vertices hacemos las caras
	for(int i=1; i<num_vertices; i++)
		triangles.push_back(_vertex3ui(0,i,i+1));
		
	triangles.push_back(_vertex3ui(0,num_vertices,1)); // para cerrar el poligono
}

//**************************************************************************
//Dibujar draw_fan
void Poligono::draw_fan(char modo){
	switch(modo){
		case 'a':
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
			break;
		default:
			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
			break;
	}
	
	glBegin(GL_TRIANGLE_FAN);
	
	int vertex1,vertex2,vertex3;
		
	for(int i=0; i<triangles.size(); i++){
		if(modo == 'c' && i%2 == 0)
			glColor3f(1.0,1.0,1.0);
		else{
			if(modo == 's' || modo == 'c')
				glColor3f(0.0,0.0,0.0);
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
