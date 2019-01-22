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
#include <stdlib.h> 
#include <string>
#include "../../BlueRapsolEngine/BlueRapsolEngine/KeyboardListener.h"
#include "../../BlueRapsolEngine/BlueRapsolEngine/MouseListener.h"
#include "../../DirectX/Common/GameTimer.h"
#include "../../DirectX/Framework/InitDirect3DApp.h"

class BlueRapsolEngine {

//Used in converting units of measurements from bytes
const LONGLONG toKB = 1024;
const LONGLONG toMB = 1024 * toKB;
const LONGLONG toGB = 1024 * toMB;

public:
	KeyboardListener kbInput;
	MouseListener mbInput;

	virtual void Initialize(HINSTANCE hInstance);
	//virtual bool Start();
	void Run(HINSTANCE hInstance);

	//Check for sufficient storage space
	bool ChkStorage(unsigned long long requiredBytes, LPCWSTR directory);

	//Check for available RAM and virtual memory
	void ChkMem();

	//Display CPU speed and architecture
	void DisplayCPUArch();
	void DisplayCPUSpeed();

private:
	//void Initialize(HINSTANCE hInstance);
	int GameLoop();

protected:
	// Used to keep track of the “delta-time” and game time (§4.4).
	GameTimer mTimer;

	//Initialize DirectX
	//TODO modify; TODO remove user input parameters
	int InitializeD3d(HINSTANCE hInstance);

	//Check for multiple Instances
	bool IsOnlyInstance(LPCTSTR appName);
};
