#include <windows.h>

#define SDL_MAIN_HANDLED
#include "DavEngine_Game/DavEngine.h"
#include "DavEngine_Game/input.h"
#include "SDL_image.h"


static void cleanup()
{
	std::cout << "static void cleanup()" << std::endl;
}

int main()
{
    IGame::Instance()->Initialize();
	input* inputObj = new input();

	atexit(cleanup);

	while (1)
	{
		IGame::Instance()->GetWindowHandler()->PrepareWindow(((DavEngine*)IGame::Instance())->GetApp());

		inputObj->doInput();

		IGame::Instance()->GetWindowHandler()->blit(((DavEngine*)IGame::Instance())->GetTextureEntity(), ((DavEngine*)IGame::Instance())->GetApp());

		IGame::Instance()->GetWindowHandler()->PresentWindow(((DavEngine*)IGame::Instance())->GetApp());

		SDL_Delay(REFRESH_RATE);
	}

	delete inputObj;

	return 0;
}