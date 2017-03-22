#ifndef H_VIEWLIST
#define H_VIEWLIST

#include "dynamicarray.h"

typedef struct view_s view;

typedef struct viewlist_s viewlist;
struct viewlist_s {
     dynamicarray *views;
};

viewlist* viewlist_create(void);
void viewlist_free(viewlist *vl, int freeitems);
view* viewlist_at(viewlist *vl, int i);
int viewlist_count(viewlist *vl);
void viewlist_add(viewlist *vl, view *v);

#endif
