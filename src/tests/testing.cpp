#include "DavEngine_Game/DavEngine.h"
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"


int main()
{
    IGame::Instance()->Initialize();
    return 0;
}