#ifndef H_VIEW
#define H_VIEW

#include <SDL/SDL.h>

typedef void (*view_drawcallback)(void *arg, SDL_Surface *screen);
typedef void (*view_mousecallback)(void *arg, int x, int y);

typedef struct view_s view;
struct view_s {
     int x, y, h, w;
     int update;
     view_drawcallback drawcbk;
     view_mousecallback mousedowncbk;
     view_mousecallback mouseupcbk;
     view_mousecallback mousemovecbk;
     void *cbkarg;
     int capturemouse;
};

view *view_create(void);
void view_free(view *v);
void view_setupdate(view *v, int update);
void view_setcallbackarg(view *v, void *arg);
void view_setdrawcallback(view *v, view_drawcallback cbk);
void view_draw(view *v, SDL_Surface *screen);
void view_setmousedowncallback(view *v, view_mousecallback cbk);
void view_setmouseupcallback(view *v, view_mousecallback cbk);
void view_setmousemovecallback(view *v, view_mousecallback cbk);
void view_mousedown(view *v, int x, int y);
void view_mouseup(view *v, int x, int y);
void view_mousemove(view *v, int x, int y);

#endif
