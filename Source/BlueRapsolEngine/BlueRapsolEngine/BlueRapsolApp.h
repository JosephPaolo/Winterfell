#pragma once

#include <stdio.h>
#include "BlueRapsolEngine.h"
#include <string>

//Name of this program for Mutex
#define MUTEX_APP_NAME L"BlueRapsolEngineMutex"

class BlueRapsolApp : public BlueRapsolEngine {

public:
	BlueRapsolApp(HINSTANCE hInstance);
	virtual bool Initialize();

protected:
	virtual void GameStart();
	virtual void GameUpdate();

private:
	void CheckInput();

	std::string player1Key;
	std::string player2Key;
};
