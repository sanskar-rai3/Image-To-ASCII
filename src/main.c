#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize2.h"

#include <stdio.h>
#include <string.h>

#define FILENAME "../image/shiroko.png"
#define WIDTH 240
#define HEIGHT 80

const char *brightness_scale = " .,~+-*#&8%@$"; 

void clearScreen(void);

int main(int argc, char *argv[]) {
    int width, height, channels;
    const int FORCED_CHANNEL = 3;
    unsigned char *data = stbi_load(FILENAME, &width, &height, &channels, FORCED_CHANNEL);
    if (data == NULL) {
        perror("Failed to load image");
        printf("Make sure you're in the build directory while running the program\n");
        return -1;
    }

    int new_width = WIDTH, new_height = HEIGHT;
    unsigned char *resized_data = malloc(FORCED_CHANNEL * WIDTH * HEIGHT);

    stbir_resize_uint8_srgb(data, width, height, 0, resized_data, new_width, new_height, 0, FORCED_CHANNEL);

    clearScreen();
    for (int y = 0; y < new_height; y++) {
        for (int x = 0; x < new_width; x++) {
            int rgb_index = 3 * (y * new_width + x);
            unsigned char r = resized_data[rgb_index + 0];
            unsigned char g = resized_data[rgb_index + 1];
            unsigned char b = resized_data[rgb_index + 2];

            float brightness = 0.299*r + 0.587*g + 0.114*b;
            int len = strlen(brightness_scale);
            int brightness_index = ((brightness / 255.0) * (len - 1));
            if (brightness_index < 0) brightness_index = 0;
            if (brightness_index >= len) brightness_index = len - 1;

            printf("\033[38;2;%d;%d;%dm%c\033[0m", r, g, b, brightness_scale[brightness_index]);
        }

        putchar('\n');
    }

    free(resized_data);
    stbi_image_free(data);
    return 0;
}

void clearScreen(void) {
    printf("\033[2J\033[H");
    fflush(stdout);
}
