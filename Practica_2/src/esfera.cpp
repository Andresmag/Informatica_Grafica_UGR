//**************************************************************************
// Práctica 2
//
// Andrés Molina López 2016-2017
//
// Implementacion de la clase Esfera
//**************************************************************************

#include "esfera.h"

//Constructor
Esfera::Esfera(){}

//Funcion para redimensionar el perfil de la esfera
void Esfera::Redimensionar(int n){
	perfil_esfera.clear();
	perfil_esfera.resize(n+1);
	
	//Para dividir un semicirculo en n puntos,
	//y que ese semicirculo sea el semicirculo derecho
	float tam_division = (PI/n);
	float pos = PI/2;
	
	//Introduzco el pimer punto a mano ya que c++ no es capaz de dar el resultado
	//correcto para cos(PI/2)
	perfil_esfera[0] = _vertex3f(0,1,0);
	pos -= tam_division;
	
	//introducimos el punto superior de la circunferencia
	for(int i=1; i<n; i++){
		perfil_esfera[i] = _vertex3f(cos(pos), sin(pos), 0);
		pos -= tam_division;
	}
	
	//Y el ultimo lo introduzco a mano por el mismo motivo que el primero
	perfil_esfera[n] = _vertex3f(0,-1,0);
	
}

//get del perfil
vector<_vertex3f> Esfera::getPerfil(){
	return perfil_esfera;
}	
	
