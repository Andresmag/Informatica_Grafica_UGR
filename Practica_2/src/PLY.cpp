//**************************************************************************
// Práctica 2
//
// Andrés Molina López 2016-2017
//
// Implementación de la clase PLY
//**************************************************************************

#include "PLY.h"

//Constructor
Modelo_PLY::Modelo_PLY(){}

//Constructor al cual se le pasa un archivo
void Modelo_PLY::CargarPLY(char *file_name){
	//Limpiamos lo que hay en el modelo cargado
	vertices.clear();
	triangles.clear();
	
	//Guardamos los puntos del PLY en el modelo
	vector<float> vertices_ply;
	vector<int> triangles_ply;
	
	_file_ply ply;
	ply.open(file_name);
	ply.read(vertices_ply, triangles_ply);
	
	vertices.resize(vertices_ply.size()/3);
	triangles.resize(triangles_ply.size()/3);
	
	for(int i=0; i<vertices_ply.size(); i+=3){
		vertices[i/3] = _vertex3f(vertices_ply[i], vertices_ply[i+1], vertices_ply[i+2]);
	}

	for(int i=0; i<triangles_ply.size(); i+=3){
		triangles[i/3] = _vertex3ui(triangles_ply[i], triangles_ply[i+1], triangles_ply[i+2]);
	}


}
