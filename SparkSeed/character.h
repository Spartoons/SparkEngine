#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct {
    int x, y;  // Position of the character
    int width, height;  // Size of the character sprite
    SDL_Texture* texture;  // Character sprite texture
} Character;

Character loadCharacter(const char* path, SDL_Renderer* renderer, int x, int y);
void renderCharacter(SDL_Renderer* renderer, Character* character, int with, int height);

#endif /* CHARACTER_H_ */
