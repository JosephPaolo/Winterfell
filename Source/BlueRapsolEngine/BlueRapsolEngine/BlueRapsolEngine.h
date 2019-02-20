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
#include "../../BlueRapsolEngine/BlueRapsolEngine/GameTimer.h"
#include "SplashScreen.h"
#include <SFML/Graphics.hpp>

class BlueRapsolEngine {

public:
	BlueRapsolEngine(HINSTANCE hInstance);
	//~BlueRapsolEngine();

	KeyboardListener kbInput;
	MouseListener mbInput;

	void Run(HINSTANCE hInstance);

	//Check for sufficient storage space
	bool ChkStorage(unsigned long long requiredBytes, LPCWSTR directory);

	//Check for available RAM and virtual memory
	void ChkMem();

	//Display CPU speed and architecture
	void DisplayCPUArch();
	void DisplayCPUSpeed();

	virtual void GameUpdate();

private:
	GameTimer mTimer;
	bool isInitializing = true;

	bool IsOnlyInstance(LPCTSTR appName);
	void Initialize(sf::RenderWindow & renderWindow);
	void GameLoop(sf::RenderWindow & renderWindow);
};
