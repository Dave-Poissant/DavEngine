#ifndef _DAVENGINE_DEFS_H_
#define _DAVENGINE_DEFS_H_

#include <string>

#include "SDL.h"
#include "SDL_image.h"

#define REFRESH_RATE 16 // Refresh rate of the screen in main while loop

#define PLAYER_SPEED          4
#define PLAYER_BULLET_SPEED   16

#define MAX_KEYBOARD_KEYS 350

struct App {
	SDL_Renderer* renderer;
	SDL_Window* window;
	int keyboard[MAX_KEYBOARD_KEYS];
};

struct Entity {
	std::string entityId;
	float x;
	float y;
	int w;
	int h;
	float dx;
	float dy;
	int health;
	int reload;
	SDL_Texture* texture;
	Entity* next;
};

struct Stage {
	Entity fighterHead;
	Entity* fighterTail;
	Entity bulletHead;
	Entity* bulletTail;
};

#endif // !_DAVENGINE_DEFS_H_
