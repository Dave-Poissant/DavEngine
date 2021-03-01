#include "input.h"
#include <SDL.h>

void input::doInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			exit(0); // TODO: Create exception class to throw handled exceptions
			break;

		default:
			break;
		}
	}
}
