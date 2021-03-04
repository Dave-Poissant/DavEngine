#ifndef _LOGICHANDLER_H_
#define _LOGICHANDLER_H_

struct Stage;
struct App;

class LogicHandler
{
public:
	LogicHandler(App* a_app);
	~LogicHandler();

	void Logic();
	void DoPlayer();
	void DoBullets();

private:
	App* m_app;
};

#endif // !_LOGICHANDLER_H_
