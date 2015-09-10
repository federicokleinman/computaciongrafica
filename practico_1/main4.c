#include "framework/canvas.h"
#include "framework/mm.h"
#include "GL/gl.h"

/**
 *  4. Dibuje el mismo triángulo, pero reducido a la mitad de su tamaño.
 * Nota: No modifique las coordenadas de los vértices, utilice transformaciones.
 */

int main(int argc, char* argv[])
{
	// Crear una ventana de 500x500 pixels:
	int cw = 900;
	int ch = 900;

	cg_init(cw, ch, NULL);

	printf("GL Version: %s\n", glGetString(GL_VERSION));

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glViewport(0,0,cw, ch);
	glFrustum(-1,1,-1,1,1,1000);

	float ang = 0.0f;
	float verts[12] = {-1.0f, -1.0f, -2.0f,
					   1.0f, -1.0f, -2.0f,
					   0.0f,  1.0f, -2.0f,
					   2.0f,  1.0f, -2.0f};

	float colors[12] = {1.0f, 0.0f, 0.0f,
						0.0f, 1.0f, 0.0f,
						0.0f, 0.0f, 1.0f,
						1.0f, 1.0f, 0.0f};

	unsigned int indexs[6] = {0, 1, 2, 1, 2, 3};

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

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -2.0f);
		glRotatef(ang, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, 2.0f);
		ang += 0.1f;

		glClear(GL_COLOR_BUFFER_BIT);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, verts);
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(3, GL_FLOAT, 0, colors);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indexs);
		glDisableClientState(GL_VERTEX_ARRAY);  glDisableClientState(GL_COLOR_ARRAY);

		cg_repaint();
	}
	// Liberar recursos:
	cg_close();

	// Ejemplo del modulo de Manejo de Memoria (MM):
	int* pint = (int *)cg_malloc(10*sizeof(int));
	printf("pint is a pointer: %p\n", pint);
	cg_free(pint); // olvidarse de liberar este objeto produce un mensaje

	return 0;
}