#include "viewlist.h"
#include <stdlib.h>

viewlist* viewlist_create(void) {
     viewlist *vl = malloc(sizeof(*vl));
     vl->views = dynamicarray_create();
     vl->views->items = malloc(sizeof(view*) * vl->views->size);
     for (int i=0; i<vl->views->size; i++) {
	  ((view**)vl->views->items)[i] = NULL;
     }
     return vl;
}

void viewlist_free(viewlist *vl, int freeitems) {
     if (freeitems) {
	  for (int i=0; i<vl->views->count; i++) {
	       view_free(((view**)vl->views->items)[i]);
	       ((view**)vl->views->items)[i] = NULL;
	  }
     }
     free(vl->views->items);
     dynamicarray_free(vl->views);
     free(vl);
}

view* viewlist_at(viewlist *vl, int i) {
     if (vl->views->count <= i) return NULL;
     return ((view**)vl->views->items)[i];
}

int viewlist_count(viewlist *vl) {
     return vl->views->count;
}

void viewlist_add(viewlist *vl, view *v) {
     int newcount = vl->views->count + 1;
     if (vl->views->size < newcount) {
	  int newsize = vl->views->size * 2;
	  vl->views->items = realloc(vl->views->items, sizeof(*v) * newsize);
	  for (int i=vl->views->size; i<newsize; i++) {
	       ((view**)vl->views->items)[i] = NULL;
	  }
	  vl->views->size = newsize;
     }
     ((view**)vl->views->items)[vl->views->count] = v;
     vl->views->count = newcount;
}

