#include "scalewindow.h"
#include "scalewindow.c"

// Function declarations
void renderMap(SDL_Renderer* renderer, int map[SCREEN_HEIGHT][SCREEN_WIDTH]);
SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer);

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    printf("SDL_image could not initialize! IMG_Error: %s\n", IMG_GetError());
    SDL_Quit();
    return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SparkSeed",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH * WINDOW_SCALE,
                                          SCREEN_HEIGHT * WINDOW_SCALE,
                                          SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }


    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Load background image
    SDL_Texture* backgroundTexture = loadTexture("back1.jpg", renderer);
    if (backgroundTexture == NULL) {
        printf("Failed to load background texture! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    int running = 1;
    SDL_Event e;
    int x = 2;
    int y = 2;
    int color = 0;

    while (running) {


        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = 0;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        y = (y > 0) ? y - 1 : y;
                        break;
                    case SDLK_DOWN:
                        y = (y < SCREEN_HEIGHT - 1) ? y + 1 : y;
                        break;
                    case SDLK_LEFT:
                        x = (x > 0) ? x - 1 : x;
                        break;
                    case SDLK_RIGHT:
                        x = (x < SCREEN_WIDTH - 1) ? x + 1 : x;
                        break;
                    case SDLK_SPACE:
                        color = (color < 7) ? color + 1 : 0;
                        break;
                }
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);

        // Render the background image
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        print_pixel(x, y, renderer, color);

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


// Functions
void renderMap(SDL_Renderer* renderer, int map[SCREEN_HEIGHT][SCREEN_WIDTH]) {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            if (map[y][x] == 1) {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);  // White
            } else {
                SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);  // Black
            }
            SDL_Rect pixel = { x * WINDOW_SCALE, y * WINDOW_SCALE, WINDOW_SCALE, WINDOW_SCALE };
            SDL_RenderFillRect(renderer, &pixel);
        }
    }
}

SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    } else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}