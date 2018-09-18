#ifndef DLL_POINT_H
#define DLL_POINT_H
#include "laby.h"
#include "dll.h"


struct point_t
{
    float x;
    float y;
};

struct dll_point_t
{
    struct point_t *pvalue;
    struct dll_point_t *next;
    struct dll_point_t *prec;
};

void dll_point_append(struct dll_point_t **pl, struct point_t point);
void dll_point_free(struct dll_point_t **pl);
void dll_point_delete(struct dll_point_t **pl, struct dll_point_t *e);

void dll_point_print(struct dll_point_t *l); 
void dll_point_concat(struct dll_point_t **pl1, struct dll_point_t *l2);

#endif