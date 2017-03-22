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
     v->views = viewlist_create();
     return v;
}

void view_free(view *v) {
     viewlist_free(v->views, 0);
     free(v);
}

void view_setupdate(view *v, int update) {
     v->update = update;
}

int view_needupdate(view *v) {
     if (v->update) return 1;
     for (int i=0; i<viewlist_count(v->views); i++) {
	  if (viewlist_at(v->views, i)->update) return 1;
     }
     return 0;

}

void view_clearupdate(view *v) {
     v->update = 0;
     for (int i=0; i<viewlist_count(v->views); i++) {
	  view_setupdate(viewlist_at(v->views, i), 0);
     }
}

void view_setdrawcallback(view *v, view_drawcallback cbk) {
     v->drawcbk = cbk;
}

void view_draw(view *v, SDL_Surface *screen) {
     if (v->drawcbk)
	  v->drawcbk(v->cbkarg, screen);
     for (int i=0; i<viewlist_count(v->views); i++) {
	  view_draw(viewlist_at(v->views, i), screen);
     }

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
     // pass event to child views
     view *cv = view_viewat(v, x, y);
     if (!cv) return;
     view_mousedown(cv, x, y);
}

void view_mouseup(view *v, int x, int y) {
     if (v->mouseupcbk) v->mouseupcbk(v->cbkarg, x, y, 0, 0, 0);
     view *cv = view_viewat(v, x, y);
     if (!cv) return;
     view_mouseup(cv, x, y);

}

void view_mousemove(view *v, int x, int y, int dx, int dy, int screenh) {
     if (v->mousemovecbk) v->mousemovecbk(v->cbkarg, x, y, dx, dy, screenh);
     view *cv = view_viewat(v, x, y);
     if (!cv) return;
     view_mousemove(cv, x, y, dx, dy, screenh);
}

void view_addview(view *v, view *cv) {
     viewlist_add(v->views, cv);
}

view* view_viewat(view *v, int x, int y) {
     int count = viewlist_count(v->views); 
     for (int i=0; i<count; i++) {
	  view *cv = viewlist_at(v->views, i);
	  if (cv->capturemouse || (x >= cv->x && x < cv->x + cv->w &&
	       y >= cv->y && y < cv->y + cv->h)) {
	       return cv;
	  }
     }
     return NULL;
}
