#include "ppm.h"

int main(int argc, char **argv)
{
	struct ppm_image im;

	ppm_image_init(&im, 1024, 768);

	int i, j;

	for( i = 0 ; i < 1024; i++)
		for(j =0 ; j < 768; j++)
			ppm_image_setpixel(&im, i, j, i%255, j%255, (i+j)%255); 


	ppm_image_dump(&im, "img.ppm");

	ppm_image_release(&im);

	return 0;
}
