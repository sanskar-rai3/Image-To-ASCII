# Image-To-ASCII

A lightweight C program that converts images into ASCII art using `stb_image` and `stb_image_resize`.

---

## Features

- Load common image formats (PNG, JPG, etc.)
- Resize images to custom dimensions
- Convert image pixels into ASCII characters
- **Colorized ASCII output (ANSI terminal colors)**
- Fast, minimal, dependency-light C implementation
- CLI-based usage

---

## Requirements

- GCC or any C99-compatible compiler
- `make` (optional)
- Linux / macOS / Windows (MinGW or WSL works)
- Terminal with ANSI color support

---

## Build

Using `make`:

```bash
make
```

Or manually:

```bash
gcc -Wall -std=c99 -lm -Iinclude/ src/main.c -o main
```

---

## Usage

```bash
./main <width> <height> <image_path>
```

### Example

```bash
./main 120 60 image.jpg
```

- `width` → ASCII output width  
- `height` → ASCII output height  
- `image_path` → path to input image  

---

## How it works

- Loads image using `stb_image`
- Resizes it using `stb_image_resize`
- Extracts pixel brightness + color
- Maps brightness to ASCII characters
- Applies ANSI color codes per pixel
- Prints colored ASCII art in terminal

---

## ASCII Palette

Dark → light mapping:

```
@ # % * + = - : .
```

---

## Color Output

The output uses ANSI escape codes to preserve original image colors in the terminal.

> Works best on modern terminals (Windows Terminal, GNOME Terminal, Alacritty, Kitty, etc.)

---

## License

This project is licensed under the MIT License.

Full license text is available in the 'LICENSE' file.