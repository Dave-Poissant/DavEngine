#include "DavEngine_Game/DavEngine.h"
#define SDL_MAIN_HANDLED
#include "DavEngine_Game/structs.h"
#include "DavEngine_Game/initSDL.h"
#include "DavEngine_Game/draw.h"
#include "DavEngine_Game/input.h"
#include "SDL_image.h"

App app;

static void cleanup()
{
	std::cout << "static void cleanup()" << std::endl;
}

int main()
{
    IGame::Instance()->Initialize();
	memset(&app, 0, sizeof(App));

	draw* drawObj = new draw();
	input* inputObj = new input();
	initSDL* initSDLObj = new initSDL();

	initSDLObj->initSDLObject(&app);

	atexit(cleanup);

	while (1)
	{
		drawObj->prepareScene(&app);

		inputObj->doInput();

		drawObj->presentScene(&app);

		SDL_Delay(16);
	}

	delete drawObj;
	delete inputObj;
	delete initSDLObj;

	return 0;
}