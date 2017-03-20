#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "synthesizer.h"

volatile sig_atomic_t quit = 0;

void handle_signal(int signum) {
     printf("shutting down\n");
     quit = 1;
}

int main(int argc, char **argv) {

     synthesizer *s = synthesizer_create();
     synthesizer_init(s);
     
     signal(SIGINT, handle_signal);

     while (!quit && !synthesizer_quit(s)) {
	  synthesizer_loop(s);
     }

     synthesizer_stop(s);
     synthesizer_free(s);

     return 0;
}
