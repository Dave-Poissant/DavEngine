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

private:
	void DoPlayer();
	void DoEnemies();
	void DoBullets();
	void SpawnEnemies();

	App* m_app;

	int m_enemySpawnTimer;
};

#endif // !_LOGICHANDLER_H_
