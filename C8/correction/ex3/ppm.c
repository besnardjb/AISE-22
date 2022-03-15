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

struct col getcol( int val , int max )
{
	double q = (double)val/(double)max;

	struct col c = { 0, 0, 0 };

	if( q < 0.25 )
	{
		c.r = ( q * 4.0 ) * 255.0;
		c.b = 255;
	}
	else if( q < 0.5 )
	{
		c.b = 255;
		c.g = 255;
		c.r = (q-0.25)*4.0*255.0;

	}
	else if( q < 0.75 )
	{
		c.b = 255;
		c.r = 255;
		c.g = 255.0 - (q-0.5)*4.0*255.0;
	}
	else
	{
		c.b = 255-(q-0.75)*4.0*255.0;
		c.g = 0;
		c.r = 255;
	}

	return c;
}
