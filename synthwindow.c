#include "synthwindow.h"
#include <stdlib.h>

synthwindow* synthwindow_create(synth *s) {
     synthwindow *sw = malloc(sizeof(*sw));
     sw->w = window_create("synthesizer");
     sw->s = s;
     sw->freqnob = knob_create("freq");
     knob_setvalue(sw->freqnob, sw->s->freq);
     knob_setmin(sw->freqnob, synth_minfreq);
     knob_setmax(sw->freqnob, synth_maxfreq);
     knob_setcallback(sw->freqnob, sw, synthwindow_freqchanged);
     window_addview(sw->w, sw->freqnob->v);
     return sw;
}

void synthwindow_freqchanged(void *arg, double value) {
     synthwindow *sw = arg;
     sw->s->freq = value;
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
