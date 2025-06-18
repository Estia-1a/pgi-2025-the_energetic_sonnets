#include <estia-image.h>
#include <stdio.h>

#include "features.h"
#include "utils.h"


void helloWorld() {
    printf("Hello World !");
}

void dimension(char* filename) {

    unsigned char* data;
    int width, height, channel_count;
    
    read_image_data(filename, &data, &width, &height, &channel_count);
    
    if (data == NULL) {
        printf("Erreur avec le fichier: %s\n", filename);
        return;
    }
}

void first_pixel (char *filename){
    unsigned char* data;
    int width, height, channel_count;
    read_image_data(filename, &data, &width, &height, &channel_count);

    if(data==NULL){
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
    read_image_data(filename, &data, &width, &height, &channel_count);
    if(data==NULL){
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
        
        unsigned char r= data[i*channel_count];
        unsigned char g= data[i*channel_count+1];
        unsigned char b= data[i*channel_count+2];

    
        unsigned char min_value = r;
        if (g < min_value)min_value=r;
        if (b < min_value)min_value=b;
        
        unsigned char max_value = r;
        if (g > max_value)max_value=g;
        if (b > max_value)max_value=b;


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

void color_green(char*source_path){
    int width, height, nbChannels;
    unsigned char *data;
    read_image_data(source_path, &data, &width, &height, &nbChannels);
    int y;
    int x;
    for(y=0; y<height; y++){
        for (x=0; x<width; x++){
            data[y*width*3+x*3] = 0;
            data[y*width*3 + x*3+2] =0;
        }
    }
    write_image_data("image_out.bmp", data, width, height);
}



void color_invert(char*source_path){
    int width, height, nbChannels;
    unsigned char *data;
    read_image_data(source_path, &data, &width, &height, &nbChannels);
    if(data == NULL)return;

    int total_pixels = width*height;
    for(int i=0;i<total_pixels;i++){
        int index=i *nbChannels;
    

            data[index]= 255-data[index];
            data[index+1]= 255-data[index+1];
             data[index+2]= 255-data[index+2];
    }
    

    write_image_data("image_out.bmp", data, width, height);
    free(data);

}


void color_red(char*source_path) {
    int width, height, nbChannels;
    unsigned char*data;
    read_image_data(source_path, &data, &width, &height, &nbChannels);
    int y;
    int x;
    for(y=0; y<height; y++){
        for (x=0; x<width; x++) {
            data[y*width*3+x*3+1]=0;
            data[y*width*3+x*3+2]=0;
        }
    }

    write_image_data("image_out.bmp", data, width, height);

}

void max_compenent(char *source_path, char component){
    int width, height, nbChannels;
    unsigned char *data;

    read_image_data(source_path, &data, &width, &height, &nbChannels);
    if(data == NULL){
        printf("erreur lors de la lecture du fichier: %s\n",source_path);
        return;
    }
    int max_component_value=0;
    int max_x=0;
    int max_y=0;
    int y, x;
    
    for(y=0; y < height; y++){
        for(x=0; x < width; x++){
            int pixel_index=(y*width+x)*nbChannels;
            int R=data[pixel_index];
            int G=data[pixel_index+1];
            int B=data[pixel_index+2];
            int component_value;
            
            if(component=='R'|| component=='r'){
                component_value= R;
            }else if(component=='G'|| component=='g'){
                component_value= G;       
            }else if(component=='B'|| component=='b'){
                component_value= B;
            }else{
                printf("option de composante invlide.\n");
                free_image_data(data);
                return;
            
            }
            if(component_value > max_component_value){
                max_component_value=component_value;
                max_x=x;
                max_y=y;
            }
       }
    }

    printf("max_component %c (%d, %d):%d\n",component, max_x,max_y,max_component_value);
    free_image_data(data);
}
void max_pixel(char*source_path){
    int width,height, nbChannels;
    unsigned char*data;
    
    read_image_data(source_path, &data, &width, &height, &nbChannels);

    if(data==NULL){
        printf("erreur lors de la lecture du fichier: %s\n", source_path);
        return;
    }
    int max_sum=0;
    int max_x=0;
    int max_y=0;
    int y, x;

    for(y=0; y<height; y++){
        for(x=0; x<width; x++){
            int pixel_index=(y*width+x)*nbChannels;
            int R=data[pixel_index];
            int G=data[pixel_index+1];
            int B=data[pixel_index+2];
            int sum= R+G+B;

            if(sum>max_sum){
                max_sum=sum;
                max_x=x;
                max_y=y;
            }

        }
    }
    int max_pixel_index=(max_y*width+max_x)*nbChannels;
    int max_R= data[max_pixel_index];
    int max_G=data[max_pixel_index+1];
    int max_B=data[max_pixel_index+2];
    printf("max_pixel (%d,%d):%d, %d\n",max_x,max_y,max_R,max_G,max_B);
    free_image_data(data);
}
void min_compenent(char *source_path, char component){
    int width, height, nbChannels;
    unsigned char *data;

    read_image_data(source_path, &data, &width, &height, &nbChannels);
    if(data == NULL){
        printf("erreur lors de la lecture du fichier: %s\n",source_path);
        return;
    }
    int min_component_value=255;
    int max_x=0;
    int max_y=0;
    int y, x;
    
    for(y=0; y < height; y++){
        for(x=0; x < width; x++){
            int pixel_index=(y*width+x)*nbChannels;
            int R=data[pixel_index];
            int G=data[pixel_index+1];
            int B=data[pixel_index+2];
            int component_value;
            
            if(component=='R'|| component=='r'){
                component_value= R;
            }else if(component=='G'|| component=='g'){
                component_value= G;       
            }else if(component=='B'|| component=='b'){
                component_value= B;
            }else{
                printf("option de composante invlide.\n");
                free_image_data(data);
                return;
            
            }
            if(component_value < min_component_value){
                min_component_value=component_value;
                max_x=x;
                max_y=y;
            }
       }
    }

    printf("max_component %c (%d, %d):%d\n",component, max_x,max_y,min_component_value);
    free_image_data(data);
}
void min_pixel(char*source_path){
    int width, height, nbChannels;
    unsigned char*data;
    read_image_data(source_path, &data, &width, &height, &nbChannels);
    int min_sum=765;
    int min_x=0;
    int min_y=0;
    int y;
    int x;
    for (y=0;y<height; y++){
        for (x=0;x<width;x++){
            int max_pixel_index=(y*width +x)*nbChannels;
            int max_R= data[max_pixel_index];
            int max_G=data[max_pixel_index+1];
            int max_B=data[max_pixel_index+2];
            int SUM=max_R+max_G+max_B;
            if (SUM<min_sum){
                min_sum=SUM;
                min_x=x;
                min_y=y;
            }

        }
    }
    int min_pixel_index=(min_y*width+min_x)*nbChannels;
    int min_R=data[min_pixel_index];
    int min_G=data[min_pixel_index+1];
    int min_B=data[min_pixel_index+2];

    printf("min_pixel(%d, %d): %d, %d, %d", min_x, min_y, min_R, min_G, min_B);
}