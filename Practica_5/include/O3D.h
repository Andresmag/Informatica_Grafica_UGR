//**************************************************************************
// Práctica 1
//
// Andrés Molina López 2016-2017
//
// Clase Objeto 3D
//**************************************************************************

#ifndef _O3D
#define _O3D

#include "OB3D.h"

class O3D : public OB3D{
protected:
	vector<_vertex3ui> triangles;
	vector<_vertex3f> normalesCaras;
	vector<_vertex3f> normalesVertices;
	
	bool pintar_normales_caras;
	bool pintar_normales_vertices;
	
	//Materiales
	GLfloat mat_ambiental[4];
	GLfloat mat_especular[4];
	GLfloat mat_difusa[4];
	float shininess;
	
public:
	
	O3D();
	
	void draw(char modo);
	void draw_iluminado();
	void draw_suavizado();
	
	void NormalizarCaras();
	void NormalizarVertices();
	
	void SetNormalesCaras(bool val);
	void SetNormalesVertices(bool val);
	
	bool getNormalesCaras();
	bool getNormalesVertices();
	
	void setMaterial(GLfloat a[], GLfloat d[], GLfloat e[], float s);
};

#endif
