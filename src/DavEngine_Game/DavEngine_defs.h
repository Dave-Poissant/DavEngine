#ifndef _DAVENGINE_DEFS_H_
#define _DAVENGINE_DEFS_H_

#include <string>

#include "SDL.h"
#include "SDL_image.h"

#define REFRESH_RATE 16 // Refresh rate of the screen in main while loop
#define FPS 60

#define PLAYER_SPEED          4
#define PLAYER_BULLET_SPEED   16
#define ALIEN_BULLET_SPEED    5

#define MAX_KEYBOARD_KEYS 350

#define SIDE_PLAYER 0
#define SIDE_ALIEN  1

struct App {
	SDL_Renderer* renderer;
	SDL_Window* window;
	int keyboard[MAX_KEYBOARD_KEYS];
};

struct Entity {
	float x;
	float y;
	int w;
	int h;
	float dx;
	float dy;
	int health;
	int reload;
	int side;
	SDL_Texture* texture;
	Entity* next;
};

#endif // !_DAVENGINE_DEFS_H_
