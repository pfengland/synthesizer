#include "window.h"
#include <stdlib.h>
#include <X11/Xlib.h>
#include <SDL/SDL_ttf.h>

window* window_create(const char *name) {

     window *w = malloc(sizeof(*w));

     w->update = 1;
     w->quit = 0;
     w->framestart = 0;

     w->views = viewlist_create();

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
     viewlist_free(w->views, 0);
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

     if (window_needupdate(w)) {

	  window_clearupdate(w);

	  SDL_FillRect(w->screen, NULL,
		       SDL_MapRGB(w->screen->format, 0,100,100));

	  for (int i=0; i<viewlist_count(w->views); i++) {
	       view_draw(viewlist_at(w->views, i), w->screen);
	  }

	  SDL_Flip(w->screen);

	  w->framestart = SDL_GetTicks();
     } 
}

int window_needupdate(window *w) {
     if (w->update) return 1;
     for (int i=0; i<viewlist_count(w->views); i++) {
	  if (viewlist_at(w->views, i)->update) return 1;
     }
     return 0;
}

void window_clearupdate(window *w) {
     w->update = 0;
     for (int i=0; i<viewlist_count(w->views); i++) {
	  view_setupdate(viewlist_at(w->views, i), 0);
     }
     return 0;
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
	       w->update = 1;
	  } else if (event.type == SDL_MOUSEBUTTONDOWN) {
	       int x = event.button.x;
	       int y = event.button.y;
	       window_mousedown(w, x, y);
	  } else if (event.type == SDL_MOUSEBUTTONUP) {
	       int x = event.button.x;
	       int y = event.button.y;
	       window_mouseup(w, x, y);
	  } else if (event.type == SDL_MOUSEMOTION) {
	       int x = event.motion.x;
	       int y = event.motion.y;
	       window_mousemove(w, x, y);
	  }
     }
}

view* window_viewat(window *w, int x, int y) {
     for (int i=0; i<viewlist_count(w->views); i++) {
	  view *v = viewlist_at(w->views, i);
	  if (x >= v->x && x < v->x + v->w &&
	      y >= v->y && y < v->y + v->h) {

	       return v;
	  }
     }
     return NULL;
}

void window_mousedown(window *w, int x, int y) {
     view *v = window_viewat(w, x, y);
     if (!v) return;
     view_mousedown(v, x, y);
}

void window_mouseup(window *w, int x, int y) {
     view *v = window_viewat(w, x, y);
     if (!v) return;
     view_mouseup(v, x, y);
}

void window_mousemove(window *w, int x, int y) {
     view *v = window_viewat(w, x, y);
     if (!v) return;
     view_mousemove(v, x, y);
}

void window_addview(window *w, view *v) {
     viewlist_add(w->views, v);
}

int window_quit(window *w) {
     return w->quit; 
}
