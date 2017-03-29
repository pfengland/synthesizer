#ifndef H_MIDICLIENT
#define H_MIDICLIENT

#include <alsa/asoundlib.h>
#include <pthread.h>

typedef void (*midiclient_callback_t)(void *arg, unsigned int num,
				      unsigned int val);

typedef struct midiclient_s midiclient;
struct midiclient_s {
     snd_seq_t *handle;
     int portid;
     int queueid;
     pthread_t thread;
     int stop;
     midiclient_callback_t cc_callback;
     midiclient_callback_t noteon_callback;
     midiclient_callback_t noteoff_callback;
     void *callback_arg;
};
midiclient* midiclient_create(void);
void midiclient_free(midiclient *m);
void midiclient_init(midiclient *m);
void midiclient_stop(midiclient *m);
void midiclient_startthread(midiclient *m);
void midiclient_read(midiclient *m);
void* midiclient_thread(void *m);
void midiclient_set_callback_arg(midiclient *m, void *arg);
void midiclient_set_cc_callback(midiclient *m, midiclient_callback_t callback);
void midiclient_set_noteon_callback(midiclient *m,
				    midiclient_callback_t callback);
void midiclient_set_noteoff_callback(midiclient *m,
				     midiclient_callback_t callback);

#endif
