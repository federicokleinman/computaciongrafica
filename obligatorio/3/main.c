#include "../framework/canvas.h"
#include "../framework/mm.h"
#include "../Obj/Obj.h"
#include "../Vec/vec4.h"
#include "GL/gl.h"


/**
 * gLenum Enumerado:  GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7
 * la Vec4 para representar el color (RGBA) y la intensidad de la iluminación ambiente de la luz
 * l Vec4 para representar el color (RGBA) y la Intensidad de la luz.
 * lp Vec4 para representar la posición de la luz. El cuarto elemento representa el tipo de luz: 1=puntual, 0=direccional
 * ls Vec4 para representar el color (RGBA) y la intensidad especular de la luz
 */
void loadLight(GLenum gLenum, Vec4 * la, Vec4 *ld, Vec4 * lp, Vec4 * ls) {

    GLfloat glLa[] = {la->x,la->w,la->y,la->z};
    GLfloat glLd[] = {ld->x,ld->w,ld->y,ld->z};
    GLfloat glLp[] = {lp->x,lp->w,lp->y,lp->z};
    GLfloat glLs[] = {ls->x,ls->w,ls->y,ls->z};

    //Cargo la intesidad ambiente de la Luz Nro 0 del pipline estático.
    glLightfv(gLenum, GL_AMBIENT, glLa);

    //Cargo la intesidad difusa de la Luz Nro 0 del pipline estático.
    glLightfv(gLenum, GL_DIFFUSE, glLd);

    //Cargo la posición de la Luz Nro 0 del pipline estático.
    glLightfv(gLenum, GL_POSITION, glLp);

    //Cargo la intesidad especular de la Luz Nro 0 del pipline estático.
    glLightfv(gLenum, GL_SPECULAR, glLs);
}

/**
 * Soporte para al menos 8 luces, puntuales y/o direccionales.
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

	//Habilito la iluminación del pipeline estático de OpenGL.
	glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    // GL_LIGHT0
    Vec4 *vec4La0 = vec4Contructor(0.10f, 0.10f, 0.10f, 1.0f);
    Vec4 *vec4Ld0 = vec4Contructor(1.0f, 1.0f, 1.0f, 1.0f);
    Vec4 *vec4Ls0 = vec4Contructor(1.0f, 1.0f, 1.0f, 1.0f);
    Vec4 *vec4Lp0 = vec4Contructor(1.0f, 1.0f, 1.0f, 0.0f);
    loadLight(GL_LIGHT0, vec4La0, vec4Ld0, vec4Lp0, vec4Ls0);

    // GL_LIGHT1
    Vec4 *vec4La1 = vec4Contructor(0.5f,0.5f,0.5f,1.0f);
    Vec4 *vec4Ld1 = vec4Contructor(0.5f, 0.3f, 0.2f, 1.0f);
    Vec4 *vec4Ls1 = vec4Contructor(1.0f,1.0f,1.0f,1.0f);
    Vec4 *vec4Lp1 = vec4Contructor(1.0f, 1.0f, 1.0f, 0.0f);
    loadLight(GL_LIGHT1, vec4La1, vec4Ld1, vec4Lp1, vec4Ls1);
//    GLfloat spot_direction[] = { -1.0, -1.0, 0.0 };
//    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
//    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
//    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);
//    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
//    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
//    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);

    // GL_LIGHT2
    Vec4 *vec4La2 = vec4Contructor( 0.2f, 0.2f, 0.2f, 1.0f);
    Vec4 *vec4Ld2 = vec4Contructor(0.8f, 0.8f, 0.8, 1.0f );
    Vec4 *vec4Lp2 = vec4Contructor(-1.5f, 1.0f, -4.0f, 1.0f );
    Vec4 *vec4Ls2 = vec4Contructor(0.5f, 0.5f, 0.5f, 1.0f );
    loadLight(GL_LIGHT2, vec4La2, vec4Ld2, vec4Lp2, vec4Ls2);


    // TODO, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7

    Obj* obj = obj_load("../Models/knight.obj");

	float ang = 0.0f;
	float pitch = 0.0f;
	float ang_vel = 1.0f;

	char done = 0;
	char wireframe = 0;
	char bfc = 0;
	char zbuff = 1;
    char enableLight0 = 0;
    char enableLight1 = 0;
    char enableLight2 = 0;
    char enableLight3 = 0;
    char enableLight4 = 0;
    char enableLight5 = 0;
    char enableLight6 = 0;
    char enableLight7 = 0;
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
                    else if (event.key.keysym.sym == SDLK_0)
                    {
                        enableLight0 = !enableLight0;
                        if(enableLight0) glEnable(GL_LIGHT0);
                        else glDisable(GL_LIGHT0);
                        break;
                    }
                    else if (event.key.keysym.sym == SDLK_1)
                    {
                        enableLight1 = !enableLight1;
                        if(enableLight1) glEnable(GL_LIGHT1);
                        else glDisable(GL_LIGHT1);
                        break;
                    }
                    else if (event.key.keysym.sym == SDLK_2)
                    {
                        enableLight2 = !enableLight2;
                        if(enableLight2) glEnable(GL_LIGHT2);
                        else glDisable(GL_LIGHT2);
                        break;
                    }
                    else if (event.key.keysym.sym == SDLK_3)
                    {
                        enableLight3 = !enableLight3;
                        if(enableLight3) glEnable(GL_LIGHT3);
                        else glDisable(GL_LIGHT3);
                        break;
                    }
                    else if (event.key.keysym.sym == SDLK_4)
                    {
                        enableLight4 = !enableLight4;
                        if(enableLight4) glEnable(GL_LIGHT4);
                        else glDisable(GL_LIGHT4);
                        break;
                    }
                    else if (event.key.keysym.sym == SDLK_5)
                    {
                        enableLight5 = !enableLight5;
                        if(enableLight5) glEnable(GL_LIGHT5);
                        else glDisable(GL_LIGHT5);
                        break;
                    }
                    else if (event.key.keysym.sym == SDLK_6)
                    {
                        enableLight6 = !enableLight6;
                        if(enableLight6) glEnable(GL_LIGHT6);
                        else glDisable(GL_LIGHT6);
                        break;
                    }
                    else if (event.key.keysym.sym == SDLK_7)
                    {
                        enableLight7 = !enableLight7;
                        if(enableLight7) glEnable(GL_LIGHT7);
                        else glDisable(GL_LIGHT7);
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

