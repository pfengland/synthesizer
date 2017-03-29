#include "synthesizer.h"
#include <stdlib.h>

synthesizer* synthesizer_create(void) {

     synthesizer *s = malloc(sizeof(*s));

     s->audio = audioclient_create();
     audioclient_set_process_callback(s->audio, synthesizer_process, s);

     s->midi = midiclient_create();
     midiclient_set_callback_arg(s->midi, s);
     midiclient_set_noteon_callback(s->midi, synthesizer_noteon);
     midiclient_set_noteoff_callback(s->midi, synthesizer_noteoff);
     
     s->s = synth_create();
     s->sw = synthwindow_create(s->s);

     return s;
}

void synthesizer_noteon(void *arg, unsigned int num,
				unsigned int val) {
     synthesizer *s = arg;
     printf("noteon: %d, %d\n", num, val);
     synth_setnote(s->s, num);
     synth_setgate(s->s, 1);
}

void synthesizer_noteoff(void *arg, unsigned int num,
				unsigned int val) {
     synthesizer *s = arg;     
     printf("noteoff: %d\n", num);
     synth_setgate(s->s, 0);
}

void synthesizer_process(void *arg, int samplerate,
			 jack_nframes_t nframes,
			 jack_default_audio_sample_t *in,
			 jack_default_audio_sample_t *out1,
			 jack_default_audio_sample_t *out2) {
     synthesizer *s = arg;
     synth_process(s->s, samplerate, nframes, out1);
     for (int i=0; i<nframes; i++) out2[i] = out1[i];
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
