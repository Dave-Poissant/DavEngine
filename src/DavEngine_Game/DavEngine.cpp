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

    m_app = new App();
	memset(m_app, 0, sizeof(App));

	m_player = new TextureEntity();
	memset(m_player, 0, sizeof(TextureEntity));

    m_windowHandler = new WindowHandler(SCREEN_WIDTH, SCREEN_HEIGHT);

	InitSDLObject();
	InitTextureEntity();
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

void DavEngine::InitTextureEntity()
{
	m_player->x = 100;
	m_player->y = 100;
	std::string currentPath = "C:\\Users\\davep\\Desktop\\DavEngine\\gfx";
	std::string filename = currentPath + "\\player.png";
	m_player->texture = m_windowHandler->loadTexture((char*)filename.c_str(), m_app);
}

App* DavEngine::GetApp()
{
    return m_app;
}

TextureEntity* DavEngine::GetTextureEntity()
{
	return m_player;
}

WindowHandler* DavEngine::GetWindowHandler()
{
    return m_windowHandler;
}

DavEngine::~DavEngine()
{
    if (m_app != nullptr)
    {
        delete m_app;
        m_app = nullptr;
    }

	if (m_player != nullptr)
	{
		delete m_player;
		m_player = nullptr;
	}

    if (m_windowHandler != nullptr)
    {
        delete m_windowHandler;
        m_windowHandler = nullptr;
    }
}
