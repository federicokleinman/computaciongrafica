#include "canvas.h"
#include "mm.h"
#include <stdlib.h>

SDL_Surface* pSurface = NULL;
int surface_locked = 0;

void cg_init(int w, int h, char* title)
{
	assert (SDL_Init(SDL_INIT_VIDEO) == 0);
	pSurface = SDL_SetVideoMode(w, h, 0, SDL_HWSURFACE|SDL_DOUBLEBUF);
	assert (pSurface != NULL);

	if (title)
	{
		SDL_WM_SetCaption(title, NULL);
	}
	else
	{
		SDL_WM_SetCaption("CG Framework v2.2", NULL);
	}

	atexit(cg_memcheck);
}

void cg_begin_frame()
{
	if (surface_locked)
		return;
	
	if (SDL_MUSTLOCK(pSurface))
		SDL_LockSurface(pSurface);
	
	surface_locked = 1;
}

void cg_end_frame()
{
	if (!surface_locked)
		return;
	
	if (SDL_MUSTLOCK(pSurface))
		SDL_UnlockSurface(pSurface);
	
	surface_locked = 0;
}

void cg_putpixel(int x, int y, Color c)
{
	assert (pSurface != NULL);

	int newx = x + pSurface->w/2;
	int newy = -y + pSurface->h/2-1;

	assert (newx >= 0 && newx < pSurface->w && 
		newy >= 0 && newy < pSurface->h);
	
	int bpp = pSurface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)pSurface->pixels + newy * pSurface->pitch + newx * bpp;
	
	int pixel = SDL_MapRGB(pSurface->format, c.r, c.g, c.b);

	if (!surface_locked && SDL_MUSTLOCK(pSurface))
		SDL_LockSurface(pSurface);
	
	switch (bpp)
	{
		case 1:	*p = pixel;
			break;

		case 2:	*(Uint16 *)p = pixel;
			break;

		case 3:	if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			{
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			}
			else
			{
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;

		case 4:	*(Uint32 *)p = pixel;
			break;
	}

	if (!surface_locked && SDL_MUSTLOCK(pSurface))
		SDL_UnlockSurface(pSurface);
}

void cg_clear(void)
{
	assert (pSurface != NULL);
	SDL_Rect r;
	r.x = r .y = 0;
	r.w = pSurface->w;
	r.h = pSurface->h;
	SDL_FillRect(pSurface, &r, 0x0);	
}

void cg_repaint(void)
{
	assert (pSurface != NULL);
	SDL_UpdateRect(pSurface, 0, 0, pSurface->w, pSurface->h);
	SDL_Flip(pSurface);
}

void cg_close(void)
{
	SDL_Quit();
}

