#ifndef _DAVENGINE_H_
#define _DAVENGINE_H_

#include "DavEngine_common/IGame.h"
#include "DavEngine_defs.h"
#include "WindowHandler.h"
#include "LogicHandler.h"

class DavEngine : public AbstractGame
{
public:
	DavEngine();

	void Initialize() override;
	void InitSDLObject();

	App* GetApp();
	WindowHandler* GetWindowHandler();
	LogicHandler* GetLogicHandler();

private:
	App* m_app;
	WindowHandler* m_windowHandler;
	LogicHandler* m_logicHandler;

	DavEngine(const DavEngine& a_toCopy);
	DavEngine& operator = (const DavEngine& a_toAssign);

	virtual ~DavEngine();
};

#endif // !_DAVENGINE_H_


