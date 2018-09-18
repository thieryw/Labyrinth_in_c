#include <stdlib.h>
#include "laby.h"
#include "dll_point.h"
#include "dll.h"


void dll_point_append(struct dll_point_t **pl, struct point_t point){

    struct point_t *p_point = malloc(sizeof(struct point_t));

    *p_point = point;

    dll_append(pl,p_point);
}

void dll_point_free(struct dll_point_t **pl)
{
    dll_free(pl);
}

void dll_point_delete(struct dll_point_t **pl, struct dll_point_t *e)
{
    dll_delete(pl, e);
}

char * value_to_string(struct point_t * p_point)
{

    char *str = malloc(sizeof(char) * 37);

    sprintf(str,"[ %f, %f ]",p_point->x,p_point->y);

    return str;

}

void dll_point_print(struct dll_point_t *l)
{
    dll_print(l, value_to_string);
}

void dll_point_concat(struct dll_point_t **pl1, struct dll_point_t *l2)
{
    dll_concat(pl1,l2);
}