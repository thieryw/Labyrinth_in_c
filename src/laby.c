#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "laby.h"
#include "dll_point.h"

static int rand_a_b(int a, int b)
{
    if (a < b)
    {
        return rand() % (b - a) + a;
    }
    else if (a > b)
    {
        return rand() % (a - b) + b;
    }
    else
    {
        return a;
    }
}

static void build_wall(struct node_t *node)
{

    if (node->width > node->height)
    {
        node->wall = VERTICAL;
    }
    else if (node->width < node->height)
    {
        node->wall = HORIZONTAL;
    }
    else
    {
        int rand_n = rand_a_b(1, 3);

        if (rand_n == 1)
        {
            node->wall = VERTICAL;
        }
        else
        {
            node->wall = HORIZONTAL;
        }
    }

    if (node->wall == HORIZONTAL)
    {
        node->wall_offset = rand_a_b(1, node->height);
        node->door_offset = rand_a_b(0, node->width);
    }
    else
    {
        node->wall_offset = rand_a_b(1, node->width);
        node->door_offset = rand_a_b(0, node->height);
    }


}




/** 
 * returns maze tree.  
 * w and h represent width and height of maze
 * x and y are the coordinates of upper left hand corner of maze. 
 */
static struct node_t * _maze_gen(int w, int h, int x, int y)
{
    struct node_t *tree = malloc(sizeof(struct node_t));

    *tree = (struct node_t){.width = w, .height = h, .x = x, .y = y};

    if (w == 1 || h == 1)
    {
        tree->wall = NO_WALL;
        tree->left_child = NULL;
        tree->right_child = NULL;
        return tree;
    }

    build_wall(tree);

    if (tree->wall == VERTICAL)
    {
        tree->left_child = _maze_gen(tree->wall_offset, h,tree->x,tree->y);
        tree->right_child = _maze_gen(w - tree->wall_offset, h,tree->x + tree->wall_offset,tree->y);
    }
    else if (tree->wall == HORIZONTAL)
    {
        tree->left_child = _maze_gen(w, tree->wall_offset,tree->x,tree->y);
        tree->right_child = _maze_gen(w, h - tree->wall_offset,tree->x,tree->y + tree->wall_offset);
    }

    return tree;
}



struct node_t *maze_gen(int w, int h)
{
    srand(time(NULL));

    return _maze_gen(w, h,0,0);

}


char pattern[] = "<line x1=\" %d\" y1=\" %d\" x2=\" %d\" y2=\" %d\" style=\"stroke:rgb(0,0,0);stroke-width:0.2\"/>\n";

int max_line_length = 79 + 4 * 13 ;

/** returns a string that represents maze walls. */
static char *_walls_str(struct node_t *sub_tree)
{

    if (sub_tree->wall == NO_WALL)
    {

        char *out = malloc(sizeof(char) * 1);

        out[0] = '\0';

        return out;
    }

    char out_wall[2 * max_line_length];

    if (sub_tree->wall == VERTICAL)
    {

        sprintf(
            out_wall,
            pattern,
            sub_tree->x + sub_tree->wall_offset,
            sub_tree->y,
            sub_tree->x + sub_tree->wall_offset,
            sub_tree->y + sub_tree->door_offset);

        char _out_wall[max_line_length];

        sprintf(
            _out_wall,
            pattern,
            sub_tree->x + sub_tree->wall_offset,
            sub_tree->y + sub_tree->door_offset + 1,
            sub_tree->x + sub_tree->wall_offset,
            sub_tree->y + sub_tree->height);

        strcat(out_wall, _out_wall);
    }
    else
    {
        sprintf(
            out_wall,
            pattern,
            sub_tree->x,
            sub_tree->y + sub_tree->wall_offset,
            sub_tree->x + sub_tree->door_offset,
            sub_tree->y + sub_tree->wall_offset);

        char _out_wall[max_line_length];

        sprintf(
            _out_wall,
            pattern,
            sub_tree->x + sub_tree->door_offset + 1,
            sub_tree->y + sub_tree->wall_offset,
            sub_tree->x + sub_tree->width,
            sub_tree->y + sub_tree->wall_offset);

        strcat(out_wall, _out_wall);
    }

    char *out_left = _walls_str(sub_tree->left_child);
    char *out_right = _walls_str(sub_tree->right_child);

    char *out = malloc(sizeof(char) * (strlen(out_left) + strlen(out_wall) + strlen(out_right) + 1));

    out[0] = '\0';


    strcat(out,out_left);
    strcat(out,out_wall);
    strcat(out,out_right);


    free(out_left);
    free(out_right);

    return out;

}

/** returns a string that is a full maze representation. */
static char * maze_str(struct node_t *tree)
{
    char str_init[max_line_length];
    char str_left_side[max_line_length];
    char str_right_side[max_line_length];
    char str_upper_side[max_line_length];
    char str_lower_side[max_line_length];

    sprintf(str_init, "<svg width=\" %d\" height=\" %d\">\n", tree->width, tree->height);
    sprintf(str_left_side, pattern, tree->x + 1, tree->y, tree->x + tree->width, tree->y);
    sprintf(str_right_side, pattern, tree->x, tree->y, tree->x, tree->y + tree->height);
    sprintf(str_upper_side, pattern, tree->x, tree->y + tree->height, tree->x + tree->width - 1, tree->y + tree->height);
    sprintf(str_lower_side, pattern, tree->x + tree->width, tree->y, tree->x + tree->width, tree->y + tree->height);

    /*
    char *str_sides = malloc(sizeof(char) * (
        strlen(str_init) + 
        strlen(str_left_side) + 
        strlen(str_right_side) + 
        strlen(str_upper_side) + 
        strlen(str_lower_side) + 1));

    sprintf(str_sides,"%s%s%s%s%s",str_init,str_left_side,str_right_side,str_upper_side,str_lower_side);

    char *str_walls = _walls_str(tree);

    char *out = malloc(sizeof(char) * (strlen(str_sides) + strlen(str_walls) + 1));

    sprintf(out,"%s%s",str_sides,str_walls);

    
    free(str_sides);
    free(str_walls);
    */

    char *str_walls = _walls_str(tree);

    char *out = malloc(sizeof(char) * (strlen(str_init) +
                                       strlen(str_left_side) +
                                       strlen(str_right_side) +
                                       strlen(str_upper_side) +
                                       strlen(str_lower_side) +
                                       strlen(str_walls) + 1));

    sprintf(out, "%s%s%s%s%s%s",
            str_init,
            str_left_side,
            str_right_side,
            str_upper_side,
            str_lower_side,
            str_walls);

    free(str_walls);

    return out;
}
/** puts a string representing a maze in an svg file. */

void maze_svg(struct node_t *tree, char file_name[])
{
    char *str_maze = maze_str(tree);

    FILE *f = fopen(file_name, "w");

    fprintf(f,"%s",str_maze);

    fclose(f);
    free(str_maze);
}

/** assert e->wall is not NO_WALL */
static struct point_t _get_door(struct node_t *e)
{

    struct point_t door;

    if (e->wall == VERTICAL)
    {
        door.x = (float)e->x + (float)e->wall_offset;
        door.y = (float)e->y + (float)e->door_offset + 0.5;
    }
    else
    {
        door.x = (float)e->x + (float)e->door_offset + 0.5;
        door.y = (float)e->y + (float)e->wall_offset;
    }

    return door;
}

static int is_door_on_rect(struct point_t door, struct node_t *e)
{

    return (door.x > (float)e->x && door.x < (float)e->x + (float)e->width) &&
               (door.y == (float)e->y || door.y == (float)e->y + (float)e->height) ||
           (door.y > (float)e->y && door.y < (float)e->y + (float)e->height) &&
               (door.x == (float)e->x || door.x == (float)e->x + (float)e->width);
}

/** 
 * return's a dll_point that represent a path from in to out ,in excluded.
 * assert in out are respectively entrance and exit of the provided tree.
 * returned list must be manually freed
 * */
static struct dll_point_t *_solution(struct node_t *tree, struct point_t in, struct point_t out)
{
    struct point_t door;
    struct dll_point_t *l = NULL;

    if (tree->wall == NO_WALL)
    {
        door = (struct point_t){.x = in.x, .y = in.y};
        dll_point_append(&l, out);
        return l;
    }
    door = _get_door(tree);

    if (is_door_on_rect(in, tree->left_child) && is_door_on_rect(out, tree->right_child))
    {
        l = _solution(tree->left_child, in, door);
        dll_point_concat(&l, _solution(tree->right_child, door, out));
    }
    else if (is_door_on_rect(in, tree->right_child) && is_door_on_rect(out, tree->left_child))
    {
        l = _solution(tree->right_child, in, door);
        dll_point_concat(&l, _solution(tree->left_child, door, out));
    }
    else if (is_door_on_rect(in, tree->left_child) && is_door_on_rect(out, tree->left_child))
    {
        l = _solution(tree->left_child, in, out);
    }
    else
    {
        l = _solution(tree->right_child, in, out);
    }
    return l;
}

void free_maze(struct node_t *tree);

/** returned list must be manually freed*/
struct dll_point_t *solution(struct node_t *tree)
{
    struct point_t in = {.x = 0.5, .y = 0};
    struct point_t out = {.x = (float)tree->width - 0.5, .y = (float)tree->height};
    struct dll_point_t *soluce = NULL;
    dll_point_append(&soluce, in);

    dll_point_concat(&soluce, _solution(tree, in, out));

    return soluce;
}

/** returns a string that draws a maze solution in a svg file. */

char *solution_str(struct node_t *tree)
{

    struct dll_point_t *l = solution(tree);
    char pattern[] = "<line x1=\" %f\" y1=\" %f\" x2=\" %f\" y2=\" %f\" style=\"stroke:rgb(0,100,0);stroke-width:0.2\"/>\n";

    int l_length = 0;
    for (struct dll_point_t *e = l; 1; e = e->next)
    {
        l_length++;

        if (e->next == l)
        {
            break;
        }
    }

    char *sol_str = malloc(sizeof(char) * ((strlen(pattern) + 30 * 4) * l_length + 1));
    sol_str[0] = '\0';

    for (struct dll_point_t *e = l; 1; e = e->next)
    {
        char str_line[strlen(pattern) + 30 * 4];

        sprintf(str_line, pattern, e->pvalue->x, e->pvalue->y, e->next->pvalue->x, e->next->pvalue->y);

        strcat(sol_str, str_line);

        if (e->next->next == l)
        {
            break;
        }
    }
    dll_point_free(&l);
    return sol_str;
}

void solution_svg(char file_name[], struct node_t *tree)
{
    char *sol_str = solution_str(tree);

    FILE *fp = fopen(file_name, "a");

    fprintf(fp, "%s", sol_str);
    free(sol_str);
    free_maze(tree);
}

static void _free_maze(struct node_t *tree)
{
    struct node_t *left = tree->left_child;
    struct node_t *right = tree->right_child;

    free(tree);
    if (left == NULL && right == NULL)
    {
        return;
    }

    free_maze(left);
    free_maze(right);
}

void free_maze(struct node_t *tree)
{
    _free_maze(tree);
}