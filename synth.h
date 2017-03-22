#ifndef H_SYNTH
#define H_SYNTH

static const double synth_initfreq = 200.0;
static const double synth_minfreq = 10.0;
static const double synth_maxfreq = 3000.0;

typedef struct synth_s synth;
struct synth_s {
     double freq;
     double freqz;
     double amp;
     double phase;
};

synth* synth_create(void);
void synth_free(synth *s);
void synth_setfreq(synth *s, double freq);
void synth_process(synth *s, int samplerate, int nframes, float *out);

#endif
