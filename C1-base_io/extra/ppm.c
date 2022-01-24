#include "ppm.h"
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
 
int ppm_image_init( struct ppm_image *im , int w , int h )
{
    memset( im, 0, sizeof( struct ppm_image));
 
    im->width = w;
    im->height = h;
 
    im->px = malloc( w * h * sizeof(struct ppm_pixel));
 
    if( !im->px)
    {
        perror("malloc");
        return 1;
    }
 
    return 0;
}
 
int ppm_image_release( struct ppm_image *im )
{
    if( im == NULL )
        return 1;
 
    free( im->px );
    im->px = NULL;
 
    im->width = 0;
    im->height = 0;
 
    return 0;
}
 
int ppm_image_dump( struct ppm_image *im, char * path )
{
    FILE * out = fopen( path , "w");
 
    if( !out )
    {
        perror("fopen");
        return 1;
    }
 
    fprintf(out, "P6\n");
    fprintf(out, "%d\n", im->width);
    fprintf(out, "%d\n", im->height);
    fprintf(out, "255\n");
    fwrite( im->px, sizeof(struct ppm_pixel) , im->width * im->height, out );
 
    fclose( out );
 
    return 0;
}
