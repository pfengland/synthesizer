#include "knob.h"
#include <stdlib.h>

knob* knob_create(void) {
     knob *k = malloc(sizeof(*k));
     k->min = 0.0;
     k->max = 0.0;
     k->val = 0.0;
     k->v = view_create();
     k->v->w = 100;
     k->v->h = 100;
     view_setupdate(k->v, 1);
     view_setdrawcallback(k->v, knob_draw, k);
     return k;
}

void knob_draw(void *arg, SDL_Surface *screen) {
     knob *k = arg;
     SDL_Rect um = {x: k->v->x, y: k->v->y,
		    w: k->v->w, h: k->v->h};

     SDL_FillRect(screen, &um,
		  SDL_MapRGB(screen->format, 100,100,100));

}

void knob_setvalue(knob *k, double v) {
     k->val = v;
     view_setupdate(k->v, 1);
}

void knob_setmin(knob *k, double min) {
     k->min = min;
     view_setupdate(k->v, 1);
}

void knob_setmax(knob *k, double max) {
     k->max = max;
     view_setupdate(k->v, 1);
}

void knob_free(knob *k) {
     view_free(k->v);
     free(k);
}

