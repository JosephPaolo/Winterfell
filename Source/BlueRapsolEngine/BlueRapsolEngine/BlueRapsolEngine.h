//*************************************************************************** 
// File name: InitBlueRapsol.h
// Authors: Joseph Malibiran, Tsuzuri Okada, Terence Stewart (C) 2018 All Rights Reserved. 
// Created: Sept. 19, 2018
// Last Updated: Sept. 19, 2018
// Version: 0.0.1A
// Description: 
//   This Class will represent the Game Application layer of the Blue Rapsol Engine
// *****************************************************************************

#pragma once

#include <windows.h>
#include <WinBase.h>
#include "../../BlueRapsolEngine/BlueRapsolEngine/KeyboardListener.h"
#include "../../BlueRapsolEngine/BlueRapsolEngine/MouseListener.h"
#include "InitBlueRapsol.h" 
#include "GameTimer.h"

class BlueRapsolEngine {

public:
	KeyboardListener kbInput;
	MouseListener mbInput;

	void Run(HINSTANCE hInstance);

private:
	void Initialize(HINSTANCE hInstance);
	int GameLoop();

protected:
	// Used to keep track of the “delta-time” and game time (§4.4).
	GameTimer mTimer;

};
