#ifndef _DRAW_H_
#define _DRAW_H_

struct App;

class draw
{
public:
	draw(){};
	~draw(){};

	void prepareScene(App* a_app);
	void presentScene(App* a_app);
};

#endif // !_DRAW_H_
