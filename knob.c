#include "knob.h"
#include <stdlib.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_ttf.h>

knob* knob_create(const char *label) {
     knob *k = malloc(sizeof(*k));
     k->min = 0.0;
     k->max = 0.0;
     k->val = 0.0;
     k->v = view_create();
     k->v->w = 100;
     k->v->h = 100;
     k->label = label;
     k->mousedowny = 0;
     view_setupdate(k->v, 1);
     view_setcallbackarg(k->v, k);
     view_setdrawcallback(k->v, knob_draw);
     view_setmousedowncallback(k->v, knob_mousedown);
     view_setmouseupcallback(k->v, knob_mouseup);
     view_setmousemovecallback(k->v, knob_mousemove);
     return k;
}

void knob_mousedown(void *arg, int x, int y, int dx, int dy, int screenh) {
     printf("knob mousedown %d, %d\n", x, y);
     knob *k = arg;
     k->v->capturemouse = 1;
     k->mousedowny = y;
}

void knob_mouseup(void *arg, int x, int y, int dx, int dy, int screenh) {
     printf("knob mouseup %d, %d\n", x, y);
     knob *k = arg;
     k->v->capturemouse = 0;
}

void knob_mousemove(void *arg, int x, int y, int dx, int dy, int screenh) {
     printf("knob mousemove %d, %d\n", x, y);
     knob *k = arg;
     if (k->v->capturemouse) {
	  double d = (double)dy / (double)screenh * -1.0;
	  k->val = k->val + d * (k->max - k->min);
	  if (k->val > k->max) k->val = k->max;
	  else if (k->val < k->min) k->val = k->min;
	  printf("knob value set to %f\n", k->val);
	  k->v->update = 1;
	  if (k->callback) k->callback(k->cbkarg, k->val);
     }
}

void knob_draw(void *arg, SDL_Surface *screen) {
     knob *k = arg;
     SDL_Rect um = {x: k->v->x, y: k->v->y,
		    w: k->v->w, h: k->v->h};

     SDL_FillRect(screen, &um,
		  SDL_MapRGB(screen->format, 100,100,100));

     // load the font
     TTF_Font *font=TTF_OpenFont("bitwise.ttf", 14);
     if(!font) {
	  printf("TTF_OpenFont: %s\n", TTF_GetError());
	  exit(1);
     }
     SDL_Color fontcolor={0,0,0};
     SDL_Color bgcolor={100,100,100};
     SDL_Color valcolor = {100,255,100};
     SDL_Surface *text_surface;
     
     text_surface=TTF_RenderText_Shaded(font,k->label,fontcolor,bgcolor);
     int padding = 2;
     SDL_Rect tum = {x: k->v->x + padding, y: k->v->y + padding,
		     w: text_surface->w, h: text_surface->h};
     SDL_Rect sum = {x: 0, y: 0, w: tum.w, h: tum.h};

     if(!text_surface) {
	  //handle error here, perhaps print TTF_GetError at least
	  printf("error rendering text\n");
	  exit(EXIT_FAILURE);
     }
     SDL_BlitSurface(text_surface,&sum,screen,&tum);
     //perhaps we can reuse it, but I assume not for simplicity.
     SDL_FreeSurface(text_surface);

     int cx = k->v->x + k->v->w / 2;
     int cy = k->v->y + k->v->h / 2;
     int rad = 25;
     ellipseRGBA(screen, cx, cy,
		 rad, rad, 255, 100, 100, 255);

     int end = (k->val - k->min) / (k->max - k->min) * 359;
     int q = 359 / 4;
     filledPieRGBA(screen, cx, cy, rad, q, end + q,
		   100, 255, 100, 255);

     char vallabel[100];
     snprintf(vallabel, 100, "%.2f", k->val);
     vallabel[99] = '\0';

     text_surface=TTF_RenderText_Shaded(font,vallabel,valcolor,bgcolor);
     tum.x = k->v->x + padding;
     tum.y = k->v->y + k->v->h - padding - text_surface->h;
     tum.w = text_surface->w;
     tum.h = text_surface->h;
     sum.x = 0;
     sum.y = 0;
     sum.w = tum.w;
     sum.h = tum.h;

     SDL_BlitSurface(text_surface,&sum,screen,&tum);
     //perhaps we can reuse it, but I assume not for simplicity.
     SDL_FreeSurface(text_surface);

     TTF_CloseFont(font);
}

void knob_setvalue(knob *k, double v) {
     k->val = v;
     view_setupdate(k->v, 1);
}

void knob_setmin(knob *k, double min) {
     k->min = min;
     view_setupdate(k->v, 1);
}

void knob_setmax(knob *k, double max) {
     k->max = max;
     view_setupdate(k->v, 1);
}

void knob_free(knob *k) {
     view_free(k->v);
     free(k);
}

void knob_setcallback(knob *k, void *arg, knob_callback cbk) {
     k->callback = cbk;
     k->cbkarg = arg;
}
