#ifndef H_SYNTH
#define H_SYNTH

static const double synth_initfreq = 200.0;
static const double synth_minfreq = 10.0;
static const double synth_maxfreq = 3000.0;

static const double synth_initamp = 0.01;
static const double synth_minamp = 0.0;
static const double synth_maxamp = 0.1;

typedef struct synth_s synth;
struct synth_s {
     double freq;
     double freqz;
     double amp;
     double ampz;
     double phase;
};

synth* synth_create(void);
void synth_free(synth *s);
void synth_setfreq(synth *s, double freq);
void synth_setamp(synth *s, double amp);
void synth_process(synth *s, int samplerate, int nframes, float *out);

#endif
