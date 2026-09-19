
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 

typedef struct {
    int width;
    int height;
    int channels;
    size_t nbytes;              
    unsigned char *px;
} Image;

static Image *image_new(int width, int height, int channels) {
    if(width <= 0 || height <= 0 || channels <= 0)
        return NULL; 
    
    if(width > SIZE_MAX / height)
        return NULL;

    size_t area = (size_t)width * height;

    if(area > SIZE_MAX / channels)
        return NULL;

    size_t res = (size_t)area * channels;

    // if(res > 2600000000)
    //     return NULL; 

    Image *img = malloc(sizeof(*img));
    if(!img) { perror("malloc"); exit(1); }
    
    img->width = width;
    img->height = height;
    img->channels = channels;

    img->nbytes = res;
    img->px = malloc(img->nbytes);

    if (!img->px){ 
        free(img);
        perror("malloc px"); exit(1); 
    }
    return img;
}

static void image_fill(Image *img, unsigned char value) {
    for (size_t i = 0; i < img->nbytes; i++){
        img->px[i] = value;                     
    }
}

int main(void) {

    
    Image *img = image_new(65536, 65536, 4);
    if(img == NULL) {
        printf("invalid input");
        return 0;
    }
    printf("allocated nbytes(int)=%zu for %dx%d x%d\n",
           img->nbytes, img->width, img->height, img->channels);

    image_fill(img, 0xFF);                       

    printf("px[0]=%u\n", img->px[0]);
    free(img->px);
    free(img);
    return 0;
}
