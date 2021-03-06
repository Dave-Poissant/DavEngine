#include "DavEngine.h"
#include "WindowHandler.h"
#include "LogicHandler.h"
#include "InputHandler.h"

IGame* IGame::m_game = new DavEngine();

DavEngine::DavEngine() : AbstractGame()
{
    std::cout << "- DavEngine::DavEngine() -" << std::endl;
	m_app = nullptr;
	m_windowHandler = nullptr;
	m_logicHandler = nullptr;
	m_inputHandler = nullptr;
}

void DavEngine::Initialize()
{
    AbstractGame::Initialize();
    std::cout << "- DavEngine::Initialize() -" << std::endl;

    m_app = new App();
	memset(m_app, 0, sizeof(App));

    m_windowHandler = new WindowHandler(SCREEN_WIDTH, SCREEN_HEIGHT, m_app);
	m_logicHandler = new LogicHandler(m_app);

	InitSDLObject();
	m_windowHandler->InitializeTexture();

	m_inputHandler = new InputHandler(m_app);
}

void DavEngine::InitSDLObject()
{
	int rendererFlags, windowFlags;

	rendererFlags = SDL_RENDERER_ACCELERATED;

	windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1); // TODO: Create exception class to throw handled exceptions
	}
	m_app->window = SDL_CreateWindow("DavEngine_game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

	if (!m_app->window)
	{
		printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
		exit(1); // TODO: Create exception class to throw handled exceptions
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

	m_app->renderer = SDL_CreateRenderer(m_app->window, -1, rendererFlags);

	if (!m_app->renderer)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1); // TODO: Create exception class to throw handled exceptions
	}
}

App* DavEngine::GetApp()
{
    return m_app;
}

WindowHandler* DavEngine::GetWindowHandler()
{
    return m_windowHandler;
}

LogicHandler* DavEngine::GetLogicHandler()
{
	return m_logicHandler;
}

InputHandler* DavEngine::GetInputHandler()
{
	return m_inputHandler;
}

DavEngine::~DavEngine()
{
    if (m_app != nullptr)
    {
        delete m_app;
        m_app = nullptr;
    }

    if (m_windowHandler != nullptr)
    {
        delete m_windowHandler;
        m_windowHandler = nullptr;
    }

	if (m_logicHandler != nullptr)
	{
		delete m_logicHandler;
		m_logicHandler = nullptr;
	}

	if (m_inputHandler != nullptr)
	{
		delete m_inputHandler;
		m_inputHandler = nullptr;
	}
}
