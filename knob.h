#ifndef H_KNOB
#define H_KNOB

#include "view.h"

typedef void (*knob_callback)(void *arg, double val);

typedef struct knob_s knob;
struct knob_s {
     double val;
     double max;
     double min;
     view *v;
     const char *label;
     int mousedowny;
     void *cbkarg;
     knob_callback callback;
};

knob* knob_create(const char *label);
void knob_setvalue(knob *k, double v);
void knob_setmin(knob *k, double min);
void knob_setmax(knob *k, double max);
void knob_free(knob *k);
void knob_draw(void *arg, SDL_Surface *screen);
void knob_mousedown(void *arg, int x, int y, int dx, int dy, int screenh);
void knob_mouseup(void *arg, int x, int y, int dx, int dy, int screenh);
void knob_mousemove(void *arg, int x, int y, int dx, int dy, int screenh);
void knob_setcallback(knob *k, void *arg, knob_callback cbk);

#endif
