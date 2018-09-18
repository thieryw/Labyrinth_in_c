#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "laby.h"

int main(void)
{
    struct node_t *maze;
    int width,height;
    char str[10];
    char file_name[14];

    printf("type in width and height : ");
    scanf("%d %d",&width,&height);
    printf("type in svg file name : ");
    scanf("%s",str);
    sprintf(file_name,"%s.svg",str);

    
    
    maze = maze_gen(width,height);
    maze_svg(maze,file_name);


    solution_svg(file_name,maze);


   







    return(0);

}