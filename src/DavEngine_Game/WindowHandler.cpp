#include <iostream>

#include "WindowHandler.h"
#include "DavEngine_defs.h"

WindowHandler::WindowHandler(int a_width, int a_height, App* a_app, Stage* a_stage) : m_width(a_width), m_height(a_height), m_app(a_app), m_stage(a_stage)
{
	m_bulletTexture = nullptr;
}

WindowHandler::~WindowHandler()
{
	if (m_stage != nullptr)
	{
		delete m_stage;
		m_stage = 0;
	}

	if (m_bulletTexture != nullptr)
	{
		m_bulletTexture = nullptr;
	}

	std::map<std::string, Entity*>::iterator it;
	for (it = textureEntitysMap.begin(); it != textureEntitysMap.end(); it++)
	{
		if (it->second != nullptr)
		{
			delete it->second;
			it->second = 0;
		}
		textureEntitysMap.erase(it);
	}
}

void WindowHandler::InitializeTexture()
{
	InitPlayer();
	InitBullet();
}

void WindowHandler::InitPlayer()
{
	Entity* player = new Entity();
	memset(player, 0, sizeof(Entity));

	m_stage->fighterTail->next = player;
	m_stage->fighterTail = player;
	player->x = 100;
	player->y = 100;
	player->entityId = (std::string)"PLAYER";

	std::string playerFilename = "C:\\Users\\davep\\Desktop\\DavEngine\\gfx\\player.png";
	player->texture = LoadTexture((char*)playerFilename.c_str());
	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
	std::cout << player->entityId.c_str() << std::endl;
	textureEntitysMap.insert(std::pair<std::string, Entity*>(player->entityId, player)); // Not sure if this is usefull
}

void WindowHandler::InitBullet()
{
	std::string bulletFilename = "C:\\Users\\davep\\Desktop\\DavEngine\\gfx\\playerBullet.png";
	m_bulletTexture = LoadTexture((char*)bulletFilename.c_str());
}

void WindowHandler::PrepareWindow()
{
	SDL_SetRenderDrawColor(m_app->renderer, 96, 128, 255, 255);
	SDL_RenderClear(m_app->renderer);
}

void WindowHandler::PresentWindow()
{
	SDL_RenderPresent(m_app->renderer);
}

SDL_Texture* WindowHandler::LoadTexture(char* a_filename)
{
	SDL_Texture* texture;
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", a_filename);
	texture = IMG_LoadTexture(m_app->renderer, a_filename);
	if (texture == nullptr)
	{
		std::cout << "WindowHandler::loadTexture()::texture pointer is null" << std::endl;
	}
	return texture;
}

void WindowHandler::Blit(Entity* a_entity)
{
	SDL_Rect dest;
	dest.x = (int)a_entity->x;
	dest.y = (int)a_entity->y;

	SDL_QueryTexture(a_entity->texture, nullptr, nullptr, &dest.w, &dest.h);
	SDL_RenderCopy(m_app->renderer, a_entity->texture, nullptr, &dest);
}

void WindowHandler::Draw()
{
	DrawPlayer();
	DrawBullets();
}

void WindowHandler::DrawPlayer()
{
	std::map<std::string, Entity*>::iterator it;
	it = textureEntitysMap.find("PLAYER");
	if (it != textureEntitysMap.end())
	{
		Blit(it->second);
	}
	
}

void WindowHandler::DrawBullets()
{
	Entity* b;

	for (b = m_stage->bulletHead.next; b != NULL; b = b->next)
	{
		Blit(b);
	}
}

void WindowHandler::FireBullet()
{
	Entity* bullet = new Entity();
	memset(bullet, 0, sizeof(Entity));

	m_stage->bulletTail->next = bullet;
	m_stage->bulletTail = bullet;

	std::map<std::string, Entity*>::iterator it;
	it = textureEntitysMap.find("PLAYER");

	if (it == textureEntitysMap.end())
	{
		std::cout << "Couldn't find PLAYER entity for FireBullet()" << std::endl;
		return;
	}
	
	auto bulletNumber = std::to_string(textureEntitysMap.size() - 1); // size() should be at least 1 with "PLAYER" in it

	bullet->entityId = (std::string)("BULLET" + bulletNumber);
	std::cout << bullet->entityId << std::endl;
	bullet->x = it->second->x;
	bullet->y = it->second->y;
	bullet->dx = PLAYER_BULLET_SPEED;
	bullet->health = 1;
	bullet->texture = m_bulletTexture;

	textureEntitysMap.insert(std::pair<std::string, Entity*>(bullet->entityId, bullet)); // Not sure if this is usefull

	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

	bullet->y += (it->second->h / 2) - (bullet->h / 2);

	it->second->reload = 8;
}

std::map<std::string, Entity*>* WindowHandler::GetEntityMap()
{
	return &textureEntitysMap;
}
