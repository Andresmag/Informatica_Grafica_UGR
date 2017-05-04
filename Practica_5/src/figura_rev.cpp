//**************************************************************************
// Práctica 2
//
// Andrés Molina López 2016-2017
//
// Implementación de la clase figura_rev
//**************************************************************************

#include "figura_rev.h"

/**************************************************/
//Constructor
Figura_rev::Figura_rev(){}

/**************************************************/
//Función que rota una posicion alredor del eje y
_vertex3f Figura_rev::RotarY(_vertex3f p, float ang){
	_vertex3f r;
	r.x = cos(ang)*p.x + sin(ang)*p.z;
	r.y = p.y;
	r.z = -sin(ang)*p.x + cos(ang)*p.z;
	return r;
}

/**************************************************/
//Función que genera una figura de revolucion
void Figura_rev::GenerarFigura(vector<_vertex3f> perfil, int n){
	//Para saber cual es la ultima figura que hemos dibujado y poder
	//modificar las divisiones
	figura_guardada = perfil;
	
	bool tapa_superior = false;
	bool tapa_inferior = false;
	_vertex3f tapa_arriba;
	_vertex3f tapa_abajo;
	
	//Limpiamos los vectores
	vertices.clear();
	triangles.clear();

	//Comprobamos si tiene tapa superior y en caso de tenerla
	//la guardamos aparte y la quitamos del perfil
	if(perfil[0].x == 0){
		tapa_arriba.x = perfil[0].x;
		tapa_arriba.y = perfil[0].y;
		tapa_arriba.z = perfil[0].z;
		tapa_superior = true;
		perfil.erase(perfil.begin());
	}
		
	
	//Comprobamos si tiene tapa inferior y en caso de tenerla
	//la guardamos aparte y la quitamos del perfil
	if(perfil[perfil.size()-1].x == 0){
		tapa_abajo.x = perfil[perfil.size()-1].x;
		tapa_abajo.y = perfil[perfil.size()-1].y;
		tapa_abajo.z = perfil[perfil.size()-1].z;
		tapa_inferior = true;
		perfil.pop_back();
	}	
	
	vertices = perfil; //metemos el perfil en el vector de vertices
	float angulo = (2*PI)/n; // calculamos en los trozos que hay que dividir la circunferencia
	int k = perfil.size();
	vertices.resize((n+1)*k); //redimensionamos el vector de vertices 
	int pos_triangles = 0;
	triangles.resize((k-1)*n*2); //redimensionamos el vector de triangulos
	
	//Creamos los vertices que van a formar los lados de la figura, y sus correspondientes caras
	for(int i=0; i<n; i++){
		perfil[0] = RotarY(perfil[0], angulo);
		vertices[k++] = perfil[0];
		for(int j=1; j<perfil.size(); j++){
			//genero la rotacion del punto
			perfil[j] = RotarY(perfil[j], angulo);
			vertices[k] = perfil[j];
			
			//genero las caras y las			
			//introduzco las caras generadas en el vector
			triangles[pos_triangles++] = _vertex3ui(k, k-1, k-perfil.size()-1);
			triangles[pos_triangles++] = _vertex3ui(k, k-perfil.size()-1, k-perfil.size());
			
			k++;
		}
	}
		
	//Añadimos la tapa superior, tanto el vertice como las caras
	if(tapa_superior){
		triangles.resize(triangles.size() + n);
		vertices.push_back(tapa_arriba);
		int pos_vertices = 0;
		for(int i=0; i<n; i++){
			 triangles[pos_triangles++] = _vertex3ui(vertices.size()-1,pos_vertices,(pos_vertices+perfil.size()));
			 pos_vertices += perfil.size();
		}
	}
	
	//Añadimos la tapa superior, tanto el vertice como las caras
	if(tapa_inferior){
		triangles.resize(triangles.size() + n);
		vertices.push_back(tapa_abajo);
		int pos_vertices = perfil.size()-1;
		
		for(int i=0; i<n; i++){
			triangles[pos_triangles++] = _vertex3ui(vertices.size()-1, (pos_vertices+perfil.size()),  pos_vertices);
			pos_vertices += perfil.size();
		}
	}
	
	NormalizarCaras();
	NormalizarVertices();
}

/**************************************************/
//Función que modifica las divisiones de la figura guardada
void Figura_rev::Modificar_divisiones(int div){
	GenerarFigura(figura_guardada, div);
}

