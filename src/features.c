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
    printf("Couleur du premier pixel: %d, %d, %d\n ",r,g,b);
}

void max_component(char *source_path, char component){
    int width , height, nbChannels;
    unsigned char *data;

    if(read_image_data(source_path, &data, &width, &height, &nbChannels)){
        int max_component_value=0;
        int max_x = 0;
        int max_y = 0;

            int y,x;
            for(y = 0;y < height; y++){
                for(x=0;x < width; x++){
                    int pixel_index =(y*width +x)*nbChannels;
                    int R=data[pixel_index];
                    int G=data[pixel_index + 1];
                    int B=data[pixel_index + 2];
                    int component_value;

                    if (component == 'R' || component =='r') {
                        component_value = R;
                    }else if (component == 'G' || component =='g'){
                        component_value = G;
                    }else if (component == 'B' || component =='b'){
                        component_value = B;
                    }else {
                        printf("option de composante invalide.\n");
                        return;
                    }
                    if (component_value > max_component_value){
                        max_component_value = component_value;
                        max_x = x;
                        max_y = y;
                    }
                }
            }
            int max_pixel_index = (max_y *width + max_x)* nbChannels;
            int max_R = data[max_pixel_index];
            int max_G = data[max_pixel_index + 1];
            int max_B = data[max_pixel_index + 2];

            printf("max_component %c (%d, %d): %d\n", component, max_x, max_y, max_component_value);
    }
}