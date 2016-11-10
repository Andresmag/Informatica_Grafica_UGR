//**************************************************************************
// Práctica 2 - Examen
//
// Andrés Molina López 2016-2017
//
// Clase para hacer una esfera
//**************************************************************************

#ifndef _ESFERA
#define _ESFERA

#include "figura_rev.h"

class Esfera : public Figura_rev{
public:
	Esfera();
	void Redimensionar(int n);
};

#endif
