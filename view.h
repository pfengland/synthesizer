#ifndef H_VIEW
#define H_VIEW

#include <SDL/SDL.h>

typedef void (*view_drawcallback)(void *arg, SDL_Surface *screen);

typedef struct view_s view;
struct view_s {
     int x, y, h, w;
     int update;
     view_drawcallback drawcbk;
     void *cbkarg;
};

view *view_create(void);
void view_free(view *v);
void view_setupdate(view *v, int update);
void view_setdrawcallback(view *v, view_drawcallback cbk, void *arg);
void view_draw(view *v, SDL_Surface *screen);

#endif
