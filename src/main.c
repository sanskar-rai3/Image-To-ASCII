#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <stdio.h>
#include <string.h>

#define FILENAME "../image/ado-chibi.png"

const char *brightness_scale = " .,~+-*#&8%@$"; 

void clearScreen(void);

int main(int argc, char *argv[]) {
    const char *filename = FILENAME;
    int width, height, channels;

    unsigned char *data = stbi_load(filename, &width, &height, &channels, 3);
    clearScreen();
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int rgb_index = 3 * (y * width + x);
            unsigned char r = data[rgb_index + 0];
            unsigned char g = data[rgb_index + 1];
            unsigned char b = data[rgb_index + 2];

            float brightness = 0.299*r + 0.587*g + 0.114*b;
            int len = strlen(brightness_scale);
            int brightness_index = (brightness / 255.0) * (len - 1);
            if (brightness_index < 0) brightness_index = 0;
            if (brightness_index >= len) brightness_index = len - 1;

            printf("\033[38;2;%d;%d;%dm%c\033[0m", r, g, b, brightness_scale[brightness_index]);
        }

        putchar('\n');
    }

    
    stbi_image_free(data);
    return 0;
}

void clearScreen(void) {
    printf("\033[2J\033[H");
    fflush(stdout);
}

// \033[38;2;<r>;<g>;<b>m

