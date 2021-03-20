#include <iostream>

#include "WindowHandler.h"
#include "DavEngine.h"
#include "DavEngine_defs.h"
#include "DavEngine_common/Game_defs.h"
#include "DavEngine_common/common/utils/Math_utils.h"

WindowHandler::WindowHandler(int a_width, int a_height, App* a_app) : m_width(a_width), m_height(a_height), m_app(a_app)
{
	m_bulletTexture = nullptr;
	m_enemyBulletTexture = nullptr;
	m_enemyTexture = nullptr;
	m_playerEntity = nullptr;
	m_resetGameTimer = 0;
	m_mathUtilsObj = new MathUtils();
}

WindowHandler::~WindowHandler()
{

	if (m_mathUtilsObj != nullptr)
	{
		delete m_mathUtilsObj;
		m_mathUtilsObj = nullptr;
	}

	if (m_bulletTexture != nullptr)
	{
		m_bulletTexture = nullptr;
	}

	if (m_enemyBulletTexture != nullptr)
	{
		m_enemyBulletTexture = nullptr;
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

	while (!m_ennemyEntitysDeque.empty())
	{
		Entity* tempEntity = m_ennemyEntitysDeque.back();
		tempEntity = nullptr;
		m_ennemyEntitysDeque.pop_back();
	}

	while (!m_enemyBulletEntitysDeque.empty())
	{
		Entity* tempEntity = m_enemyBulletEntitysDeque.back();
		tempEntity = nullptr;
		m_enemyBulletEntitysDeque.pop_back();
	}
}

void WindowHandler::InitializeTexture()
{
	ResetGame();
	InitEnemy();
	InitBullet();
	InitEnemyBullet();
}

void WindowHandler::ResetGame()
{
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

	InitPlayer();

	IGame::Instance()->GetLogicHandler()->SetEnemySpawntimer(0);

	m_resetGameTimer = FPS * 2;
}

void WindowHandler::InitPlayer()
{
	Entity* player = new Entity();
	memset(player, 0, sizeof(Entity));

	player->x = 100;
	player->y = 100;

	std::string playerFilename = "C:\\Users\\davep\\Desktop\\DavEngine\\gfx\\player.png";
	player->texture = LoadTexture((char*)playerFilename.c_str());
	SDL_QueryTexture(player->texture, nullptr, nullptr, &player->w, &player->h);

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

void WindowHandler::InitEnemyBullet()
{
	std::string enemyBulletFilename = "C:\\Users\\davep\\Desktop\\DavEngine\\gfx\\alienBullet.png";
	m_enemyBulletTexture = LoadTexture((char*)enemyBulletFilename.c_str());
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
	DrawEnemyBullets();
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

void WindowHandler::DrawEnemyBullets()
{
	size_t i = 1;
	while (i <= m_enemyBulletEntitysDeque.size() && !m_enemyBulletEntitysDeque.empty())
	{
		Blit(m_enemyBulletEntitysDeque.at(m_enemyBulletEntitysDeque.size() - i));
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

	SDL_QueryTexture(bullet->texture, nullptr, nullptr, &bullet->w, &bullet->h);

	bullet->y += (m_playerEntity->h / 2) - (bullet->h / 2);

	m_playerEntity->reload = 8;
}

void WindowHandler::FireEnemyBullet(Entity* a_enemyEntity)
{
	Entity* enemyBullet = new Entity();
	memset(enemyBullet, 0, sizeof(Entity));

	enemyBullet->x = a_enemyEntity->x;
	enemyBullet->y = a_enemyEntity->y;
	enemyBullet->health = 1;
	enemyBullet->texture = m_enemyBulletTexture;
	enemyBullet->side = a_enemyEntity->side;

	m_enemyBulletEntitysDeque.push_front(enemyBullet);

	SDL_QueryTexture(enemyBullet->texture, nullptr, nullptr, &enemyBullet->w, &enemyBullet->h);
	enemyBullet->x += (a_enemyEntity->w / 2) - (enemyBullet->w / 2);
	enemyBullet->y += (a_enemyEntity->h / 2) - (enemyBullet->h / 2);

	m_mathUtilsObj->CalcSlope((int)(m_playerEntity->x + (m_playerEntity->w / 2)), (int)(m_playerEntity->y + (m_playerEntity->h / 2)),
							  (int)a_enemyEntity->x, (int)a_enemyEntity->y, &enemyBullet->dx, &enemyBullet->dy);
	enemyBullet->dx *= ALIEN_BULLET_SPEED;
	enemyBullet->dy *= ALIEN_BULLET_SPEED;

	enemyBullet->side = SIDE_ALIEN;

	a_enemyEntity->reload = (rand() % FPS * 2);
}

bool WindowHandler::BulletHitFighter(Entity* a_bulletEntity)
{
	size_t i = 1;
	while (i <= m_ennemyEntitysDeque.size() && !m_ennemyEntitysDeque.empty())
	{
		Entity* tempEntity = m_ennemyEntitysDeque.at(m_ennemyEntitysDeque.size() - i);
		if (tempEntity->side != a_bulletEntity->side &&
			m_mathUtilsObj->Collision((int)a_bulletEntity->x, (int)a_bulletEntity->y, (int)a_bulletEntity->w,
									  (int)a_bulletEntity->h, (int)tempEntity->x, (int)tempEntity->y,
									  (int)tempEntity->w, (int)tempEntity->h))
		{
			a_bulletEntity->health = 0;
			tempEntity->health = 0;

			return true;
		}
		i++;
	}

	return false;
}

void WindowHandler::CreateEnemy()
{
	Entity* enemy = new Entity();
	memset(enemy, 0, sizeof(Entity));

	enemy->x = SCREEN_WIDTH;
	enemy->y = (float)(rand() % SCREEN_HEIGHT);
	enemy->health = 1;
	enemy->texture = m_enemyTexture;
	enemy->dx = -(float)(2 + (rand() % 4));

	m_ennemyEntitysDeque.push_front(enemy);

	SDL_QueryTexture(enemy->texture, nullptr, nullptr, &enemy->w, &enemy->h);
	enemy->reload = FPS * (1 + (rand() % 3));
}

std::deque<Entity*>* WindowHandler::GetBulletDeque()
{
	return &m_bulletEntitysDeque;
}

std::deque<Entity*>* WindowHandler::GetEnemyBulletDeque()
{
	return &m_enemyBulletEntitysDeque;
}

std::deque<Entity*>* WindowHandler::GetEnemyDeque()
{
	return &m_ennemyEntitysDeque;
}

Entity* WindowHandler::GetPlayerEntity()
{
	return m_playerEntity;
}

int WindowHandler::GetGameResetTimer()
{
	return m_resetGameTimer;
}

void WindowHandler::SetGameResetTimer(int a_timer)
{
	m_resetGameTimer = a_timer;
}
