//**************************************************************************
// Práctica 1
//
// Andrés Molina López 2016-2017
//
// Implementacion de la clase Tetraedro
/*
		  		v0	· 
    			  / \/
    			 /   \/
    			/     \ /
    		v1·-------·v2
    			 
    	Caras del tetraedro
		 
	  		v0	· 				   v0 ·					v0 ·					v3 ·
    		  / \				     / \					  / \					  / \
    		 /   \		       /   \				 /   \				 /   \
    		/ c0  \			   / c1  \				/ c2  \				/ c3  \
    	v1·-------·v2	   v2·-------·v3		v3·-------·v1		v1·-------·v2
           
*/
//**************************************************************************

#include "tetraedro.h"

//Constructor
Tetraedro::Tetraedro(){
	vertices.resize(4);
	//Introducimos los vertices del cubo
	/*v0*/vertices[0] =_vertex3f(0,0.5,0);
	/*v1*/vertices[1] = _vertex3f(-0.5,-0.5,0.5);
	/*v2*/vertices[2] = _vertex3f(0.5,-0.5,0.5);
	/*v3*/vertices[3] = _vertex3f(0,-0.5,-0.5);

	triangles.resize(4);
	//Separamos los vertices de manera que formen 
	//los triangulos de cada cara
	/*c0 */triangles[0] = _vertex3ui(0,1,2);
	/*c1 */triangles[1] = _vertex3ui(0,2,3);
	/*c2 */triangles[2] = _vertex3ui(0,3,1);
	/*c3 */triangles[3] = _vertex3ui(3,2,1);
	
}
