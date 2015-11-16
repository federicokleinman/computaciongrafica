#include "framework/canvas.h"
#include "framework/mm.h"
#include "cg_parser.h"
#include "Vec3.h"
#include <math.h>

enum bool {false, true};
typedef enum bool bool;

typedef struct {
    Vec3 origin; // punto en el espacio
    Vec3 dir; // normalizada
} Ray;

typedef struct {
    CG_Sphere* e;
    float lambda;
} Inter;

typedef struct {
    int points;
    float t0;
    float t1;
} InterSphere;

#define clamp(value,min,max) ((value <= min) ? min : ((value >= max) ? max : value))
#define EPSILON 0.01f
#define INF 100000.0f

#define SIZE 300

// Crear una ventana de 600x600 pixels:
int cw = SIZE;
int ch = SIZE;

Color mult_color(float coef, Color c) {
    int r = (coef * c.r);
    int g = (coef * c.g);
    int b = (coef * c.b);

    Color cg_color;
    cg_color.r = clamp(r, 0, 255);
    cg_color.g = clamp(g, 0, 255);
    cg_color.b = clamp(b, 0, 255);
    return cg_color;
}

Color add_color(Color a, Color b) {
    int _r = (int) a.r + (int) b.r;
    int _g = (int) a.g + (int) b.g;
    int _b = (int) a.b + (int) b.b;

    Color cg_color;
    cg_color.r = clamp(_r, 0, 255);
    cg_color.g = clamp(_g, 0, 255);
    cg_color.b = clamp(_b, 0, 255);
    return cg_color;
}

InterSphere rayo_esfera(const Ray* ray, const CG_Sphere* e) {
    InterSphere res;
    res.points = 0;

    Vec3 L = Vec3_diff(e->pos, ray->origin);
    float tca = vec3_dot(&L, &ray->dir);

    if (tca >= 0) {
        float d2 = vec3_dot(&L, &L) - tca * tca;
        if (d2 > e->radius * e->radius) {
            return res;
        }

        float thc = sqrt(e->radius * e->radius - d2);
        res.t0 = tca - thc;
        res.t1 = tca + thc;

        res.points = (res.t0 == res.t1) ? 1 : 2;
    }

    return res;
}

Inter intersectar_rayo(const Ray* ray, float min, float max) {
    Inter res;
    res.e = NULL;
    res.lambda = max;

    for (CG_Sphere* pEsfera = escena.pSphere; pEsfera != NULL; pEsfera = pEsfera->next) {
        InterSphere inter = rayo_esfera(ray, pEsfera);

        if (inter.points > 0) {
            if (min <= inter.t0 && inter.t0 <= res.lambda) {
                res.lambda = inter.t0;
                res.e = pEsfera;
            }

            if (min <= inter.t1 && inter.t1 <= res.lambda) {
                res.lambda = inter.t1;
                res.e = pEsfera;
            }
        }
    }

    return res;
}

Color trazar_rayo(const Ray* rayoVista, float min, float max, int max_rec) {
	Color res;
	res.r = 0;
	res.g = 0;
	res.b = 0;

	Inter inter = intersectar_rayo(rayoVista, min, max);
	if (inter.e != NULL) {
		// Luz ambiente
		res = mult_color(escena.intAmbient, inter.e->material.cd);

		// Puntos y Vectores
		Ray lRay;
		lRay.origin = vec3_add(rayoVista->origin, vec3_mult(rayoVista->dir, inter.lambda));
		Vec3 N = Vec3_diff(lRay.origin, inter.e->pos);
		vec3_normalize(&N);
		Vec3 V = vec3_negate(rayoVista->dir);
		vec3_normalize(&V);

		// Luces
		for (CG_Light* pLight = escena.pLight; pLight != NULL; pLight = pLight->next) {
			lRay.dir = (pLight->type == CG_POINT) ? Vec3_diff(pLight->pos, lRay.origin) : vec3_negate(pLight->pos);
			vec3_normalize(&lRay.dir);

			Inter i_sombra = intersectar_rayo(&lRay, EPSILON, INF);
			if (i_sombra.e == NULL) {
				// Difuso
				float diffuse = pLight->intens * vec3_dot(&N, &lRay.dir);
				Color diffuseColor = mult_color(diffuse, inter.e->material.cd);
				res = add_color(res, diffuseColor);

				// Especular
				if (inter.e->material.coef_espec > 0) {
					Vec3 R = Vec3_diff(vec3_mult(N, 2.0f * vec3_dot(&N, &lRay.dir)), lRay.dir);
					vec3_normalize(&R);
					float spec = pLight->intens * pow(vec3_dot(&V, &R), inter.e->material.coef_espec);
					Color specularColor = mult_color(spec, inter.e->material.cs);
					res = add_color(res, specularColor);
				}
			}
		}

		// Reflejos
		if (max_rec > 0) {
			Vec3 R = Vec3_diff(vec3_mult(N, 2.0f * vec3_dot(&N, &V)), V);
			lRay.dir = Vec3_diff(R, lRay.origin);
			vec3_normalize(&lRay.dir);
			Color cr = trazar_rayo(&lRay, EPSILON, INF, max_rec - 1);
			res = add_color(mult_color(1.0f - inter.e->material.coef_refl, res), mult_color(inter.e->material.coef_refl, cr));
		}
	}

	return res;
}


void putpixelLoop() {
	Ray ray;
	ray.origin = escena.cam;

	Vec3 V;
	V.z = escena.dist;
	for (int x = -cw / 2; x < cw / 2; x++) {
		for (int y = -ch / 2; y < ch / 2; y++) {
			V.x = x * escena.vw / cw;
			V.y = y * escena.vh / ch;

			ray.dir = Vec3_diff(V, ray.origin);
			float distance = vec3_norm(&ray.dir);
			vec3_normalize(&ray.dir);
			Color c = trazar_rayo(&ray, distance, INF, 3);
			cg_putpixel(x, y, c);
		}
	}
}

int main(int argc, char* argv[])
{
	// Crear una ventana de 500x500 pixels:
//	int cw = 500;
//	int ch = 500;
	cg_init(cw, ch, NULL);
	
#ifdef WIN32
    freopen( "CON", "w", stdout );
	freopen( "CON", "w", stderr );
#endif

	bool b = true;
	b = 1 && 0;
	float r = rand() / (float)RAND_MAX;
	if(!b)
		printf("bool ok!!! %f\n",r);
	// Dibujar un pequeno "+" en el centro de la ventana:
//	Color color = cg_color_new(0xff, 0x0, 0x0);
	//int x, y;
//	for (int x = -1; x <= 1; x++)
//	{
//		for (int y = -1; y <= 1; y++)
//		{
//			if (x == 0 || y == 0)
//			{
//				cg_putpixel(x, y, color);
//			}
//		}
//	}
	cg_parse_conf("Escenas_Raytracer/escena1.txt");
	// Actualizar la pantalla:
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

		cg_clear();

        putpixelLoop();

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

