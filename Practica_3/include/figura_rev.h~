//**************************************************************************
// Práctica 2
//
// Andrés Molina López 2016-2017
//
// Clase para hacer figuras de revolución
//**************************************************************************

#ifndef _FIGURA_REV
#define _FIGURA_REV

#include "O3D.h"
#include <cmath>
#define PI 3.141592654

class Figura_rev : public O3D{
private:
	vector<_vertex3f> figura_guardada;
public:
	Figura_rev();
	_vertex3f RotarY(_vertex3f p, float ang);
	void GenerarFigura(vector<_vertex3f> verts, int n);
	void Modificar_divisiones(int div);
};

#endif
