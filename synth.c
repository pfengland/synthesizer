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

     s->gate = 0;
     s->note = 0;
     
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

	  //	  float midifreq = 440 * pow(2.0, (s->note - 69) / 12.0);
	  float midifreq = 440 * powf(powf(2.0, 1.0/12), (s->note - 49));
	  float f = s->freq + midifreq;
	  float freqphase = s->freqz * 2.0 * 3.14159265359 / samplerate;
	  float wave = sin(s->phase) * s->ampz;
	  float a = s->amp * (float)s->gate;
	  
	  s->phase = s->phase + freqphase;
	  out[i] = wave;

	  //	  s->freqz = 0.001 * s->freq + 0.999 * s->freqz;
	  s->freqz = 0.01 * f + 0.99 * s->freqz;
	  s->ampz = 0.01 * a + 0.99 * s->ampz;
     }
}

void synth_setnote(synth *s, int note) {
     s->note = note;
}

void synth_setgate(synth *s, int gate) {
     s->gate = gate;
}
