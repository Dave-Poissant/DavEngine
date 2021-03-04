#ifndef _LOGICHANDLER_H_
#define _LOGICHANDLER_H_

struct Stage;
struct App;

class LogicHandler
{
public:
	LogicHandler(Stage* a_stage, App* a_app);
	~LogicHandler();

	void Logic();
	void DoPlayer();
	void DoBullets();

private:
	Stage* m_stage;
	App* m_app;
};

#endif // !_LOGICHANDLER_H_
