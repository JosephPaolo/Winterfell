#pragma once

#include "BlueRapsolEngine.h"

//Name of this program for Mutex
#define MUTEX_APP_NAME L"BlueRapsolEngineMutex"

class BlueRapsolApp : public BlueRapsolEngine {

public:
	BlueRapsolApp(HINSTANCE hInstance);
	virtual bool Initialize();

protected:
	virtual void GameStart();
	virtual void GameUpdate();

};
