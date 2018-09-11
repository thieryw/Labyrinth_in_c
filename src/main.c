#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "laby.h"

int main(void)
{
    struct node_t *tree;
    int width,height;
    char str[10];
    char file_name[14];

    printf("type in width and height : ");
    scanf("%d %d",&width,&height);
    printf("type in svg file name : ");
    scanf("%s",str);
    sprintf(file_name,"%s.svg",str);

    
    
    tree = maze_gen(width,height);
    maze_svg(tree,file_name);

    free_maze(tree);

    return(0);

}