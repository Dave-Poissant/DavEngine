#include <map>
#include <string>

#include "LogicHandler.h"
#include "DavEngine.h"

LogicHandler::LogicHandler(Stage* a_stage, App* a_app) : m_stage(a_stage), m_app(a_app)
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
	std::map<std::string, Entity*>::iterator it;
	it = IGame::Instance()->GetWindowHandler()->GetEntityMap()->find("PLAYER");

	if (it == IGame::Instance()->GetWindowHandler()->GetEntityMap()->end())
	{
		std::cout << "Couldn't find PLAYER entity" << std::endl;
		return;
	}

	it->second->dx = it->second->dy = 0;

	if (it->second->reload > 0)
	{
		it->second->reload--;
	}

	if (m_app->keyboard[SDL_SCANCODE_UP])
	{
		it->second->dy = -PLAYER_SPEED;
	}

	if (m_app->keyboard[SDL_SCANCODE_DOWN])
	{
		it->second->dy = PLAYER_SPEED;
	}

	if (m_app->keyboard[SDL_SCANCODE_LEFT])
	{
		it->second->dx = -PLAYER_SPEED;
	}

	if (m_app->keyboard[SDL_SCANCODE_RIGHT])
	{
		it->second->dx = PLAYER_SPEED;
	}

	if (m_app->keyboard[SDL_SCANCODE_LCTRL] && it->second->reload == 0)
	{
		IGame::Instance()->GetWindowHandler()->FireBullet();
	}

	it->second->x += it->second->dx;
	it->second->y += it->second->dy;
}

void LogicHandler::DoBullets()
{
	Entity* b, * prev;

	prev = &m_stage->bulletHead;

	for (b = m_stage->bulletHead.next; b != NULL; b = b->next)
	{
		b->x += b->dx;
		b->y += b->dy;

		if (b->x > SCREEN_WIDTH)
		{
			if (b == m_stage->bulletTail)
			{
				m_stage->bulletTail = prev;
			}

			prev->next = b->next;

			std::map<std::string, Entity*>::iterator it;
			it = IGame::Instance()->GetWindowHandler()->GetEntityMap()->find(b->entityId);
			if (it != IGame::Instance()->GetWindowHandler()->GetEntityMap()->end())
			{
				IGame::Instance()->GetWindowHandler()->GetEntityMap()->erase(it);
			}
			else
			{
				std::cout << "Couldn't find BULLET entity" << std::endl;
			}
			
			delete b;
			b = prev;
		}

		prev = b;
	}
}
