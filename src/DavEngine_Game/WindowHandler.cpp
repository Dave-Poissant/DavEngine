#include <iostream>

#include "WindowHandler.h"
#include "DavEngine_defs.h"

void WindowHandler::PrepareWindow(App* a_app)
{
	SDL_SetRenderDrawColor(a_app->renderer, 96, 128, 255, 255);
	SDL_RenderClear(a_app->renderer);
}

void WindowHandler::PresentWindow(App* a_app)
{
	SDL_RenderPresent(a_app->renderer);
}

SDL_Texture* WindowHandler::loadTexture(char* a_filename, App* a_app)
{
	SDL_Texture* texture;
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", a_filename);
	texture = IMG_LoadTexture(a_app->renderer, a_filename);
	if (texture == nullptr)
	{
		std::cout << "WindowHandler::loadTexture()::texture pointer is null" << std::endl;
	}
	return texture;
}

void WindowHandler::blit(TextureEntity* a_textureEntity, App* a_app)
{
	SDL_Rect dest;
	dest.x = a_textureEntity->x;
	dest.y = a_textureEntity->y;

	if (SDL_QueryTexture(a_textureEntity->texture, nullptr, nullptr, &dest.w, &dest.h) == -1)
	{
		if (a_textureEntity->texture == nullptr)
		{
			//std::cout << "WindowHandler::blit()::SDL_Querytexture()::texture pointer is null" << std::endl;
		}
	}

	if (SDL_RenderCopy(a_app->renderer, a_textureEntity->texture, nullptr, &dest) == -1)
	{
		if (a_textureEntity->texture == nullptr)
		{
			//std::cout << "WindowHandler::blit()::SDL_RenderCopy()::texture pointer is null" << std::endl;
		}
	}

	
}
