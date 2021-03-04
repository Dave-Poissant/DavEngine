#ifndef _WINDOWHANDLER_H_
#define _WINDOWHANDLER_H_

#include <string>
#include <map>

struct App;
struct Stage;
struct Entity;
struct SDL_Texture;

class WindowHandler
{
public:
	WindowHandler(int a_width, int a_height, App* a_app, Stage* a_stage);

	~WindowHandler();

	void InitializeTexture();

	void PrepareWindow();
	void PresentWindow();
	void Draw();
	void FireBullet();

	std::map<std::string, Entity*>* GetEntityMap();

	void Blit(Entity* a_entity);
	SDL_Texture* LoadTexture(char* a_filename);

private:
	void InitPlayer();
	void InitBullet();

	void DrawPlayer();
	void DrawBullets();

	Stage* m_stage;
	App* m_app;
	SDL_Texture* m_bulletTexture;

	int m_width;
	int m_height;

	std::map<std::string, Entity*> textureEntitysMap;

};

#endif // !_WINDOWHANDLER_H_
