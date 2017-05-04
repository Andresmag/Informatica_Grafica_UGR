//**************************************************************************
// Práctica 4
//
// Andrés Molina López 2016-2017
//
// Clase para el manejo de la luz general
//**************************************************************************

#ifndef _ILUMINACION
#define _ILUMINACION

#include "luz.h"

class Iluminacion{
private:
	bool activa;
	Luz light0;
	Luz light1;

public:
	Iluminacion();
	void luzGeneral();
	void turnLight(int num);
	bool getLuzGeneral();
	void aplicar(float alpha1, float beta1, float alpha2, float beta2);
};

#endif
