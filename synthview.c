#include "synthview.h"

synthview* synthview_create(synth *s) {
     synthview *sv = malloc(sizeof(*sv));
     sv->s = s;
     sv->v = view_create();
     sv->v->expandh = 1;
     sv->v->expandv = 1;
     sv->freqnob = knob_create("freq");
     knob_setvalue(sv->freqnob, sv->s->freq);
     knob_setmin(sv->freqnob, synth_minfreq);
     knob_setmax(sv->freqnob, synth_maxfreq);
     knob_setcallback(sv->freqnob, sv, synthview_freqchanged);
     view_addview(sv->v, sv->freqnob->v);
     return sv;
}

void synthview_free(synthview *sv) {
     knob_free(sv->freqnob);
     free(sv);
}

void synthview_freqchanged(void *arg, double value) {
     synthview *sv = arg;
     synth_setfreq(sv->s, value);
}
