#include <iostream>

#include "WindowHandler.h"
#include "DavEngine_defs.h"
#include "DavEngine_common/Game_defs.h"

WindowHandler::WindowHandler(int a_width, int a_height, App* a_app) : m_width(a_width), m_height(a_height), m_app(a_app)
{
	m_bulletTexture = nullptr;
	m_enemyTexture = nullptr;
	m_playerEntity = nullptr;
}

WindowHandler::~WindowHandler()
{
	if (m_bulletTexture != nullptr)
	{

		m_bulletTexture = nullptr;
	}

	if (m_enemyTexture != nullptr)
	{
		m_enemyTexture = nullptr;
	}

	if (m_playerEntity != nullptr)
	{
		delete m_playerEntity;
		m_playerEntity = nullptr;
	}

	while (!m_bulletEntitysDeque.empty())
	{
		Entity* tempEntity = m_bulletEntitysDeque.back();
		tempEntity = nullptr;
		m_bulletEntitysDeque.pop_back();
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
	InitEnemy();
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

void WindowHandler::InitEnemy()
{
	std::string enemyFilename = "C:\\Users\\davep\\Desktop\\DavEngine\\gfx\\enemy.png";
	m_enemyTexture = LoadTexture((char*)enemyFilename.c_str());
}

void WindowHandler::InitBullet()
{
	std::string bulletFilename = "C:\\Users\\davep\\Desktop\\DavEngine\\gfx\\playerBullet.png";
	m_bulletTexture = LoadTexture((char*)bulletFilename.c_str());
}

void WindowHandler::PrepareWindow()
{
	SDL_SetRenderDrawColor(m_app->renderer, 32, 32, 32, 255);
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
	DrawFighters();
	DrawBullets();
}

void WindowHandler::DrawPlayer()
{
	Blit(m_playerEntity);
}

void WindowHandler::DrawFighters()
{
	size_t i = 1;
	while (i <= m_ennemyEntitysDeque.size() && !m_ennemyEntitysDeque.empty())
	{
		Blit(m_ennemyEntitysDeque.at(m_ennemyEntitysDeque.size() - i));
		i++;
	}
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

	bullet->x = m_playerEntity->x + 5;
	bullet->y = m_playerEntity->y;
	bullet->dx = PLAYER_BULLET_SPEED;
	bullet->health = 1;
	bullet->texture = m_bulletTexture;

	m_bulletEntitysDeque.push_front(bullet);

	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

	bullet->y += (m_playerEntity->h / 2) - (bullet->h / 2);

	m_playerEntity->reload = 8;
}

void WindowHandler::CreateEnemy()
{
	Entity* enemy = new Entity();
	memset(enemy, 0, sizeof(Entity));

	enemy->x = SCREEN_WIDTH;
	enemy->y = (float)(rand() % SCREEN_HEIGHT);
	enemy->texture = m_enemyTexture;
	enemy->dx = -(float)(2 + (rand() % 4));

	m_ennemyEntitysDeque.push_front(enemy);

	SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);
}

std::deque<Entity*>* WindowHandler::GetBulletDeque()
{
	return &m_bulletEntitysDeque;
}

std::deque<Entity*>* WindowHandler::GetEnemyDeque()
{
	return &m_ennemyEntitysDeque;
}

Entity* WindowHandler::GetPlayerEntity()
{
	return m_playerEntity;
}
