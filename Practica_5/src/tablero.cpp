//**************************************************************************
// Práctica 4
//
// Andrés Molina López 2016-2017
//
// Implementacion de la clase Tablero
//**************************************************************************

#include "tablero.h"

//Constructor
Tablero::Tablero(){
	A(-0.5,0,-0.5);
	B(0.5,0,-0.5);
	C(-0.5,0,0.5);
	D(0.5,0,0.5);
	num_divisiones = 1;
	Dimensionar(num_divisiones);
}

//Calcular los vertices y triangulos del tablero
void Tablero::Dimensionar(int divisiones){
	num_divisiones = divisiones;
	float div_x = (B.x - A.x)/divisiones;
	float div_z = (C.z - A.z)/divisiones;
	vector<float> valores_x(divisiones+1);
	vector<float> valores_z(divisiones+1);
	valores_x[0] = A.x;
	valores_z[0] = A.z;
	
	//Rellenamos el vector con los puntos que va a tomar la x y la z
	for(int i=1; i<divisiones+1; i++){
		valores_x[i] = valores_x[i-1] + div_x;
		valores_z[i] = valores_z[i-1] + div_z;
	}
	
	//Rellenaos el vector de vertices
	int num_vertices = (divisiones+1)*(divisiones+1);
	vertices.resize(num_vertices);
	int k=0;
	
	for(int i=0; i<divisiones+1; i++){
		for(int j=0; j<divisiones+1; j++){
			if(k == 0){
				vertices[k] = A;
			}
			else if(k == divisiones){
				vertices[k] = B;
			}
			else if(k == (num_vertices-divisiones-1)){
				vertices[k] = C;
			}
			else if(k == (num_vertices-1)){
				vertices[k] = D;
			}
			else{
				vertices[k] = _vertex3f(valores_x[j], 0, valores_z[i]);	
			}
			k++;
		}
	}
	
	//Rellenamos el vector de triangulos
	triangles.resize(2*divisiones*divisiones);
	k=0;
	
	for(int i=0; i<vertices.size()-divisiones-1; i+=divisiones+1){
		for(int j=i; j<i+divisiones; j++){
			triangles[k] = _vertex3ui(j+divisiones+1, j+1, j);
			k++;
			triangles[k] = _vertex3ui(j+divisiones+2, j+1, j+divisiones+1);
			k++;
		}
	}
}

//Cambiar el numero de divisiones
void Tablero::setDivisiones(int valor){
	if(valor < 1)
		valor = 1;
	num_divisiones = valor;
	Dimensionar(num_divisiones);
}

//Ver cuantas divisiones hay
int Tablero::getDivisiones(){
	return num_divisiones;
}
