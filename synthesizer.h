#ifndef H_SYNTHESIZER
#define H_SYNTHESIZER

#include "midiclient.h"
#include "audioclient.h"
#include "synthwindow.h"
#include "synth.h"

typedef struct synthesizer_s synthesizer;
struct synthesizer_s {
     audioclient *audio;
     midiclient *midi;
     synthwindow *sw;
     synth *s;
};

synthesizer* synthesizer_create(void);
void synthesizer_free(synthesizer *s);
void synthesizer_init(synthesizer *s);
void synthesizer_stop(synthesizer *s);
void synthesizer_loop(synthesizer *s);
int synthesizer_quit(synthesizer *s);

#endif
