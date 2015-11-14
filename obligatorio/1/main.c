#include "../framework/canvas.h"
#include "../framework/mm.h"
#include "Obj.h"
#include "GL/gl.h"

/**
 * 1. Rasterización de modelos OBJ, dibujando triángulos sólidos o una “malla de alambre”.
 */
int main(int argc, char* argv[])
{
	// Crear una ventana de 750x750 pixels.
	int cw = 750;
	int ch = 750;

	cg_init(cw, ch, NULL);

	// Actualizar la pantalla:
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glViewport(0,0,cw, ch);
	glFrustum(-1,1,-1,1,1,1000);

	Obj* obj = obj_load("../Models/knight.obj");

	float ang = 0.0f;
	float pitch = 0.0f;
	float ang_vel = 1.0f;

	char done = 0;
	char wireframe = 0;
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
					if (event.key.keysym.sym == SDLK_m)
					{
						wireframe = !wireframe;
						if(wireframe)
							glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
						else
							glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
		obj_render(obj);
		cg_repaint();
	}

	// Liberar recursos:
	obj_free(obj);
	cg_close();

	return 0;
}