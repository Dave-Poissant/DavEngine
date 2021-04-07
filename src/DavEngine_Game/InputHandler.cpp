#include "InputHandler.h"
#include "DavEngine_defs.h"

InputHandler::InputHandler(App* a_app) : m_app(a_app)
{

}

InputHandler::~InputHandler() {}

void InputHandler::DoInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			exit(0); // TODO: Create exception class to throw handled exceptions
			break;
		case SDL_KEYDOWN:
			DoKeyDown(&event.key);
			break;

		case SDL_KEYUP:
			DoKeyUp(&event.key);
			break;

		default:
			break;
		}
	}
}

void InputHandler::DoKeyDown(SDL_KeyboardEvent* event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		m_app->keyboard[event->keysym.scancode] = 1;
	}
}

void InputHandler::DoKeyUp(SDL_KeyboardEvent* event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		m_app->keyboard[event->keysym.scancode] = 0;
	}
}