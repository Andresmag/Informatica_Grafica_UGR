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
	figura_guardada.clear();
	figura_guardada.resize(n+1);
	
	//Para dividir un semicirculo en n puntos,
	//y que ese semicirculo sea el semicirculo derecho
	float tam_division = (PI/n);
	float pos = PI/2;
	
	//Introduzco el pimer punto a mano ya que c++ no es capaz de dar el resultado
	//correcto para cos(PI/2)
	figura_guardada[0] = _vertex3f(0,1,0);
	pos -= tam_division;
	
	//introducimos el punto superior de la circunferencia
	for(int i=1; i<n; i++){
		figura_guardada[i] = _vertex3f(cos(pos), sin(pos), 0);
		pos -= tam_division;
	}
	
	//Y el ultimo lo introduzco a mano por el mismo motivo que el primero
	figura_guardada[n] = _vertex3f(0,-1,0);
	
	Modificar_divisiones(n);
	
}
	
