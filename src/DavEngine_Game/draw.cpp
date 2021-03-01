#include "draw.h"
#include "structs.h"

void draw::prepareScene(App* a_app)
{
	SDL_SetRenderDrawColor(a_app->renderer, 96, 128, 255, 255);
	SDL_RenderClear(a_app->renderer);
}

void draw::presentScene(App* a_app)
{
	SDL_RenderPresent(a_app->renderer);
}
