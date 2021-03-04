#ifndef _INPUT_H_
#define _INPUT_H_

struct App;
struct SDL_KeyboardEvent;

class Input
{
public:
	Input(App* a_app);
	~Input();

	void DoInput();
	

private:
	App* m_app;

	void DoKeyUp(SDL_KeyboardEvent* event);
	void DoKeyDown(SDL_KeyboardEvent* event);
};

#endif // !_INPUT_H_
