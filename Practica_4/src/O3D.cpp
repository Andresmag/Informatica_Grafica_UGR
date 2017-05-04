//**************************************************************************
// Práctica 1
//
// Andrés Molina López 2016-2017
//
// Implementación de la clase Objeto 3D
//**************************************************************************

#include "O3D.h"

//Constructor
O3D::O3D(){
	pintar_normales_caras = false;
	pintar_normales_vertices = false;
	
	//Blanco plastico
	mat_ambiental[0] = 0.1;
	mat_ambiental[1] = 0.2;
	mat_ambiental[2] = 0;
	mat_ambiental[3] = 1;
	
	mat_especular[0] = 0.7;
	mat_especular[1] = 0.7;
	mat_especular[2] = 0.7;
	mat_especular[3] = 1;
	
	mat_difusa[0] = 0.2;
	mat_difusa[1] = 0.2;
	mat_difusa[2] = 0.2;
	mat_difusa[3] = 1;
	
	shininess = 1000;
}

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
			if(modo == 'c' && i%2 == 0){
					glColor3f(1.0,1.0,0.0);
			}
			else{
				if(modo == 's' || modo == 'c'){
						glColor3f(0.5,0.0,0.5);
				}
				else{
						glColor3f(1.0,0.0,0.0);
				}
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
	
	if(pintar_normales_caras){
		glBegin(GL_LINES);
		for(int i=0; i<normalesCaras.size(); i++){
			_vertex3f punto_medio, extremo;
			punto_medio = (vertices[triangles[i].x] + vertices[triangles[i].y] + vertices[triangles[i].z])/3;
			extremo = punto_medio + normalesCaras[i];
			
			glVertex3f(punto_medio.x, punto_medio.y, punto_medio.z);
			glVertex3f(extremo.x, extremo.y, extremo.z);
		}
		glEnd();
	}
	
	if(pintar_normales_vertices){
		glBegin(GL_LINES);
		for(int i=0; i<normalesVertices.size(); i++){
			_vertex3f extremo;
			extremo = normalesVertices[i] + vertices[i];
			
			glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
			glVertex3f(extremo.x, extremo.y, extremo.z);
		}
		glEnd();
	}
}

//**************************************************************************
//Función que sirve para dibujar en modo iluminado flat
void O3D::draw_iluminado(){
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambiental);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_especular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difusa);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	glShadeModel(GL_FLAT);
	glBegin(GL_TRIANGLES);
		for(int i=0; i<triangles.size(); i++){
			glNormal3fv((GLfloat *) &normalesCaras[i]);
			
			int vertex1,vertex2,vertex3;
			
			vertex1=triangles[i].x;
			vertex2=triangles[i].y;
			vertex3=triangles[i].z;
			
			glVertex3fv((GLfloat *) &vertices[vertex1]);
			glVertex3fv((GLfloat *) &vertices[vertex2]);
			glVertex3fv((GLfloat *) &vertices[vertex3]);
		}
	glEnd();
}	

//**************************************************************************
//Función que sirve para dibujar en modo iluminado smooth
void O3D::draw_suavizado(){
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambiental);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_especular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difusa);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	glShadeModel(GL_SMOOTH);
	glBegin(GL_TRIANGLES);
		for(int i=0; i<triangles.size(); i++){			
			int vertex1,vertex2,vertex3;
			
			vertex1=triangles[i].x;
			vertex2=triangles[i].y;
			vertex3=triangles[i].z;
			
			glNormal3fv((GLfloat *) &normalesVertices[vertex1]);
			glVertex3fv((GLfloat *) &vertices[vertex1]);
			glNormal3fv((GLfloat *) &normalesVertices[vertex2]);
			glVertex3fv((GLfloat *) &vertices[vertex2]);
			glNormal3fv((GLfloat *) &normalesVertices[vertex3]);
			glVertex3fv((GLfloat *) &vertices[vertex3]);
		}
	glEnd();
}
//**************************************************************************
//Función que sirve para calcular las normales de las caras
void O3D::NormalizarCaras(){
	_vertex3f vector1, vector2, prod_vectorial;
	normalesCaras.resize(triangles.size());
	for(int i=0; i<triangles.size();i++){
		vector1 = vertices[triangles[i].y] - vertices[(triangles[i].x)];
		vector2 = vertices[triangles[i].z] - vertices[(triangles[i].x)];
		
		prod_vectorial = vector1.cross_product(vector2);
		prod_vectorial.normalize();
		
		normalesCaras[i] = prod_vectorial;
	}
}

//**************************************************************************
//Función que sirve para calcular las normales de los vertices
void O3D::NormalizarVertices(){
	_vertex3f vector1, vector2, prod_vectorial;
	normalesVertices.resize(vertices.size());
	for(int i=0; i<triangles.size();i++){
		normalesVertices[triangles[i].x] += normalesCaras[i];
		normalesVertices[triangles[i].y] += normalesCaras[i];
		normalesVertices[triangles[i].z] += normalesCaras[i];
	}
	
	for(int i=0; i<normalesVertices.size(); i++)
		normalesVertices[i] = normalesVertices[i].normalize();
}

//**************************************************************************
//Función para activar pintar las normales de las caras
void O3D::SetNormalesCaras(bool val){
	pintar_normales_caras = val;
}

//**************************************************************************
//Función para activar pintar las normales de los vertices
void O3D::SetNormalesVertices(bool val){
	pintar_normales_vertices = val;
}

//**************************************************************************
//Función para saber si hay que pintar las normales de las caras o no
bool O3D::getNormalesCaras(){
	return pintar_normales_caras;
}

//**************************************************************************
//Función para saber si hay que pintar los vertices de las caras o no
bool O3D::getNormalesVertices(){
	return pintar_normales_vertices;
}

//**************************************************************************
//Función para cambiar el material del objeto
void O3D::setMaterial(GLfloat a[], GLfloat d[], GLfloat e[], float s){
	for(int i=0; i<4; i++){
		mat_ambiental[i] = a[i];
		mat_difusa[i] = d[i];
		mat_especular[i] = e[i];
	}
	shininess = s;
}


