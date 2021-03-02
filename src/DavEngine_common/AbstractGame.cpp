#include "IGame.h"

AbstractGame::AbstractGame() : IGame()
{
	std::cout << "- AbstractGame::AbstractGame() -" << std::endl;
}

void AbstractGame::Initialize()
{
	std::cout << "- AbstractGame::Initialize() -" << std::endl;
}

WindowHandler* AbstractGame::GetWindowHandler()
{
	return nullptr;
}
