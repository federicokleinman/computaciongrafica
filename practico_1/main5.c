#include "framework/canvas.h"
#include "framework/mm.h"
#include "GL/gl.h"
#include "Obj.h"

/**
 * Dibuje el modelo definido por el archivo knight.obj 1 disponible en webasignatura. El
 * formato del archivo OBJ se encuentra definido en el anexo I de este documento. Cada
 * triángulo del modelo debe ser dibujado usando un tono de gris randómico en sus vértices.
 * Nota: Para parsear el archivo obj, puede utilizar las funciones fgets (definida en stdio.h),
 * strcmp, strtok (definidas en string.h), atof y atoi (definidas en stdlib.h).
 */
int main(int argc, char* argv[])
{
// Crear una ventana de 500x500 pixels:
	int cw = 900;
	int ch = 900;

	cg_init(cw, ch, NULL);

#ifdef WIN32
    freopen( "CON", "w", stdout );
    freopen( "CON", "w", stderr );
#endif

	printf("GL Version: %s\n", glGetString(GL_VERSION));
	// Actualizar la pantalla:
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glViewport(0,0,cw, ch);
	glFrustum(-1,1,-1,1,1,1000);

	//Habilito la iluminación del pipeline estático de OpenGL.
	glEnable(GL_LIGHTING);

	//Creo un Vec4 para representar el color (RGBA) y la Intensidad de la luz.
	//P.e.: (1,1,1,1) = Luz Blanca intensa, (0.5,0.5,0.5,1) = Luz blanca tenue, (0.5,0,0,1) = Luz roja tenue.
	float l0[] = {1.0f,1.0f,1.0f,1.0f};
	//Creo un Vec4 para representar el color (RGBA) y la intensidad de la iluminación ambiente de la luz
	float la[] = {0.10f,0.10f,0.10f,1.0f};
	//Creo un Vec4 para representar la posición de la luz. El cuarto elemento representa el tipo de luz: 1=puntual, 0=direccional
	float l0p[]= {1.0f,1.0f,1.0f,1.0f};
	//Creo un Vec4 para representar el color (RGBA) y la intensidad especular de la luz
	float ls[] = {1.0f,1.0f,1.0f,1.0f};
	//Cargo la intesidad ambiente de la Luz Nro 0 del pipline estático.
	glLightfv(GL_LIGHT0, GL_AMBIENT, la);
	//Cargo la intesidad difusa de la Luz Nro 0 del pipline estático.
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0);
	//Cargo la posición de la Luz Nro 0 del pipline estático.
	glLightfv(GL_LIGHT0, GL_POSITION, l0p);
	//Cargo la intesidad especular de la Luz Nro 0 del pipline estático.
	glLightfv(GL_LIGHT0, GL_SPECULAR, ls);
	//Prendo la Luz nro 0 del pipline estático. Hay 8 luces, representadas por las constantes GL_LIGHT0 a GL_LIGHT7
	//Por defecto está todas apagadas al inicio.
	glEnable(GL_LIGHT0);

	//Creo un Vec4 para representar el color difuso(RGBA) del material del objeto a dibujar.
	float cyan[] = {1.0f, 0.0f, 1.0f, 1.f};
	//Cargo el color difuso del la cara de adelante del objeto a dibujar.
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);
	//Cargo el color especular del la cara de adelante del objeto a dibujar.
	glMaterialfv(GL_FRONT, GL_SPECULAR, ls);
	//Cargo el coeficiente especular de la cara de adelante del objeto a dibujar.
	glMateriali(GL_FRONT, GL_SHININESS, 32);

	float ang = 0.0f;
	float pitch = 0.0f;
	float ang_vel = 1.0f;

	Obj* knight = obj_load("Models/knight.obj");

	printf("num of faces %d\n", knight->numfaces);    // delete
	printf("num of vertices %d\n", knight->numverts);  // delete


	char done = 0;
	char wireframe = 0;
	char bfc = 0;
	glEnable(GL_DEPTH_TEST);
	char zbuff = 1;
	unsigned char key_pressed[1024];
	memset(key_pressed, 0, 1024);

	while (!done)
	{

		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_KEYDOWN:
					key_pressed[event.key.keysym.sym] = 1;
					if (event.key.keysym.sym == SDLK_z)
					{
						zbuff = !zbuff;
						if(zbuff)
							glEnable(GL_DEPTH_TEST);
						else
							glDisable(GL_DEPTH_TEST);
						break;
					}
					else if (event.key.keysym.sym == SDLK_m)
					{
						wireframe = !wireframe;
						if(wireframe)
							glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
						else
							glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
						break;
					}
					else if (event.key.keysym.sym == SDLK_b)
					{
						bfc = !bfc;
						if(bfc)
						{
							glEnable(GL_CULL_FACE);
							glCullFace(GL_BACK);
							glFrontFace(GL_CW);
						}
						else
							glDisable(GL_CULL_FACE);
						break;
					}
					else if (event.key.keysym.sym != SDLK_ESCAPE)
						break;
				case SDL_QUIT : done = 1;break;
				case SDL_KEYUP: key_pressed[event.key.keysym.sym] = 0;

			}
		}

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -50.0f);
		glRotatef(pitch, 1.0f, 0.0f, 0.0f);
		glRotatef(ang, 0.0f, 1.0f, 0.0f);

		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

		if(key_pressed[SDLK_RIGHT]) ang += ang_vel;
		if(key_pressed[SDLK_LEFT]) ang -= ang_vel;
		if(key_pressed[SDLK_UP]) pitch += ang_vel;
		if(key_pressed[SDLK_DOWN]) pitch -= ang_vel;

		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		obj_render(knight);

		cg_repaint();
	}
	obj_free(knight);
	// Liberar recursos:
	cg_close();

	// Ejemplo del modulo de Manejo de Memoria (MM):
	int* pint = (int *)cg_malloc(10*sizeof(int));
	printf("pint is a pointer: %p\n", pint);
	cg_free(pint); // olvidarse de liberar este objeto produce un mensaje


	return 0;
}