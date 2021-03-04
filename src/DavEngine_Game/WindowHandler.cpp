#include <iostream>

#include "WindowHandler.h"
#include "DavEngine_defs.h"

WindowHandler::WindowHandler(int a_width, int a_height, App* a_app) : m_width(a_width), m_height(a_height), m_app(a_app)
{
	m_bulletTexture = nullptr;
	m_playerEntity = nullptr;
}

WindowHandler::~WindowHandler()
{
	if (m_bulletTexture != nullptr)
	{
		m_bulletTexture = nullptr;
	}

	if (m_playerEntity != nullptr)
	{
		m_playerEntity = nullptr;
	}

	while (!m_bulletEntitysDeque.empty())
	{
		Entity* tempEntity = m_bulletEntitysDeque.back();
		tempEntity = nullptr;
		m_bulletEntitysDeque.pop_back();
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

	player->x = 100;
	player->y = 100;

	std::string playerFilename = "C:\\Users\\davep\\Desktop\\DavEngine\\gfx\\player.png";
	player->texture = LoadTexture((char*)playerFilename.c_str());
	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);

	m_playerEntity = player;
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
	Blit(m_playerEntity);
}

void WindowHandler::DrawBullets()
{
	size_t i = 1;
	while (i <= m_bulletEntitysDeque.size() && !m_bulletEntitysDeque.empty())
	{
		Blit(m_bulletEntitysDeque.at(m_bulletEntitysDeque.size() - i));
		i++;
	}
}

void WindowHandler::FireBullet()
{
	Entity* bullet = new Entity();
	memset(bullet, 0, sizeof(Entity));

	bullet->x = m_playerEntity->x;
	bullet->y = m_playerEntity->y;
	bullet->dx = PLAYER_BULLET_SPEED;
	bullet->health = 1;
	bullet->texture = m_bulletTexture;

	m_bulletEntitysDeque.push_front(bullet);

	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

	bullet->y += (m_playerEntity->h / 2) - (bullet->h / 2);

	m_playerEntity->reload = 8;
}

std::deque<Entity*>* WindowHandler::GetBulletDeque()
{
	return &m_bulletEntitysDeque;
}

Entity* WindowHandler::GetPlayerEntity()
{
	return m_playerEntity;
}
