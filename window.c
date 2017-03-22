#include "window.h"
#include <stdlib.h>
#include <X11/Xlib.h>
#include <SDL/SDL_ttf.h>

window* window_create(const char *name) {

     window *w = malloc(sizeof(*w));
     w->v = view_create();
     view_setupdate(w->v, 1);

     w->quit = 0;
     w->framestart = 0;

     XInitThreads();
     SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
     if (TTF_Init() == -1) {
	  printf("TTF_Init: %s\n", TTF_GetError());
	  exit(1);
     }

     // get the screen
     //    int opts = SDL_SWSURFACE|SDL_NOFRAME;
     int opts = SDL_SWSURFACE|SDL_RESIZABLE;
     w->screen = SDL_SetVideoMode(640, 480, 32, opts);

     SDL_WM_SetCaption(name, NULL);

     return w;
}

void window_free(window *w) {
     TTF_Quit();
     SDL_Quit();
     view_free(w->v);
     free(w);
}

void window_loop(window *w) {
     window_events(w);
     window_update(w);
}

void window_update(window *w) {

     // limit framerate
     int elapsed = SDL_GetTicks() - w->framestart;
     if (elapsed < window_frametime) {
	  return;
     }

     if (view_needupdate(w->v)) {

	  view_clearupdate(w->v);

	  // fill background
	  SDL_FillRect(w->screen, NULL,
		       SDL_MapRGB(w->screen->format, 0,100,100));

	  // draw child views
	  view_draw(w->v, w->screen);

	  SDL_Flip(w->screen);

	  w->framestart = SDL_GetTicks();
     } 
}

void window_events(window *w) {

     SDL_Event event;

     while (SDL_PollEvent(&event)) {

	  if (event.type == SDL_KEYDOWN) {

	  } else if (event.type == SDL_QUIT) {
	       w->quit = 1;
	  } else if (event.type == SDL_VIDEORESIZE) {
	       int opts = SDL_SWSURFACE|SDL_RESIZABLE;
	       w->screen = SDL_SetVideoMode(event.resize.w, event.resize.h,
					    32, opts);
	       view_setupdate(w->v, 1);
	  } else if (event.type == SDL_MOUSEBUTTONDOWN) {
	       int x = event.button.x;
	       int y = event.button.y;
	       view_mousedown(w->v, x, y);
	  } else if (event.type == SDL_MOUSEBUTTONUP) {
	       int x = event.button.x;
	       int y = event.button.y;
	       view_mouseup(w->v, x, y);
	  } else if (event.type == SDL_MOUSEMOTION) {
	       int x = event.motion.x;
	       int y = event.motion.y;
	       view_mousemove(w->v, x, y, event.motion.xrel, event.motion.yrel,
			      w->screen->h);
	  }
     }
}

int window_quit(window *w) {
     return w->quit; 
}
