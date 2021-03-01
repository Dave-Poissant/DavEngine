#include "DavEngine.h"

IGame* IGame::m_game = new DavEngine();

DavEngine::DavEngine() : AbstractGame()
{
    std::cout << "- DavEngine::DavEngine() -" << std::endl;
}

void DavEngine::Initialize()
{
    AbstractGame::Initialize();
    std::cout << "- DavEngine::Initialize() -" << std::endl;
}