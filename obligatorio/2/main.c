#include "../framework/canvas.h"
#include "../framework/mm.h"
#include "../Obj/Obj.h"
#include "GL/gl.h"

/**
 * 2. Determinación de superficies ocultas por medio de Z-Buffer y optimización por Backface culling.
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
					else if (event.key.keysym.sym == SDLK_m)
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
				case SDL_QUIT :
					done = 1;
					break;
				case SDL_KEYUP:
					key_pressed[event.key.keysym.sym] = 0;

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