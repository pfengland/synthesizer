#include "synth.h"
#include <stdlib.h>

synth* synth_create(void) {
     synth *s = malloc(sizeof(*s));
     s->freq = synth_initfreq;
     return s;
}

void synth_free(synth *s) {
     free(s);
}

void synth_setfreq(synth *s, double freq) {
     s->freq = freq;
}
