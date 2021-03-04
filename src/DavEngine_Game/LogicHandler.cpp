#include <deque>
#include <string>

#include "LogicHandler.h"
#include "DavEngine.h"

LogicHandler::LogicHandler(App* a_app) : m_app(a_app)
{

}

LogicHandler::~LogicHandler()
{

}

void LogicHandler::Logic()
{
	DoPlayer();

	DoBullets();
}

void LogicHandler::DoPlayer()
{
	Entity* player = IGame::Instance()->GetWindowHandler()->GetPlayerEntity();

	player->dx = player->dy = 0;

	if (player->reload > 0)
	{
		player->reload--;
	}

	if (m_app->keyboard[SDL_SCANCODE_UP])
	{
		player->dy = -PLAYER_SPEED;
	}

	if (m_app->keyboard[SDL_SCANCODE_DOWN])
	{
		player->dy = PLAYER_SPEED;
	}

	if (m_app->keyboard[SDL_SCANCODE_LEFT])
	{
		player->dx = -PLAYER_SPEED;
	}

	if (m_app->keyboard[SDL_SCANCODE_RIGHT])
	{
		player->dx = PLAYER_SPEED;
	}

	if (m_app->keyboard[SDL_SCANCODE_LCTRL] && player->reload == 0)
	{
		IGame::Instance()->GetWindowHandler()->FireBullet();
	}

	player->x += player->dx;
	player->y += player->dy;
}

void LogicHandler::DoBullets()
{
	std::deque<Entity*>* bulletDeque = IGame::Instance()->GetWindowHandler()->GetBulletDeque();

	size_t i = 1;
	while (i <= bulletDeque->size() && !bulletDeque->empty())
	{
		Entity* tempEntity = bulletDeque->at(bulletDeque->size() - i);
		tempEntity->x += tempEntity->dx;
		tempEntity->y += tempEntity->dy;

		if (tempEntity->x > SCREEN_WIDTH)
		{
			tempEntity = nullptr;
			bulletDeque->pop_back();
		}
		i++;
	}
}
