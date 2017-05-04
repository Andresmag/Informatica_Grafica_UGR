//**************************************************************************
// Práctica 1
//
// Andrés Molina López 2016-2017
//
// Implementacion de la clase Cubo
/*
		  v6
        ·-----·v5			
       /     /|			
	 v2·-----· |			
      |   v1| ·v4
      |     |/
    v3·-----·v0
    
    	Caras del cubo con la división en dos triangulos
		 
	  v2·-----·v1		 v1·-----·v5		v5·-----·v6
		 | \ c0|				| \ c2|			  | \ c4|
		 |  \  |				|  \  |			  |  \  |
		 |c1 \ |				|c3 \ |			  |c5 \ |
	  v3·-----·v0  	 v0·-----·v4  		v4·-----·v7
	  
	  v6·-----·v2		 v6·-----·v5		v3·-----·v0
		 | \ c6|				| \ c8|			  | \c10|
		 |  \  |				|  \  |			  |  \  |
		 |c7 \ |				|c9 \ |			  |c11\ |
	  v7·-----·v3  	 v2·-----·v1  		v7·-----·v4
           
*/
//**************************************************************************

#include "cubo.h"

//Constructor
Cube::Cube(){
	vertices.resize(8);
	//Introducimos los vertices del cubo
	/*v0*/vertices[0] = _vertex3f(0.5,-0.5,0.5);
	/*v1*/vertices[1] = _vertex3f(0.5,0.5,0.5);
	/*v2*/vertices[2] = _vertex3f(-0.5,0.5,0.5);
	/*v3*/vertices[3] = _vertex3f(-0.5,-0.5,0.5);
	/*v4*/vertices[4] = _vertex3f(0.5,-0.5,-0.5);
	/*v5*/vertices[5] = _vertex3f(0.5,0.5,-0.5);
	/*v6*/vertices[6] = _vertex3f(-0.5,0.5,-0.5);
	/*v7*/vertices[7] = _vertex3f(-0.5,-0.5,-0.5);
	
	triangles.resize(12);
	//Separamos los vertices de manera que formen 
	//los triángulos que conforman las caras
	/*c0 */triangles[0] = _vertex3ui(0,1,2);
	/*c1 */triangles[1] = _vertex3ui(0,2,3);
	/*c2 */triangles[2] = _vertex3ui(1,4,5);
	/*c3 */triangles[3] = _vertex3ui(0,4,1);
	/*c4 */triangles[4] = _vertex3ui(7,6,5);
	/*c5 */triangles[5] = _vertex3ui(4,7,5);
	/*c6 */triangles[6] = _vertex3ui(3,2,6);
	/*c7 */triangles[7] = _vertex3ui(7,3,6);
	/*c8 */triangles[8] = _vertex3ui(1,5,6);
	/*c9 */triangles[9] = _vertex3ui(2,1,6);
	/*c10*/triangles[10] = _vertex3ui(0,3,4);
	/*c11*/triangles[11] = _vertex3ui(3,7,4);	
	
}

