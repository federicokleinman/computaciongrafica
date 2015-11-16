#ifndef CANVAS_H
#define CANVAS_H

#ifndef APPLEMAC
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif //APPLEMAC

#include "color.h"

#include <assert.h>

void cg_init(int, int, char*);
void cg_putpixel(int, int, Color);
void cg_clear(void);
void cg_repaint(void);
void cg_close(void);
//void cg_begin_frame();
//void cg_end_frame();

#endif //CANVAS_H
