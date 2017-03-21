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
     v->capturemouse = 0;
     return v;
}

void view_free(view *v) {
     free(v);
}

void view_setupdate(view *v, int update) {
     v->update = update;
}

void view_setdrawcallback(view *v, view_drawcallback cbk) {
     v->drawcbk = cbk;
}

void view_draw(view *v, SDL_Surface *screen) {
     if (!v->drawcbk) return;
     v->drawcbk(v->cbkarg, screen);
}

void view_setcallbackarg(view *v, void *arg) {
     v->cbkarg = arg;
}

void view_setmousedowncallback(view *v, view_mousecallback cbk) {
     v->mousedowncbk = cbk;
}

void view_setmouseupcallback(view *v, view_mousecallback cbk) {
     v->mouseupcbk = cbk;
}

void view_setmousemovecallback(view *v, view_mousecallback cbk) {
     v->mousemovecbk = cbk;
}

void view_mousedown(view *v, int x, int y) {
     if (v->mousedowncbk) v->mousedowncbk(v->cbkarg, x, y, 0, 0, 0);
}

void view_mouseup(view *v, int x, int y) {
     if (v->mouseupcbk) v->mouseupcbk(v->cbkarg, x, y, 0, 0, 0);
}

void view_mousemove(view *v, int x, int y, int dx, int dy, int screenh) {
     if (v->mousemovecbk) v->mousemovecbk(v->cbkarg, x, y, dx, dy, screenh);
}
