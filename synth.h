#ifndef H_SYNTH
#define H_SYNTH

static const double synth_initfreq = 200.0;
static const double synth_minfreq = 0.001;
static const double synth_maxfreq = 3000.0;

typedef struct synth_s synth;
struct synth_s {
     int freq;
};

synth* synth_create(void);
void synth_free(synth *s);
void synth_setfreq(synth *s, double freq);

#endif
