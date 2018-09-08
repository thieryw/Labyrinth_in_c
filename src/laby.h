#ifndef FUNCTION_H
#define FUNCTION_H



struct point 
{
    int x;
    int y;
};

enum wall_type {VERTICAL, HORIZONTAL, NO_WALL};

static struct tree 
{
    struct point box_offset;
    enum wall_type wall;
    int wall_offset;
    int door_offset;
    struct tree *left_child;
    struct tree *right_child;
    int width;
    int height;
};


#endif