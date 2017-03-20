#ifndef H_KNOB
#define H_KNOB

#include "view.h"

typedef struct knob_s knob;
struct knob_s {
     double val;
     double max;
     double min;
     view *v;
};

knob* knob_create(void);
void knob_setvalue(knob *k, double v);
void knob_setmin(knob *k, double min);
void knob_setmax(knob *k, double max);
void knob_free(knob *k);
void knob_draw(void *arg, SDL_Surface *screen);

#endif
