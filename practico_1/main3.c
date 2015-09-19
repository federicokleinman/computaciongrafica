#include "framework/canvas.h"
#include "framework/mm.h"
#include "GL/gl.h"

/**
 *  Dibuje el triángulo formado por los vértices [(-1,-1,-2), (1,-1,-2), (0,1,-2)].
 */
int main(int argc, char* argv[])
{
// Crear una ventana de 500x500 pixels:

	int cw = 500;
	int ch = 500;

	cg_init(cw, ch, NULL);

	// Utilizando la función glGetString, imprima por consola el número de versión de OpenGL que utiliza su sistema.
	printf("GL Version: %s\n", glGetString(GL_VERSION));

	// specifies the red, green, blue, and alpha values used by glClear to clear the color buffers.
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	// Actualizar la pantalla:
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glViewport(0,0,cw, ch);
	glFrustum(-1,1,-1,1,1,1000);

	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10.0f);

	glBegin(GL_TRIANGLES);
		glColor3f(0.3f, 0.8f, 0.1f);
		glVertex3f(0.5f, 2.0f, -2.0f);

		glColor3f(0.3f, 0.1f, 0.9f);
		glVertex3f(0.0f,1.0f, -2.0f);

		glColor3f(0.5f, 0.2f, 0.2f);
		glVertex3f(-2.0f, 1.0f, -2.0f);
	glEnd();


	cg_repaint();

	int done = 0;

	while (!done)
	{
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_KEYDOWN:
					if (event.key.keysym.sym != SDLK_ESCAPE)
						break;
				case SDL_QUIT : done = 1;
			}
		}

		cg_repaint();
	}
	// Liberar recursos:
	cg_close();

	return 0;
}



