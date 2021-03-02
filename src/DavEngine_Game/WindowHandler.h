#ifndef _WINDOWHANDLER_H_
#define _WINDOWHANDLER_H_

#include <string>

struct App;
struct TextureEntity;
struct SDL_Texture;

class WindowHandler
{
public:
	WindowHandler(int a_width, int a_height) : m_width(a_width), m_height(a_height) {};
	~WindowHandler() {};

	void PrepareWindow(App* a_app);
	void PresentWindow(App* a_app);
	void blit(TextureEntity* a_textureEntity, App* a_app);
	SDL_Texture* loadTexture(char* a_filename, App* a_app);

private:
	int m_width;
	int m_height;

};

#endif // !_WINDOWHANDLER_H_
