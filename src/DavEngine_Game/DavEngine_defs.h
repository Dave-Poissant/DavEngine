#ifndef _DAVENGINE_DEFS_H_
#define _DAVENGINE_DEFS_H_

#include "SDL.h"
#include "SDL_image.h"

struct App {
	SDL_Renderer* renderer = nullptr;
	SDL_Window* window = nullptr;
};

struct TextureEntity {
	int x = 0;
	int y = 0;
	SDL_Texture* texture = nullptr;
};

#define REFRESH_RATE 16 // Refresh rate of the screen in main while loop

#endif // !_DAVENGINE_DEFS_H_
