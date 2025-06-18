#include <estia-image.h>
#include <stdio.h>

#include "features.h"
#include "utils.h"

/**
 * @brief Here, you have to code features of the project.
 * Do not forget to commit regurlarly your changes.
 * Your commit messages must contain "#n" with: n = number of the corresponding feature issue.
 * When the feature is totally implemented, your commit message must contain "close #n".
 */

void helloWorld() {
    printf("Hello World !");
}

void dimension(char* filename) {
    unsigned char* data;
    int width, height, channel_count;
    if (read_image_data(filename, &data, &width, &height, &channel_count) == 0) {
        printf("Erreur avec le fichier: %s\n", filename);
        return;
    }
    printf("Dimensions: %d %d\n", width, height);
    free_image_data(data);
}

void first_pixel (char *filename){
    unsigned char* data;
    int width, height, channel_count;
    if (read_image_data(filename, &data, &width, &height, &channel_count) == 0) {
        printf("Erreur avec le fichier: %s\n", filename);
        return;
    }
    int r=data[0];
    int g=data[1];
    int b=data[2];
    printf("firt_pixel: %d, %d, %d\n ",r,g,b);
}

void tenth_pixel (char *filename){
    unsigned char* data;
    int width, height, channel_count;
    if (read_image_data(filename, &data, &width, &height, &channel_count) == 0) {
        printf("Erreur avec le fichier: %s\n", filename);
        return;
    }
    int r=data[27];
    int g=data[28];
    int b=data[29];
    printf("tenth_pixel: %d, %d, %d\n ",r,g,b);
}

void color_desaturate(char *source_path) {
    int width, height, channel_count;
    unsigned char *data;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    unsigned char *new_data = (unsigned char *)malloc(width * height * channel_count * sizeof(unsigned char));
    if (new_data == NULL) {
        printf("Allocation à la mémoire échoué.\n");
        return;
    }
    int i = 0;
    while (i < width * height) {
        pixelRGB *pixel = (pixelRGB *)(data + i * channel_count);
        unsigned char min_value = pixel->R;
        if (pixel->G < min_value) {
            min_value = pixel->G;
        }
        if (pixel->B < min_value) {
            min_value = pixel->B;
        }
        unsigned char max_value = pixel->R;
        if (pixel->G > max_value) {
            max_value = pixel->G;
        }
        if (pixel->B > max_value) {
            max_value = pixel->B;
        }
        unsigned char new_value = (min_value + max_value) / 2;
        new_data[i * channel_count] = new_value;
        new_data[i * channel_count + 1] = new_value;
        new_data[i * channel_count + 2] = new_value;
        i++;
    }
    write_image_data("image_out.bmp", new_data, width, height);
    
}


void color_gray_luminance(char*source_path) {
    int width, height, nbChannels;
    unsigned char*data;

    read_image_data(source_path, &data, &width, &height, &nbChannels);

    for (int y=0; y<height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned char red   = data[y * width * 3 + x * 3];
            unsigned char green = data[y * width * 3 + x * 3 + 1];
            unsigned char blue  = data[y * width * 3 + x * 3 + 2];
            unsigned char gray  = (unsigned char)(0.21 * red + 0.72 * green + 0.07 * blue);

            data[y * width * 3 + x * 3]     = gray;
            data[y * width * 3 + x * 3 + 1] = gray;
            data[y * width * 3 + x * 3 + 2] = gray;
        }
    }

    write_image_data("image_out.bmp", data, width, height);

    free(data);
}