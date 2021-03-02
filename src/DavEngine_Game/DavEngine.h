#ifndef _DAVENGINE_H_
#define _DAVENGINE_H_

#include "DavEngine_common/IGame.h"
#include "DavEngine_defs.h"
#include "WindowHandler.h"

class DavEngine : public AbstractGame
{
public:
	DavEngine();

	void Initialize() override;
	void InitSDLObject();
	void InitTextureEntity();

	App* GetApp();
	TextureEntity* GetTextureEntity();
	WindowHandler* GetWindowHandler();

private:
	App* m_app;
	TextureEntity* m_player;
	WindowHandler* m_windowHandler;

	DavEngine(const DavEngine& a_toCopy);
	DavEngine& operator = (const DavEngine& a_toAssign);

	virtual ~DavEngine();
};

#endif // !_DAVENGINE_H_


