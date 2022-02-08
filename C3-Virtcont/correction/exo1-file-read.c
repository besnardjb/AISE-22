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


    /********************
     * WRITING THE FILE *
     ********************/

    FILE * file = fopen("./part.dat", "r");

    if(!file)
    {
        perror("fopen");
        return 1;
    }

    int ret = fread(part, sizeof(struct particle), NUM_PART, file);

    if(ret < 0)
    {
        perror("fread");
        return 1;
    }
   
    /*****************
     * CHECK CONTENT *
     *****************/

    int i;

    for (i = 0; i < NUM_PART; i++)
    {
        if( part[i].x != i)
        {
            fprintf(stderr, "ERROR on x %d != %d\n", part[i].x , i);
        }

        if( part[i].y != (i+1) )
        {
            fprintf(stderr, "ERROR on y %d != %d\n", part[i].x , i + 1);
        }
        
        if( part[i].z != 1337)
        {
            fprintf(stderr, "ERROR on z %d != %d\n", part[i].x , 1337);
        }

    }
    

    /***************
     * FREE THINGS *
     ***************/

    fclose(file);

    free(part);

    return 0;
}