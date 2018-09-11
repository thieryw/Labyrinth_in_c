#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "laby.h"

static int rand_a_b(int a, int b)
{
    if (a < b)
    {
        return (rand() % (b - a) + a);
    }
    else if (a > b)
    {
        return (rand() % (a - b) + b);
    }
    else
    {
        return (a);
    }
}
static void _build_wall(struct node_t *maze)
{
    if (maze->wall == HORIZONTAL)
    {
        maze->wall_offset = rand_a_b(1, maze->height);
        maze->door_offset = rand_a_b(0, maze->width);
    }
    else
    {
        maze->wall_offset = rand_a_b(1, maze->width);
        maze->door_offset = rand_a_b(0, maze->height);
    }
}

static void _make_wall(struct node_t *maze)
{
    int rand_n;
    if (maze->width > maze->height)
    {
        maze->wall = VERTICAL;
    }
    else if (maze->width < maze->height)
    {
        maze->wall = HORIZONTAL;
    }
    else
    {
        rand_n = rand_a_b(1, 3);
        if (rand_n == 1)
        {
            maze->wall = VERTICAL;
        }
        else
        {
            maze->wall = HORIZONTAL;
        }
    }
    _build_wall(maze);
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
        _maze_gen(maze->left_child, maze->wall_offset, H);
        _maze_gen(maze->right_child, W - maze->wall_offset, H);
    }
    else if (maze->wall == HORIZONTAL)
    {
        *(maze->right_child) = (struct node_t){.x = maze->x, .y = maze->y + maze->wall_offset};
        _maze_gen(maze->left_child, W, maze->wall_offset);
        _maze_gen(maze->right_child, W, H - maze->wall_offset);
    }
}

struct node_t *maze_gen(int W, int H)
{
    srand(time(NULL));
    struct node_t *maze = malloc(sizeof(struct node_t));

    *maze = (struct node_t){.x = 0, .y = 0};

    _maze_gen(maze, W, H);

    return (maze);
}

static void _maze_svg(struct node_t *t, FILE *fp, char str[])
{
    if (t->wall == NO_WALL)
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

void maze_svg(struct node_t *t, char file_name[])
{
    FILE *fp = fopen(file_name, "w");
    char str[] = "<line x1=\" %d\" y1=\" %d\" x2=\" %d\" y2=\" %d\" style=\"stroke:rgb(0,0,0);stroke-width:0.2\"/>\n";

    fprintf(fp, "<svg width=\" %d\" height=\" %d\">\n", t->width, t->height);
    fclose(fp);

    fp = fopen(file_name, "a");

    fprintf(fp, str, t->x + 1, t->y, t->x + t->width, t->y);
    fprintf(fp, str, t->x, t->y, t->x, t->y + t->height);
    fprintf(fp, str, t->x, t->y + t->height, t->x + t->width - 1, t->y + t->height);
    fprintf(fp, str, t->x + t->width, t->y, t->x + t->width, t->y + t->height);

    _maze_svg(t, fp, str);
    fclose(fp);
}

static void _free_maze(struct node_t *t)
{
    struct node_t *left = t->left_child;
    struct node_t *right = t->right_child;
    
    free(t);
    if(left == NULL && right == NULL)
    {
        return;
    }

    free_maze(left);
    free_maze(right);
}

void free_maze(struct node_t *t)
{
    _free_maze(t);
}