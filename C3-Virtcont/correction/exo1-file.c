#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

struct particle
{
    int x,y,z;
};

#define NUM_PART 128

int main(int argc, char ** argv)
{
    /********
     * INIT *
     ********/

    /* struct particle part[NUM_PART]; */
    struct particle *part = malloc(NUM_PART * sizeof(struct particle));

    if(!part)
    {
        perror("malloc");
        return 1;
    }

    int i;

    for (i = 0; i < NUM_PART; i++)
    {
        part[i].x = i;
        part[i].y = i + 1;
        part[i].z = 1337;
    }
    
    /********************
     * WRITING THE FILE *
     ********************/

    FILE * file = fopen("./part.dat", "w");

    if(!file)
    {
        perror("fopen");
        return 1;
    }

    int ret = fwrite(part, sizeof(struct particle), NUM_PART, file);

    if(ret < 0)
    {
        perror("fwrite");
        return 1;
    }
   
    /***************
     * FREE THINGS *
     ***************/

    fclose(file);

    free(part);

    return 0;
}