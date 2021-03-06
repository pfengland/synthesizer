#ifndef H_WINDOW
#define H_WINDOW

#include <SDL/SDL.h>
#include "view.h"

static const int window_frameRate = 30;
// key repeat rate
static const int window_initrepeat = 300;
static const int window_repeat = 100;

static const int window_fps = 20;
#define window_frametime 1000 / window_fps

typedef struct window_s window;
struct window_s {
     SDL_Surface *screen;
     int quit;
     int framestart;
     view *v;
};

window* window_create(const char *name);
void window_free(window *w);
void window_loop(window *w);
void window_events(window *w);
void window_update(window *w);
int window_quit(window *w);

#endif
