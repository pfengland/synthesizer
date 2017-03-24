#ifndef H_SYNTHVIEW
#define H_SYNTHVIEW

#include "knob.h"
#include "view.h"
#include "synth.h"

typedef struct synthview_s synthview;
struct synthview_s {
     knob *freqnob;
     knob *ampnob;
     view *v;
     synth *s;
};

synthview* synthview_create(synth *s);
void synthview_free(synthview *sw);
void synthview_freqchanged(void *arg, double value);
void synthview_ampchanged(void *arg, double value);

#endif
