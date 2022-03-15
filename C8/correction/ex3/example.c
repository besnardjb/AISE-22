#include "ppm.h"
 
 
int main(int argc, char *argv[])
{
    struct ppm_image im;
 
    ppm_image_init( &im, 1024, 1024 );
 
    int i,j;
 
    for (i = 0; i < 1024; ++i) {
            for (j = 0; j < 1024; ++j) {
                        ppm_image_setpixel( &im, i, j, i%255, j%255, (i+j)%255);
                    }
        }
 
    for (i = 0; i < 1024; ++i) {
            ppm_image_setpixel( &im, i, i, 255, 0, 0 );
        }
 
    ppm_image_dump( &im , "test.ppm");
 
    ppm_image_release( &im );
 
 
    return 0;
}
