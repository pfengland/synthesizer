#include "synthwindow.h"
#include <stdlib.h>

synthwindow* synthwindow_create(synth *s) {
     synthwindow *sw = malloc(sizeof(*sw));
     sw->w = window_create("synthesizer");
     sw->s = s;
     sw->sv = synthview_create(s);
     view_addview(sw->w->v, sw->sv->v);
     return sw;
}

void synthwindow_free(synthwindow *sw) {
     window_free(sw->w);
     free(sw);
}

void synthwindow_loop(synthwindow *sw) {
     window_loop(sw->w);
}

int synthwindow_quit(synthwindow *sw) {
     return window_quit(sw->w);
}
