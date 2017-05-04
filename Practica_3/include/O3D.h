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
	
public:
	
	O3D();
	
	void draw(char modo);
	
};

#endif
