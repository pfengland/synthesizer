#include "synthesizer.h"
#include <stdlib.h>

synthesizer* synthesizer_create(void) {
     synthesizer *s = malloc(sizeof(*s));
     s->audio = audioclient_create();
     s->midi = midiclient_create();
     s->s = synth_create();
     s->sw = synthwindow_create(s->s);
     return s;
}

void synthesizer_init(synthesizer *s) {
     audioclient_init(s->audio);
     midiclient_init(s->midi);
}

void synthesizer_stop(synthesizer *s) {
     audioclient_stop(s->audio);
}

void synthesizer_free(synthesizer *s) {
     synthwindow_free(s->sw);
     synth_free(s->s);
     midiclient_free(s->midi);
     audioclient_free(s->audio);
     free(s);
}

void synthesizer_loop(synthesizer *s) {
     synthwindow_loop(s->sw);
}

int synthesizer_quit(synthesizer *s) {
     return synthwindow_quit(s->sw);
}
