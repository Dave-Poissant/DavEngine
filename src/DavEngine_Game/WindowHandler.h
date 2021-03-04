#ifndef _WINDOWHANDLER_H_
#define _WINDOWHANDLER_H_

#include <string>
#include <deque>

struct App;
struct Stage;
struct Entity;
struct SDL_Texture;

class WindowHandler
{
public:
	WindowHandler(int a_width, int a_height, App* a_app);

	~WindowHandler();

	void InitializeTexture();

	void PrepareWindow();
	void PresentWindow();
	void Draw();
	void FireBullet();

	std::deque<Entity*>* GetBulletDeque();
	Entity* GetPlayerEntity();

	void Blit(Entity* a_entity);
	SDL_Texture* LoadTexture(char* a_filename);

private:
	void InitPlayer();
	void InitBullet();

	void DrawPlayer();
	void DrawBullets();

	App* m_app;
	SDL_Texture* m_bulletTexture;
	Entity* m_playerEntity;

	int m_width;
	int m_height;

	std::deque<Entity*> m_bulletEntitysDeque;
};

#endif // !_WINDOWHANDLER_H_
