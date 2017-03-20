#ifndef H_DICTIONARY
#define H_DICTIONARY

#define dictionary_hashsize 101

typedef struct dictionary_s dictionary;
struct dictionary_s {
     nlist *hashtable[dictionary_hashsize];
};

#endif
