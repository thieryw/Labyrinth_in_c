#ifndef LABY_H
#define LABY_H


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


struct node_t *maze_gen(int w, int h);

void maze_svg(struct node_t *tree, char file_name[]);

void solution_svg(char file_name[],struct node_t *tree);


#endif