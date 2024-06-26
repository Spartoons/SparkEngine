#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#ifndef SCALEWINDOW_h_
#define SCALEWINDOW_h_

#define SCREEN_WIDTH 10
#define SCREEN_HEIGHT 10
#define WINDOW_SCALE 40  // Scale the window size for better visibility

void print_pixel(int x, int y, SDL_Renderer* renderer, int color);

#endif /* SCALEWINDOW_h_ */