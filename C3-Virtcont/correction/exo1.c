#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
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

    int fd = open("./part.dat", O_CREAT | O_WRONLY, 0600);

    if(fd < 0)
    {
        perror("fd");
        return 1;
    }

    /**************************
     * WRITE DATA TO THE FILE *
     **************************/

    size_t to_write = sizeof(struct particle) * NUM_PART;
    size_t written = 0;

    while(to_write != written)
    {
        int ret = write(fd, part + written, to_write - written);

        if(ret < 0)
        {
            if(errno = EINTR)
            {
                continue;
            }
        
            perror("write");
            return 1;
        }

        written += ret;
    }


    /***************
     * FREE THINGS *
     ***************/

    close(fd);

    free(part);

    return 0;
}