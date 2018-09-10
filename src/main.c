#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "laby.h"

int main(void)
{
    struct node_t *tree;
    
    tree = maze_gen(30,30);
    //print_tree(tree);
    maze_svg(tree);

    return(0);

}