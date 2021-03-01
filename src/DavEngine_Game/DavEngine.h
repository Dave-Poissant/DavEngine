#ifndef _DAVENGINE_H_
#define _DAVENGINE_H_

#include "DavEngine_common/IGame.h"

class DavEngine : public AbstractGame
{
public:
	DavEngine();

	void Initialize() override;

	DavEngine(const DavEngine& a_toCopy);
	DavEngine& operator = (const DavEngine& a_toAssign);

	virtual ~DavEngine() {};
};

#endif // !_DAVENGINE_H_


