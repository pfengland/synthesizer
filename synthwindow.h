#ifndef H_SYNTHWINDOW
#define H_SYNTHWINDOW

#include "window.h"
#include "knob.h"
#include "synth.h"

typedef struct synthwindow_s synthwindow;
struct synthwindow_s {
     window *w;
     synth *s;
     knob *freqnob;
};

synthwindow* synthwindow_create(synth *s);
void synthwindow_free(synthwindow *sw);
void synthwindow_loop(synthwindow *sw);
int synthwindow_quit(synthwindow *sw);

#endif
