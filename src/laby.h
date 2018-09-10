#ifndef FUNCTION_H
#define FUNCTION_H

struct point
{
    int x;
    int y;
};

enum wall_type
{
    VERTICAL,
    HORIZONTAL,
    NO_WALL
};

struct node_t
{
    int x, y;
    enum wall_type wall;
    int wall_offset;
    int door_offset;
    struct node_t *left_child;
    struct node_t *right_child;
    int width;
    int height;
} ;
struct node_t *maze_gen(int W, int H);
void maze_svg(struct node_t *t);
#endif