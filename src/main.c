#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize2.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOVE_CURSOR_TOP   "\033[H"
#define CLEAR_FROM_CURSOR "\033[0J"
#define SWAP_BUFFER       "\033[?1049h"
#define RETURN_BUFFER     "\033[?1049l"


void clearBuffer(void) {
    printf(MOVE_CURSOR_TOP);
    printf(CLEAR_FROM_CURSOR);
}

void swapBuffer(void) {
    printf(SWAP_BUFFER);
}

void returnBuffer(void) {
    printf(RETURN_BUFFER);
}

const char *brightness_scale = " .,-~+=&%#$@$"; 

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("error: Usage: %s <width> <height> <image_path>\n", argv[0]);
        return -1;
    }
    const int WIDTH      = atoi(argv[1]);
    const int HEIGHT     = atoi(argv[2]);
    const char *img_path = argv[3];

    int width, height, channels;
    const int FORCED_CHANNEL = 3;
    unsigned char *data = stbi_load(img_path, &width, &height, &channels, FORCED_CHANNEL);
    if (!data) {
        fprintf(stderr, "Failed to load image: %s\n", stbi_failure_reason());
        return -1;
    }

    int new_width  = WIDTH;
    int new_height = HEIGHT;

    unsigned char *resized_data = malloc(FORCED_CHANNEL * WIDTH * HEIGHT);
    if (!resized_data) {
        fprintf(stderr, "Failed to allocate memory\n");
        return -1;
    }
    
    stbir_resize_uint8_srgb(data, width, height, 0, resized_data, new_width, new_height, 0, FORCED_CHANNEL);

    swapBuffer();
    clearBuffer();

    int len = strlen(brightness_scale);
    for (int y = 0; y < new_height; y++) {
        for (int x = 0; x < new_width; x++) {
            int rgb_index   = 3 * (y * new_width + x);
            unsigned char r = resized_data[rgb_index + 0];
            unsigned char g = resized_data[rgb_index + 1];
            unsigned char b = resized_data[rgb_index + 2];

            float brightness = 0.299*r + 0.587*g + 0.114*b;
            int brightness_index = ((brightness / 255.0) * (len - 1));

            if (brightness_index < 0)    brightness_index = 0;
            if (brightness_index >= len) brightness_index = len - 1;

            printf("\033[38;2;%d;%d;%dm%c\033[0m", r, g, b, brightness_scale[brightness_index]);
        }

        putchar('\n');
    }

    getchar(); // Wait till user presses enter
    free(resized_data);
    stbi_image_free(data);
    returnBuffer();
    return 0;
}