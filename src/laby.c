#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "laby.h"

static void _make_wall(struct node_t *maze)
{
    if(maze->width >= maze->height)
    {
        maze->wall = VERTICAL;
        maze->wall_offset = maze->width / 2;
        maze->door_offset = 0;
    }
    else
    {
        maze->wall = HORIZONTAL;
        maze->wall_offset = maze->height / 2;
        maze->door_offset = 0;
    }
}

static void _maze_gen(struct node_t *maze, int W, int H)
{

    maze->width = W;
    maze->height = H;
    
    if (W == 1 || H == 1)
    {
        maze->wall = NO_WALL;
        maze->left_child = NULL;
        maze->right_child = NULL;
        return;
    }

    _make_wall(maze);
    maze->left_child = malloc(sizeof(struct node_t));
    maze->right_child = malloc(sizeof(struct node_t));


    *(maze->left_child) = (struct node_t){.x = maze->x, .y = maze->y};
    if (maze->wall == VERTICAL)
    {
        *(maze->right_child) = (struct node_t){.x = maze->x + maze->wall_offset, .y = maze->y};
        _maze_gen(maze->left_child,maze->wall_offset,H);
        _maze_gen(maze->right_child,W - maze->wall_offset,H); 
    }
    else if (maze->wall == HORIZONTAL)
    {
        *(maze->right_child) = (struct node_t){.x = maze->x, .y = maze->y + maze->wall_offset};
        _maze_gen(maze->left_child,W,maze->wall_offset);
        _maze_gen(maze->right_child,W,H - maze->wall_offset);
    }
}

struct node_t *maze_gen(int W, int H)
{
    struct node_t *maze = malloc(sizeof(struct node_t));

    *maze = (struct node_t){.x = 0, .y = 0};

    _maze_gen(maze,W,H);

    return (maze);
}



static void _maze_svg(struct node_t *t, FILE *fp, char str[])
{
    if(t->wall == NO_WALL)
    {
        return;
    }
    else if (t->wall == VERTICAL)
    {
        fprintf(fp, str, t->x + t->wall_offset, t->y, t->x + t->wall_offset, t->y + t->door_offset);
        fprintf(fp, str, t->x + t->wall_offset, t->y + t->door_offset + 1, t->x + t->wall_offset, t->y + t->height);
    }
    else
    {
        fprintf(fp, str, t->x, t->y + t->wall_offset, t->x + t->door_offset, t->y + t->wall_offset);
        fprintf(fp, str, t->x + t->door_offset + 1, t->y + t->wall_offset, t->x + t->width, t->y + t->wall_offset);
    }

    _maze_svg(t->left_child, fp, str);
    _maze_svg(t->right_child, fp, str);
}

void maze_svg(struct node_t *t)
{
    FILE *fp = fopen("maze.svg", "w");
    char str[] = "<line x1=\" %d\" y1=\" %d\" x2=\" %d\" y2=\" %d\" style=\"stroke:rgb(0,0,0);stroke-width:0.2\"/>\n";

    fprintf(fp, "<svg width=\" %d\" height=\" %d\">\n", t->width, t->height);
    fclose(fp);

    fp = fopen("maze.svg", "a");

    fprintf(fp, str, t->x + 1, t->y, t->x + t->width, t->y);
    fprintf(fp, str, t->x, t->y, t->x, t->y + t->height);
    fprintf(fp, str, t->x, t->y + t->height, t->x + t->width - 1, t->y + t->height);
    fprintf(fp, str, t->x + t->width, t->y, t->x + t->width, t->y + t->height);

    _maze_svg(t, fp, str);
    fclose(fp);
}