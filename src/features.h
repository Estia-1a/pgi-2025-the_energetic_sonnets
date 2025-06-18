#ifndef FEATURES_H
#define FEATURES_H
void helloWorld();
void dimension(char* filename);
void first_pixel (char *source_path);
void max_component(char *source_path, char component);
#endif
void tenth_pixel (char *source_path);
void color_desaturate(char *source_path);

void read_image_data(char *filename, unsigned char **data, int *width, int *height, int *channel_count);
void write_image_data(char *filename, unsigned char *data, int width, int height);
void color_gray_luminance(char* source_path);
















void read_image_data(char* filename, unsigned char** data, int* width, int* height, int* channel_count);

void write_image_data(char* filename, unsigned char* data, int width, int height);


void color_green(char* source_path);

void read_image_data(char* filename, unsigned char** data, int* width, int* height, int* channel_count);

void write_image_data(char* filename, unsigned char* data, int width, int height);
