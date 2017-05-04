//**************************************************************************
// Práctica 3
//
// Andrés Molina López 2016-2017
//
// Cuerpo principal del programa
/*
	Esta practica se ha diseñado un regulador de Watt por medio de un modelo
	jerarquico. El modelo se puede ver con los distintos tipos de visualización
	usados anteriormente, y ademas se puede hacer que empiece girar con la tecla K
	de manera que cada vez que se le de va ganando velocidad, y con la tecla L se 
	le puede reducir la velocidad.
*/
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include <unistd.h>
#include "cubo.h"
#include "tetraedro.h"
#include "PLY.h"
#include "figura_rev.h"
#include "vertex.h"
#include "esfera.h"
#include "piramide.h"
#include "regulador.h"
#include "tablero.h"
#include "iluminacion.h"
#include "camara.h"
#include <vector>

// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
/*GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;*/

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

//Creamos el regulador de watt
Regulador regulador_watt;

//Creamos el tablero
Tablero tablero;

//Cremaos las dos luces que necesitamos
Iluminacion luces;

//Creamos la camara
Camara camara(false);

//Vector de beethovens
vector<Modelo_PLY> modelos;


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
char draw_obj = 'o'; // la inicializamos en c para que al empezar esté dibujado el cubo
/*
	Modos posibles:
	c -> cubo
	t -> tetraedro
	p -> ply
	f -> figura revolucion
	r -> regulador de watt
	o -> tablero
*/

char mode = 'c';	// la inicializamos en s para que el dibujo inicial sea en solido
/*
	Modos posibles:
	p -> puntos
	s -> solido
	c -> ajedrez
	a -> aristas
	t -> todo
*/

int divisiones = 50; //numero de veces que rotamos el perfil

char especiales_rev;
/*
	x -> no está activo
	e -> esfera
	p -> piramide
*/

float alpha_luz0 = 0;
float beta_luz0 = 0;

float alpha_luz1 = 0;
float beta_luz1 = 0;

bool iluminado = false;
bool suavizado = false;

//Materiales
GLfloat ambiental_bronze[] ={0.2125, 0.1275, 0.054, 1};
GLfloat difusa_bronze[] ={0.7, 0.7, 0.7, 1};
GLfloat especular_bronze[] ={0.393548, 0.271906, 0.166721, 1};
float shininess_bronze = 10;

GLfloat ambiental_wplastic[] ={0.1, 0.2, 0, 1};
GLfloat difusa_wplastic[] ={0.2, 0.2, 0.2, 1};
GLfloat especular_wplastic[] ={0.7, 0.7, 0.7, 1};
float shininess_wplastic = 1000;

const unsigned int BUFSIZE = 1024;

int xant=0, yant=0, x_pos, y_pos;
bool moviendo_camara = false, nueva_pos = true;
GLuint seleccionado; bool select_hecha = false;// -1 es que no hay ningún objeto seleccionado
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
void projection_type(){
	if(camara.getParalela())
		glOrtho(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
	
	else{
		//Para ajustar el tamaño de la ventana al de viewport
		Window_width = (0.5*UI_window_width)/500;
		Window_height = (0.5*UI_window_height)/500;
		
		// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
		//  Front_plane>0  Back_plane>PlanoDelantero)
		glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
	}
	
}
void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();
projection_type();

}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{
//posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
camara.setObservador();
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
	luces.aplicar(alpha_luz0, beta_luz0, alpha_luz1, beta_luz1);
	switch(draw_obj){
		case 'c':
		glPushName(0);
			if(!iluminado && !suavizado){
				switch(mode){
					case 't':
						mode = 'a';
						cubo.draw(mode);
						mode = 'p';
						cubo.draw(mode);
						mode = 's';
						cubo.draw(mode);
						mode = 't'; // Para que no se cambia a dibujar solido
						break;
					default:
						cubo.draw(mode);
						break;
				}
			}
			if(iluminado)
				cubo.draw_iluminado();
			if(suavizado)
				cubo.draw_suavizado();
		glPopName();
		break;
		case 't':
		glPushName(1);
		if(!iluminado && !suavizado){
			switch(mode){
					case 't':
						mode = 'a';
						tetraedro.draw(mode);
						mode = 'p';
						tetraedro.draw(mode);
						mode = 's';
						tetraedro.draw(mode);
						mode = 't';
						break;
					default:
						tetraedro.draw(mode);
						break;
				}
			}
			if(iluminado)
				tetraedro.draw_iluminado();
			if(suavizado)
				tetraedro.draw_suavizado();
		glPopName();
		break;
		case 'p':
		glPushName(2);
		switch(mode){
				case 't':
					mode = 'a';
					modelo.draw(mode);
					mode = 'p';
					modelo.draw(mode);
					mode = 's';
					modelo.draw(mode);
					mode = 't';
					break;
				default:
					modelo.draw(mode);
					break;
			}
		glPopName();
		break;
		case 'f':
			if(especiales_rev == 'e'){
				glPushName(3);
				if(!iluminado && !suavizado){
					switch(mode){
							case 't':
								mode = 'a';
								esfera.draw(mode);
								mode = 'p';
								esfera.draw(mode);
								mode = 's';
								esfera.draw(mode);
								mode = 't';
								break;
							default:
								esfera.draw(mode);
								break;
					}
				}
				if(iluminado)
					esfera.draw_iluminado();
				if(suavizado)
					esfera.draw_suavizado();
				glPopName();
			}
			else{
			glPushName(4);
				if(!iluminado && !suavizado){
					switch(mode){
							case 't':
								mode = 'a';
								if(especiales_rev == 'p'){
									glPushMatrix();
									glRotatef(45,0,1,0);
									piramide.draw(mode);
									mode = 'p';
									piramide.draw(mode);
									mode = 's';
									piramide.draw(mode);
									glPopMatrix();
								}
								else{
									figura.draw(mode);
									mode = 'p';
									figura.draw(mode);
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
				glPopName();
				}
				if(iluminado){
					if(especiales_rev == 'p')
						piramide.draw_iluminado();
					else
						figura.draw_iluminado();
				}
				if(suavizado){
					if(especiales_rev == 'p')
						piramide.draw_suavizado();
					else
						figura.draw_suavizado();
				}
			}
			break;
			case 'r':
			glPushName(5);
				switch(mode){
				case 't':
					mode = 'a';
					regulador_watt.draw(mode);
					mode = 'p';
					regulador_watt.draw(mode);
					mode = 's';
					regulador_watt.draw(mode);
					mode = 't';
					break;
				default:
					regulador_watt.draw(mode);
					break;
				}
			glPopName();
			break;
			case 'o':
			glPushName(6);
				if(!iluminado && !suavizado){
					switch(mode){
					case 't':
						mode = 'a';
						tablero.draw(mode);
						mode = 'p';
						tablero.draw(mode);
						mode = 's';
						tablero.draw(mode);
						mode = 't';
						break;
					default:
						tablero.draw(mode);
						break;
					}
				}
				if(iluminado)
					tablero.draw_iluminado();
				if(suavizado)
					tablero.draw_suavizado();
			glPopName();
			break;
			case 'v':
				int names = 0;
				int x_ini = -20;
				int z_ini = -10;
				for(int i=0; i<3; i++){
					for(int j=0; j<5; j++){
						glPushName(names);
						glPushMatrix();
						glTranslatef(x_ini,0,z_ini);
						modelos[names].draw(mode);
						glPopMatrix();
						glPopName();
						x_ini += 10;
						names++;
					}
					x_ini = -20;
					z_ini += 10;
				}
			break;
	}
}

//**************************************************************************
// Funcion para hacer que el regulador de watt se mantenga girando

void Idle() {
	if(draw_obj == 'r') {
		regulador_watt.mover();
		usleep(500);
		glutPostRedisplay();
	}

}

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
UI_window_width = Ancho1;
UI_window_height = Alto1;
change_projection();
glViewport(0,0,UI_window_width,UI_window_height);
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
	switch(Tecla1){
		case 'Q':
			exit(0);
			break;
		case 'q':
			exit(0);
			break;
		case 'p':
			mode = 'p';
			break;
		case 'a':
			mode = 'a';
			break;
		case 's':
			mode = 's';
			break;
		case 'c':
			mode = 'c';
			break;
		case 't':
			mode = 't';
			break;
		case 'k':
			regulador_watt.cambiarVelocidad(0.2);
			break;
		case 'l':
			regulador_watt.cambiarVelocidad(-0.1);
			break;
		case 'n':
			if(draw_obj == 'f' && especiales_rev == 'e'){
				if(esfera.getNormalesCaras())
					esfera.SetNormalesCaras(false);
				else
					esfera.SetNormalesCaras(true);
			}
			else if(draw_obj == 'c'){
				if(cubo.getNormalesCaras())
					cubo.SetNormalesCaras(false);
				else
					cubo.SetNormalesCaras(true);
			}
			else if(draw_obj == 'o'){
				if(tablero.getNormalesCaras())
					tablero.SetNormalesCaras(false);
				else
					tablero.SetNormalesCaras(true);
			}
			else if(draw_obj == 'f' && especiales_rev != 'e' && especiales_rev != 'p'){
				if(figura.getNormalesCaras())
					figura.SetNormalesCaras(false);
				else
					figura.SetNormalesCaras(true);
			}
			break;
		case 'v':
			if(draw_obj == 'f' && especiales_rev == 'e'){
				if(esfera.getNormalesVertices())
					esfera.SetNormalesVertices(false);
				else
					esfera.SetNormalesVertices(true);
			}
			else if(draw_obj == 'c'){
				if(cubo.getNormalesVertices())
					cubo.SetNormalesVertices(false);
				else
					cubo.SetNormalesVertices(true);
			}
			else if(draw_obj == 'o'){
				if(tablero.getNormalesVertices())
					tablero.SetNormalesVertices(false);
				else
					tablero.SetNormalesVertices(true);
			}
			else if(draw_obj == 'f' && especiales_rev != 'e' && especiales_rev != 'p'){
				if(figura.getNormalesVertices())
					figura.SetNormalesVertices(false);
				else
					figura.SetNormalesVertices(true);
			}
			break;
		case 'i':
			iluminado = !iluminado;
			break;
		case 'g':
			suavizado = !suavizado;
			break;
		case 'E':
			alpha_luz0++;
			if(alpha_luz0 > 90) alpha_luz0 = 90;
			break;
		case 'D':
			alpha_luz0--;
			if(alpha_luz0 < -90) alpha_luz0 = -90;
			break;
		case 'e':
			beta_luz0++;
			if(beta_luz0 > 360) beta_luz0 = 360;
			break;
		case 'd':
			beta_luz0--;
			if(beta_luz0 < 0) beta_luz0 = 0;
			break;
		case 'R':
			alpha_luz1++;
			if(alpha_luz1 > 90) alpha_luz1 = 90;
			break;
		case 'F':
			alpha_luz1--;
			if(alpha_luz1 < -90) alpha_luz1 = -90;
			break;
		case 'r':
			beta_luz1++;
			if(beta_luz1 > 360) beta_luz1 = 360;
			break;
		case 'f':
			beta_luz1--;
			if(beta_luz1 < 0) beta_luz1 = 0;
			break;
		case 'x':
			if(draw_obj == 'f' && especiales_rev == 'e')
				esfera.setMaterial(ambiental_bronze, difusa_bronze, especular_bronze, shininess_bronze);
			else if(draw_obj == 'f' && especiales_rev != 'e' && especiales_rev != 'p')
				figura.setMaterial(ambiental_bronze, difusa_bronze, especular_bronze, shininess_bronze);
			break;
		case 'z':
			if(draw_obj == 'f' && especiales_rev == 'e')
				esfera.setMaterial(ambiental_wplastic, difusa_wplastic, especular_wplastic, shininess_wplastic);
			else if(draw_obj == 'f' && especiales_rev != 'e' && especiales_rev != 'p')
				figura.setMaterial(ambiental_wplastic, difusa_wplastic, especular_wplastic, shininess_wplastic);
			break;
		case 'y':
			camara.setParalela();
			change_projection();
			break;
		case '0':
			luces.luzGeneral();
			break;
		case '8':
			luces.turnLight(0);
			break;
		case '9':
			luces.turnLight(1);
			break;
		case '1':
			if(draw_obj == 'p'){
				modelo.CargarPLY("data/armadillo.ply");
			}
			else if(draw_obj == 'f'){
				especiales_rev = 'x';
				figura.GenerarFigura(cilindro, divisiones);
			}
			break;
		case '2':
			if(draw_obj == 'p'){
				modelo.CargarPLY("data/beethoven.ply");
			}
			else if(draw_obj == 'f'){
				especiales_rev = 'x';
				figura.GenerarFigura(vaso, divisiones);
			}
			break;
		case '3':
			if(draw_obj == 'p'){
				modelo.CargarPLY("data/big_dodge.ply");
			}
			else if(draw_obj == 'f'){
				especiales_rev = 'x';
				figura.GenerarFigura(vaso_inv, divisiones);
			}
			break;
		case '4':
			if(draw_obj == 'p'){
				modelo.CargarPLY("data/big_porsche.ply");
			}
			else if(draw_obj == 'f'){
				especiales_rev = 'x';
				figura.GenerarFigura(cono, divisiones);
			}
			break;
		case '5':
			if(draw_obj == 'p'){
				modelo.CargarPLY("data/big_spider.ply");
			}
			else if(draw_obj == 'f'){
				especiales_rev = 'x';
				figura.GenerarFigura(tubo, divisiones);
			}
			break;
		case '6':
			if(draw_obj == 'f'){
				especiales_rev = 'e';
				esfera.Redimensionar(divisiones);
				esfera.NormalizarCaras();
				esfera.NormalizarVertices();
			}
			break;
		case '7':
			if(draw_obj == 'f'){
				especiales_rev = 'p';
			}
			break;
		case '-':
			if(draw_obj == 'f' && especiales_rev != 'p'){
				if(divisiones > 3)
					divisiones--;
				if(especiales_rev == 'e'){
					esfera.Redimensionar(divisiones);
				}
				figura.Modificar_divisiones(divisiones);
			}
			if(draw_obj == 'o'){
				tablero.setDivisiones(tablero.getDivisiones()-1);
				tablero.NormalizarCaras();
				tablero.NormalizarVertices();
			}
			break;
		case '+':
			if(draw_obj == 'f' && especiales_rev != 'p'){
				divisiones++;
				if(especiales_rev == 'e'){
					esfera.Redimensionar(divisiones);
				}
				figura.Modificar_divisiones(divisiones);
			}
			if(draw_obj == 'o'){
				tablero.setDivisiones(tablero.getDivisiones()+1);
				tablero.NormalizarCaras();
				tablero.NormalizarVertices();
			}
			break;
	}
	glutPostRedisplay();

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
	case GLUT_KEY_F1: draw_obj = 't'; select_hecha = false; break;
	case GLUT_KEY_F2: draw_obj = 'c'; select_hecha = false; break;
	case GLUT_KEY_F3: draw_obj = 'p'; select_hecha = false; break;
	case GLUT_KEY_F4: draw_obj = 'f'; select_hecha = false; break;
	case GLUT_KEY_F5: draw_obj = 'r'; select_hecha = false; break;
	case GLUT_KEY_F6: draw_obj = 'o'; select_hecha = false; break;
	case GLUT_KEY_F7: draw_obj = 'v'; select_hecha = false; break;
	}
glutPostRedisplay();
}

//***************************************************************************
// Funcion para pinchar con el raton
//***************************************************************************
void procesarHits(GLint hits, GLuint buffer[]){
	unsigned int i, j;
	GLuint names, *ptr, minZ, *ptrNames, numberOfNames;
	printf("Primitivas intersectadas = %d\n", hits); ptr = (GLuint *) buffer;
	minZ = 0xffffffff;
	for(i=0; i<hits; i++){
		names = *ptr; ptr++;
		if(*ptr < minZ){
			numberOfNames = names;
			minZ = *ptr; ptrNames = ptr+2;
		}
		ptr += names+2;
	}
	printf("Los nombres de la primitiva mas cercana son (%d): ", numberOfNames); ptr = ptrNames;
	for(j=0; j<numberOfNames; j++, ptr++){
		printf("%d", *ptr);
		
	}
	printf("\n");
	ptr--;
	
	if(!select_hecha){
		select_hecha = true;
		seleccionado = *ptr;
		printf("Seleccionado = %d\n", seleccionado);
		if(draw_obj == 'v')
			modelos[seleccionado].setSeleccionado(true);
	}
	else{
		if(draw_obj == 'v'){
			modelos[seleccionado].setSeleccionado(false);
			seleccionado = *ptr;
			printf("Seleccionado = %d\n", seleccionado);
			modelos[seleccionado].setSeleccionado(true);
		}
	}
	glutPostRedisplay();
}

void pick(int x, int y){
	GLuint selectBuf[BUFSIZE];
	GLint hits, viewport[4];
	glGetIntegerv (GL_VIEWPORT, viewport);
	glSelectBuffer (BUFSIZE, selectBuf);
	glRenderMode (GL_SELECT);
	glInitNames();
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPickMatrix (x, viewport[3]-y, 5.0, 5.0, viewport);
	glFrustum(-Window_width,Window_width,-Window_height,Window_height, Front_plane, Back_plane);
	change_observer();
	draw_objects();
	hits = glRenderMode (GL_RENDER);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-Window_width,Window_width,-Window_height,Window_height, Front_plane, Back_plane);
	if(hits != 0)
		procesarHits(hits,selectBuf);
	else{
		if(select_hecha){
			if(draw_obj == 'v')
				modelos[seleccionado].setSeleccionado(false);
			select_hecha = false;
		}
	}
	glutPostRedisplay();
}

void ratonMovido(int x, int y){
	if(moviendo_camara){
		if(nueva_pos){
			x_pos = x;
			y_pos = y;
			nueva_pos = false;
		}
		camara.girar((x+xant-x_pos)*0.005, (y-yant-y_pos)*0.005);
		xant = x+xant-x_pos;
		yant = y+yant-y_pos;
		glutPostRedisplay();
	}
}

void clickRaton(int boton, int estado, int x, int y){
	if(boton == GLUT_LEFT_BUTTON){
		if(estado == GLUT_DOWN){
			moviendo_camara = false; 
			pick(x,y);
		}
	}
	else if(boton == GLUT_RIGHT_BUTTON){
		if(estado == GLUT_DOWN){
			moviendo_camara = true;
		}
		else
			moviendo_camara = false;
			nueva_pos = true;
	}
	else if(boton == 3){
		if(estado == GLUT_DOWN)
			if(camara.getParalela()){
				Window_width*=1.05;
				Window_height*=1.05;
				change_projection();
			}
			else
				camara.zoom(1);
		glutPostRedisplay();
	}
	else if(boton == 4){
		if(estado == GLUT_DOWN)
			if(camara.getParalela()){
				Window_width*=0.95;
				Window_height*=0.95;
				change_projection();
			}
			else
				camara.zoom(-1);
		glutPostRedisplay();
	}
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
/*Observer_distance=2*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;*/

camara.setDistance(Front_plane);

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
glutCreateWindow("Práctica 5");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw_scene);
// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "tecla_normal" al evento correspondiente
glutKeyboardFunc(normal_keys);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_keys);

glutIdleFunc(Idle);

glutMouseFunc(clickRaton);
glutMotionFunc(ratonMovido);

// funcion de inicialización
initialize();

modelo.CargarPLY("data/beethoven.ply");
modelos.resize(15);
for(int i=0; i<modelos.size(); i++){
	modelos[i] = modelo;
}

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
figura.GenerarFigura(tubo, divisiones);

//Calculamos normales
cubo.NormalizarCaras();
cubo.NormalizarVertices();

tetraedro.NormalizarCaras();
tetraedro.NormalizarVertices();

tablero.NormalizarCaras();
tablero.NormalizarVertices();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
