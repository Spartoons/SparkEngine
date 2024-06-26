#include "scalewindow.h"

void print_pixel(int x, int y, SDL_Renderer* renderer, int color){
    // Draw a white pixel at (x, y)

    //COLOR
    switch (color)
    {
    case 0: // 0 -  RED:     0xFF, 0x00, 0x00, 0x00
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
        break;
    case 1: // 1 -  PINK:    0xFF, 0x00, 0xFF, 0x00
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0x00);
        break;
    case 2: // 2 -  YELLOW:  0xFF, 0xFF, 0x00, 0x00
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0x00);
        break;
    case 3: // 3 -  GREEN:   0x00, 0xFF, 0x00, 0x00
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00);
        break;
    case 4: // 4 -  BLUE:    0x00, 0x00, 0xFF, 0x00
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0x00);
        break;
    case 5: // 5 -  PURPLE:  0xBB, 0x00, 0xFF, 0x00
        SDL_SetRenderDrawColor(renderer, 0xBB, 0x00, 0xFF, 0x00);
        break;
    case 6:// 6 -  ORANGE:  0xFF, 0xA0, 0x00, 0x00
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xA0, 0x00, 0x00);
        break;
    case 7: // 7 -  WHITE:   0xFF, 0xFF, 0xFF, 0x00
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);
        break;
    case 8: // 8 -  BLACK:   0x00, 0x00, 0x00, 0x00
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        break;
    
    default:
        break;
    }
    

    SDL_Rect pixel1 = { x*WINDOW_SCALE, y*WINDOW_SCALE, WINDOW_SCALE, WINDOW_SCALE }; // First two parameter x and y of the upper left corner os the rectangle, the last two are base and height of the rectangle
    SDL_RenderFillRect(renderer, &pixel1);
}

