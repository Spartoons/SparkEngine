#include "character.h"
#include <stdio.h>

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

Character loadCharacter(const char* path, SDL_Renderer* renderer, int x, int y) {
    Character character;
    character.texture = loadTexture(path, renderer);
    if (character.texture == NULL) {
        printf("Failed to load character texture!\n");
    }
    SDL_QueryTexture(character.texture, NULL, NULL, &character.width, &character.height);
    character.x = x;
    character.y = y;
    return character;
}

void renderCharacter(SDL_Renderer* renderer, Character* character, int width, int height) {
    SDL_Rect renderQuad = { character->x, character->y, width, height };
    SDL_RenderCopy(renderer, character->texture, NULL, &renderQuad);
}
