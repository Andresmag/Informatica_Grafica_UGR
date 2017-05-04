//**************************************************************************
// Práctica 2
//
// Andrés Molina López 2016-2017
//
// Clase PLY
//**************************************************************************

#ifndef _PLY
#define _PLY

#include "O3D.h"
#include "file_ply_stl.h"

class Modelo_PLY : public O3D{	
public:
	
	Modelo_PLY();
	void CargarPLY(char * file_name);
	
};

#endif
