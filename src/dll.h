
#ifndef DLL_H
#define DLL_H

struct dll_t
{
    void * pvalue;
    struct dll_t *next;
    struct dll_t *prec;
};

/** value must be allocated with malloc, will be free internally */
void dll_append(struct dll_t **pl, void * pvalue);
void dll_free(struct dll_t **pl);
void dll_delete(struct dll_t **pl, struct dll_t *e);

/** 
 * return a string representing the list.
 * Need to be feed!
 */
char *dll_to_string(struct dll_t *l, char * (*value_to_string)(void *));

void dll_print(struct dll_t *l, char * (*value_to_string)(void *)); 
/** l will be concatenated at the end of pl */ 
 void dll_concat(struct dll_t **pl1, struct dll_t *l2);

#endif