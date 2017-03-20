#include "view.h"
#include <stdlib.h>

view *view_create(void) {
     view *v = malloc(sizeof(*v));
     v->x = 0;
     v->y = 0;
     v->w = 0;
     v->h = 0;
     v->update = 0;
     v->drawcbk = NULL;
     v->cbkarg = NULL;
     return v;
}

void view_free(view *v) {
     free(v);
}

void view_setupdate(view *v, int update) {
     v->update = update;
}

void view_setdrawcallback(view *v, view_drawcallback cbk, void *arg) {
     v->drawcbk = cbk;
     v->cbkarg = arg;
}

void view_draw(view *v, SDL_Surface *screen) {
     if (!v->drawcbk) return;
     v->drawcbk(v->cbkarg, screen);
}
