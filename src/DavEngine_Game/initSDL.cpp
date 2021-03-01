#include <iostream>

#include "initSDL.h"
#include "defs.h"
#include "structs.h"

void initSDL::initSDLObject(App* a_app)
{
	int rendererFlags, windowFlags;

	rendererFlags = SDL_RENDERER_ACCELERATED;

	windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1); // TODO: Create exception class to throw handled exceptions
	}
	a_app->window = SDL_CreateWindow("DavEngine_game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

	if (!a_app->window)
	{
		printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
		exit(1); // TODO: Create exception class to throw handled exceptions
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	a_app->renderer = SDL_CreateRenderer(a_app->window, -1, rendererFlags);

	if (!a_app->renderer)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1); // TODO: Create exception class to throw handled exceptions
	}
}
