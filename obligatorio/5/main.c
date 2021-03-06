#include "../framework/canvas.h"
#include "../framework/mm.h"
#include "Obj.h"
#include "shader.h"
#include <GL/gl.h>
#include <SDL/SDL_image.h>

int main(int argc, char* argv[])
{
	int cw = 750;
	int ch = 750;

	cg_init(cw, ch, NULL);

    glClearColor(0,0,1,1);
    // Actualizar la pantalla:
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glViewport(0,0,cw, ch);
    glFrustum(-1,1,-1,1,1,1000);

    glEnable(GL_LIGHTING);

    // glEnable(GL_NORMALIZE);
    float l0[] = {1.0f,1.0f,1.0f,1.0f};
    float la[] = {0.10f,0.10f,0.10f,1.0f};
    float l0p[]= {1.0f,1.0f,1.0f,1.0f};
    float ls[] = {1.0f,1.0f,1.0f,1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, la);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, l0);
    glLightfv(GL_LIGHT0, GL_POSITION, l0p);
    glLightfv(GL_LIGHT0, GL_SPECULAR, ls);
    glEnable(GL_LIGHT0);

    float cyan[] = {1.0f, 1.0f, 1.0f, 1.f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ls);
    glMateriali(GL_FRONT, GL_SHININESS, 16);

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

    char use_shader = 0;
    char specular = 0;
    Shader gouraud = shader_new("shaders/gouraud_vp.glsl", "shaders/gouraud_fp.glsl");
    GLint uniform_especular = shader_get_unif_loc(gouraud, "especular");
    GLint uniform_tex = shader_get_unif_loc(gouraud, "tex");

    Obj* objPtr ;
    int example = atoi(argv[1]);

    if (example==1 || example==3)
        objPtr = obj_load("../Models/knight_texturas.obj");
    else if (example==2)
        objPtr = obj_load("../Models/box_texturas.obj");

    //Cargo la imagen de disco usando SDL_image
    SDL_Surface* surface; // = IMG_Load("../Models/knight.png");

    if (example==1 )
        surface = IMG_Load("../Models/knight.png");
    else if (example==2)
        surface = IMG_Load("../Models/box.jpg");
    else if (example==3)
        surface = IMG_Load("../Models/knight_good.png");


//    Obj* objPtr = obj_load("../Models/knight_texturas.obj");
//    Obj* objPtr = obj_load("../Models/box_texturas.obj");

    //Cargo la imagen de disco usando SDL_image
//    SDL_Surface* surface = IMG_Load("../Models/knight.png");
//    SDL_Surface* surface = IMG_Load("../Models/knight_good.png");
//    SDL_Surface* surface = IMG_Load("../Models/box.jpg");

    if (surface==NULL) { //Si falla la carga de la imagen, despliego el mensaje de error correspondiente y termino el programa.
        printf("Error: \"%s\"\n", SDL_GetError());
        return 1;
    }

    GLuint texture;
    //Creo un espacio para alojar una textura en memoria de video
    glGenTextures(1,&texture);
    //Activo la textura nro 0
    glActiveTexture(GL_TEXTURE0);
    //Habilito la carga para la textura recien creada
    glBindTexture(GL_TEXTURE_2D,texture);

    //Cargo los datos de la imagen en la textura.
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 surface->w,
                 surface->h,
                 0,
                 GL_RGB,GL_UNSIGNED_BYTE,
                 surface->pixels);
    //Luego de copiada la imagen a memoria de video, puedo liberarla sin problemas
    SDL_FreeSurface(surface);

    //Seteo el filtro a usar cuando se mapea la textura a una superficie mas chica (GL_LINEAR = filtro bilineal)
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR);
    //Seteo el filtro a usar cuando se mapea la textura a una superficie mas grande (GL_LINEAR = filtro bilineal)
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER,
                    GL_LINEAR);

    //Seteo el comportamiento cuando encuentro coordenadas de textura fuera del rango [0,1]
    //GL_REPEAT es el comportamiento por defecto.
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S,
                    GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T,
                    GL_REPEAT);

	while (!done)
	{

		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_KEYDOWN:
                    key_pressed[event.key.keysym.sym] = 1;
                    if (event.key.keysym.sym == SDLK_p)
				    {
				        use_shader = !use_shader;
				        break;
				    }
				    else if (event.key.keysym.sym == SDLK_s)
				    {
				        specular = !specular;
				        break;
				    }
                    else if (event.key.keysym.sym == SDLK_z)
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

        if (example==1 || example==3)
            glTranslatef(0.0f, 0.0f, -50.0f);
        else if (example==2)
            glTranslatef(0.0f, 0.0f, -2.0f);

//        glTranslatef(0.0f, 0.0f, -50.0f);
//        glTranslatef(0.0f, 0.0f, -2.0f);

        glRotatef(pitch, 1.0f, 0.0f, 0.0f);
        glRotatef(ang, 0.0f, 1.0f, 0.0f);

        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

        if(key_pressed[SDLK_RIGHT]) ang += ang_vel;
        if(key_pressed[SDLK_LEFT]) ang -= ang_vel;
        if(key_pressed[SDLK_UP]) pitch += ang_vel;
        if(key_pressed[SDLK_DOWN]) pitch -= ang_vel;

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        //Informo a OpenGL que para todas las operaciones a continuaci�n utilice las texturas 2D cargadas
        glEnable(GL_TEXTURE_2D);

        if(use_shader)
        {
            shader_use(gouraud);
            glUniform1i(uniform_especular, specular);
            //Le digo al shader que el sampler2D de nombre "tex" se corresponde con GL_TEXTURE0
            //que es donde cargu� mi textura.
            glUniform1i(uniform_tex, 0);
            //Luego asocio la textura con el id "texture"
            glBindTexture(GL_TEXTURE_2D,texture);
            obj_render2(objPtr);
            shader_stop(gouraud);
        }
        else
        {
            glBindTexture(GL_TEXTURE_2D,texture);
            obj_render2(objPtr);
        }

        cg_repaint();
	} // while

    // Liberar recursos:
    obj_free(objPtr);
    shader_free(gouraud);
    glDeleteTextures(1,&texture);
	cg_close();

	return 0;
}
