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

    /********************
     * READING THE FILE *
     ********************/

    int fd = open("./part.dat", O_CREAT | O_RDONLY, 0600);

    if(fd < 0)
    {
        perror("fd");
        return 1;
    }

    /**************************
     * WRITE DATA TO THE FILE *
     **************************/

    size_t to_read = sizeof(struct particle) * NUM_PART;
    size_t didread = 0;

    while(to_read != didread)
    {
        int ret = read(fd, part + didread, to_read - didread);

        if(ret < 0)
        {
            if(errno = EINTR)
            {
                continue;
            }
        
            perror("read");
            return 1;
        }

        didread += ret;
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

    close(fd);

    free(part);

    return 0;
}