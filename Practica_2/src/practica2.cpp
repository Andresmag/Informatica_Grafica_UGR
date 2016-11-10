//**************************************************************************
// Práctica 2
//
// Andrés Molina López 2016-2017
//
// Cuerpo principal del programa
/*
	La práctica es una continuación de la anterior, de manera que sigue 
	integrando la visualización del cubo y del tetrado, pero además se han
	añadidos dos posibilidades:
		- La primera es la capacidad de leer de un fichero .ply, cargar la 
		figura que este contiene y poder visualizarla.
		- La segunda es la capacidad de crear y visualizar figuras de revolución
		a patir de un perfil dado y un número de vueltas, de manera que crea
		la figura rotando el perfil dado alrededor del eje Y el número de veces
		indicado.
*/
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include "cubo.h"
#include "tetraedro.h"
#include "PLY.h"
#include "figura_rev.h"
#include "vertex.h"
#include "esfera.h"
#include "piramide.h"
#include <vector>

// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

// Creamos el cubo y el tetraedro
Cube cubo;
Tetraedro tetraedro;

//Creamos un objeto PLY
Modelo_PLY modelo;

//Creamos una figura de revolucion
Figura_rev figura;

//Creamos la esfera
Esfera esfera;

//Creamos la piramide
Piramide piramide;

//Creamos los perfiles de las figuras
//Cilindro
vector<_vertex3f> cilindro(4);
//vaso
vector<_vertex3f> vaso(3);
//vaso invertido
vector<_vertex3f> vaso_inv(3);
//cono
vector<_vertex3f> cono(3);
//tubo
vector<_vertex3f> tubo(2);

// Creamos las varibles de control para saber que figura hay que dibujar y
// de que manera
char draw_obj = 'c'; // la inicializamos en c para que al empezar esté dibujado el cubo
/*
	Modos posibles:
	c -> cubo
	t -> tetraedro
	p -> ply
	f -> figura revolucion
*/

char mode = 's';	// la inicializamos en s para que el dibujo inicial sea en solido
/*
	Modos posibles:
	p -> puntos
	s -> solido
	c -> ajedrez
	a -> aristas
	t -> todo
*/

int divisiones = 10; //numero de veces que rotamos el perfil

char especiales_rev;
/*
	x -> no está activo
	e -> esfera
	p -> piramide
*/

//**************************************************************************
//
//***************************************************************************

void clear_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{
	switch(draw_obj){
		case 'c':
			switch(mode){
				case 'p':
					cubo.draw_points();
					break;
				case 't':
					mode = 'a';
					cubo.draw(mode);
					cubo.draw_points();
					mode = 's';
					cubo.draw(mode);
					mode = 't'; // Para que no se cambia a dibujar solido
					break;
				default:
					cubo.draw(mode);
					break;
			}
			break;
		
		case 't':
		switch(mode){
				case 'p':
					tetraedro.draw_points();
					break;
				case 't':
					mode = 'a';
					tetraedro.draw(mode);
					tetraedro.draw_points();
					mode = 's';
					tetraedro.draw(mode);
					mode = 't';
					break;
				default:
					tetraedro.draw(mode);
					break;
			}
			break;
			
		case 'p':
		switch(mode){
				case 'p':
					modelo.draw_points();
					break;
				case 't':
					mode = 'a';
					modelo.draw(mode);
					modelo.draw_points();
					mode = 's';
					modelo.draw(mode);
					mode = 't';
					break;
				default:
					modelo.draw(mode);
					break;
			}
			break;
			
		case 'f':
			if(especiales_rev == 'e'){
				switch(mode){
						case 'p':
							esfera.draw_points();
							break;
						case 't':
							mode = 'a';
							esfera.draw(mode);
							esfera.draw_points();
							mode = 's';
							esfera.draw(mode);
							mode = 't';
							break;
						default:
							esfera.draw(mode);
							break;
				}
			}
			else{
				switch(mode){
						case 'p':
							if(especiales_rev == 'p'){
								glPushMatrix();
								glRotatef(45,0,1,0);
								piramide.draw_points();
								glPopMatrix();
							}
							else
								figura.draw_points();
							break;
						case 't':
							mode = 'a';
							if(especiales_rev == 'p'){
								glPushMatrix();
								glRotatef(45,0,1,0);
								piramide.draw(mode);
								piramide.draw_points();
								mode = 's';
								piramide.draw(mode);
								glPopMatrix();
							}
							else{
								figura.draw(mode);
								figura.draw_points();
								mode = 's';
								figura.draw(mode);
							}
							mode = 't';
							break;
						default:
							if(especiales_rev == 'p'){
								glPushMatrix();
								glRotatef(45,0,1,0);
								piramide.draw(mode);
								glPopMatrix();
							}
							else
								figura.draw(mode);
							break;
				}
			}
			break;
	}
}


//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{

clear_window();
change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{
	switch(toupper(Tecla1)){
		case 'Q':
			exit(0);
			break;
		case 'P':
			mode = 'p';
			break;
		case 'A':
			mode = 'a';
			break;
		case 'S':
			mode = 's';
			break;
		case 'C':
			mode = 'c';
			break;
		case 'T':
			mode = 't';
			break;
		case '1':
			if(draw_obj == 'p'){
				modelo.CargarPLY("data/armadillo.ply");
			}
			else if(draw_obj == 'f'){
				especiales_rev = 'x';
				figura.GenerarFigura(cilindro, divisiones);
			}
			glutPostRedisplay();
			break;
		case '2':
			if(draw_obj == 'p'){
				modelo.CargarPLY("data/beethoven.ply");
			}
			else if(draw_obj == 'f'){
				especiales_rev = 'x';
				figura.GenerarFigura(vaso, divisiones);
			}
			glutPostRedisplay();
			break;
		case '3':
			if(draw_obj == 'p'){
				modelo.CargarPLY("data/big_dodge.ply");
			}
			else if(draw_obj == 'f'){
				especiales_rev = 'x';
				figura.GenerarFigura(vaso_inv, divisiones);
			}
			glutPostRedisplay();
			break;
		case '4':
			if(draw_obj == 'p'){
				modelo.CargarPLY("data/big_porsche.ply");
			}
			else if(draw_obj == 'f'){
				especiales_rev = 'x';
				figura.GenerarFigura(cono, divisiones);
			}
			glutPostRedisplay();
			break;
		case '5':
			if(draw_obj == 'p'){
				modelo.CargarPLY("data/big_spider.ply");
			}
			else if(draw_obj == 'f'){
				especiales_rev = 'x';
				figura.GenerarFigura(tubo, divisiones);
			}
			glutPostRedisplay();
			break;
		case '6':
			if(draw_obj == 'f'){
				especiales_rev = 'e';
				esfera.Redimensionar(divisiones);
				esfera.Modificar_divisiones(divisiones);
			}
			glutPostRedisplay();
			break;
		case '7':
			if(draw_obj == 'f'){
				especiales_rev = 'p';
				piramide.Modificar_divisiones(4); //Siempre es 4 ya que si tuviese mas caras no seria una piramide
			}
			glutPostRedisplay();
			break;
		case '-':
			if(draw_obj == 'f' && especiales_rev != 'p'){
				if(divisiones > 3)
					divisiones--;
				if(especiales_rev == 'e'){
					esfera.Redimensionar(divisiones);
					esfera.Modificar_divisiones(divisiones);
				}
				figura.Modificar_divisiones(divisiones);
			}
			glutPostRedisplay();
			break;
		case '+':
			if(draw_obj == 'f' && especiales_rev != 'p'){
				divisiones++;
				if(especiales_rev == 'e'){
					esfera.Redimensionar(divisiones);
					esfera.Modificar_divisiones(divisiones);
				}
				figura.Modificar_divisiones(divisiones);
			}
			glutPostRedisplay();
			break;
			
	}

}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	case GLUT_KEY_F1: draw_obj = 't'; break;
	case GLUT_KEY_F2: draw_obj = 'c'; break;
	case GLUT_KEY_F3: draw_obj = 'p'; break;
	case GLUT_KEY_F4: draw_obj = 'f'; break;
	}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Window_width=0.5;
Window_height=0.5;
Front_plane=1;
Back_plane=1000;

// se inicia la posicion del observador, en el eje z
Observer_distance=2*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
//
change_projection();
//
glViewport(0,0,UI_window_width,UI_window_height);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{

// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(UI_window_width,UI_window_height);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("Práctica 2");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw_scene);
// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "tecla_normal" al evento correspondiente
glutKeyboardFunc(normal_keys);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_keys);

// funcion de inicialización
initialize();
modelo.CargarPLY("data/beethoven.ply");

//Rellenamos los perfiles de las figuras
//cilindro
cilindro[0] = _vertex3f(0,0.5,0);
cilindro[1] = _vertex3f(0.5,0.5,0);
cilindro[2] = _vertex3f(0.5,-0.5,0);
cilindro[3] = _vertex3f(0,-0.5,0);

//vaso
vaso[0] = _vertex3f(0.5,0.5,0);
vaso[1] = _vertex3f(0.25,-0.5,0);
vaso[2] = _vertex3f(0,-0.5,0);

//vaso invertido
vaso_inv[0] = _vertex3f(0,0.5,0);
vaso_inv[1] = _vertex3f(0.25,0.5,0);
vaso_inv[2] = _vertex3f(0.5,-0.5,0);

//cono
cono[0] = _vertex3f(0,0.5,0);
cono[1] = _vertex3f(0.5,-0.5,0);
cono[2] = _vertex3f(0,-0.5,0);

//tubo
tubo[0] = _vertex3f(0.5,0.5,0);
tubo[1] = _vertex3f(0.5,-0.5,0);

//Cargamos por defecto el cilindro
figura.GenerarFigura(cilindro, divisiones);

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
