#ifndef PPM_H
#define PPM_H
 
struct ppm_pixel
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};
 
static inline void ppm_setpixel( struct ppm_pixel * px, unsigned char r , unsigned char g , unsigned char b)
{
    px->r = r;
    px->g = g;
    px->b = b;
}
 
struct ppm_image
{
    unsigned int width;
    unsigned int height;
    struct ppm_pixel * px;
};
 
int ppm_image_init( struct ppm_image *im , int w , int h );
int ppm_image_release( struct ppm_image *im );
 
static inline void ppm_image_setpixel( struct ppm_image * im, int x, int y, unsigned char r , unsigned char g , unsigned char b)
{
    struct ppm_pixel * px = im->px + im->width * y + x;
    ppm_setpixel( px, r, g, b);
}
 
int ppm_image_dump( struct ppm_image *im, char * path );
 
 
#endif /* PPM_H */
