#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "laby.h"

enum wall_type {VERTICAL, HORIZONTAL, NO_WALL};
struct node 
{
    struct point box_offset;
    enum wall_type wall;
    int wall_offset;
    int door_offset;
    struct node *left_child;
    struct node *right_child;
    int width;
    int height;
};

 

