#ifndef _DAVENGINE_H_
#define _DAVENGINE_H_

#include "DavEngine_common/IGame.h"
#include "DavEngine_defs.h"

class WindowHandler;
class LogicHandler;
class InputHandler;

class DavEngine : public AbstractGame
{
public:
	DavEngine();

	void Initialize() override;
	void InitSDLObject();

	App* GetApp();
	WindowHandler* GetWindowHandler() override;
	LogicHandler* GetLogicHandler() override;
	InputHandler* GetInputHandler() override;

private:
	App* m_app;
	WindowHandler* m_windowHandler;
	LogicHandler* m_logicHandler;
	InputHandler* m_inputHandler;

	DavEngine(const DavEngine& a_toCopy);
	DavEngine& operator = (const DavEngine& a_toAssign);

	virtual ~DavEngine();
};

#endif // !_DAVENGINE_H_


