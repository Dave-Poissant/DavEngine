#include <windows.h>

#define SDL_MAIN_HANDLED
#include "DavEngine_Game/DavEngine.h"
#include "DavEngine_Game/input.h"
#include "SDL_image.h"

static void capFrameRate(long* then, float* remainder)
{
	long wait, frameTime;

	wait = 16 + (long)*remainder;

	*remainder -= (int)*remainder;

	frameTime = SDL_GetTicks() - *then;

	wait -= frameTime;

	if (wait < 1)
	{
		wait = 1;
	}

	SDL_Delay(wait);

	*remainder += (int)0.667;

	*then = SDL_GetTicks();
}

static void cleanup()
{
	std::cout << "static void cleanup()" << std::endl;
}

int main()
{
	long then;
	float remainder;

    IGame::Instance()->Initialize();
	Input* inputObj = new Input(((DavEngine*)IGame::Instance())->GetApp());

	atexit(cleanup);

	then = SDL_GetTicks();

	remainder = 0;

	while (1)
	{
		IGame::Instance()->GetWindowHandler()->PrepareWindow();

		inputObj->DoInput();

		IGame::Instance()->GetLogicHandler()->Logic();

		IGame::Instance()->GetWindowHandler()->Draw();

		IGame::Instance()->GetWindowHandler()->PresentWindow();

		capFrameRate(&then, &remainder);
	}

	return 0;
}