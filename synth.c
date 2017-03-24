#include "synth.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

synth* synth_create(void) {
     synth *s = malloc(sizeof(*s));

     s->freq = synth_initfreq;
     s->freqz = s->freq;

     s->phase = 0.0;

     s->amp = synth_initamp;
     s->ampz = s->amp;
     
     return s;
}

void synth_free(synth *s) {
     free(s);
}

void synth_setfreq(synth *s, double freq) {
     printf("synth setting freq to %f\n", freq);
     s->freq = freq;
}

void synth_setamp(synth *s, double amp) {
     printf("synth setting amp to %f\n", amp);
     s->amp = amp;
}

void synth_process(synth *s, int samplerate, int nframes, float *out) {
     for (int i=0; i<nframes; i++) {

	  float freqphase = s->freqz * 2.0 * 3.14159265359 / samplerate;
	  float wave = sin(s->phase) * s->ampz;
	  
	  s->phase = s->phase + freqphase;
	  out[i] = wave;

	  s->freqz = 0.001 * s->freq + 0.999 * s->freqz;
	  s->ampz = 0.001 * s->amp + 0.999 * s->ampz;
     }
}
