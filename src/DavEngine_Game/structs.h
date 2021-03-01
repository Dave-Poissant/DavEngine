#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#include "SDL.h"

struct App{
	SDL_Renderer* renderer = nullptr;
	SDL_Window* window = nullptr;
};

#endif // !_STRUCTS_H_
