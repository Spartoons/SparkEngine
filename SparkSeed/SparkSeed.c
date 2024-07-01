#include "scalewindow.h"
#include "scalewindow.c"
#include "character.c"

// Function declarations
void renderMap(SDL_Renderer* renderer, int map[SCREEN_HEIGHT][SCREEN_WIDTH]);

int main(int argc, char* argv[]) {
    // Initialize:
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

    // Load character
    Character character = loadCharacter("character.png", renderer, 100, 100);

    int running = 1;
    SDL_Event e;

    while (running) {
        // Handle events
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);

        // Render the background image
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        // Render the character
        renderCharacter(renderer, &character, 200, 200);

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(character.texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
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